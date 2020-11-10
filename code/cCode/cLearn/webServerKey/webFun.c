#include "webFun.h"
#include "keyApiFun.h"


extern int  DTKMServerLevel[];
extern int  sockfd;
extern char *buff;
extern char *retJson;
extern pthread_t logMonitoringThreadId;
extern char *http_res_tmpl_bak;
extern char *http_res_tmpl;

//发送函数，发送调用结果
void http_send(int sock_client,char *content) {
	char HTTP_HEADER[BUFF_SIZE],HTTP_INFO[BUFF_SIZE];
	int len = strlen(content);
    memset(HTTP_HEADER, 0x00, BUFF_SIZE);
    memset(HTTP_INFO, 0x00, BUFF_SIZE);
	sprintf(HTTP_HEADER, http_res_tmpl, "%s%s");
	len = sprintf(HTTP_INFO, "%s%s", HTTP_HEADER, content);
	//printf("\nsend ok!\n");
	send(sock_client,HTTP_INFO,len,0);
}
//信号处理函数，用于自定义信号处理，主要处理CTRL+C的结束
void handle_signal(int sign) {
    fputs("\nSIGNAL INTERRUPT \nBye Cleey! \nSAFE EXIT\n",stdout);
    free(buff);
    free(retJson);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "key service stop");
    pthread_exit(&logMonitoringThreadId);
    close(sockfd);
    exit(0);
}
//线程函数，用于监控日志大小，如果过大会对日志进行删除，函数中size为日志文件大小
void logMonitoringThread(void) {
    struct stat statbuf;
    long size = 0;
    char fileName[64];
    char systemManage[128];
	memset(fileName, 0, sizeof(fileName));
    memset(systemManage, 0, sizeof(fileName));
	sprintf(fileName, "%s/%s", getenv("HOME"), DTAU_DEBUG_FILE_);
    stat(fileName,&statbuf);
    size = statbuf.st_size;
    printf("%s size is %ld\n", DTAU_DEBUG_FILE_, size);
    if(size > 1073741824) { //日志大于1024M清除日志
        sprintf(systemManage, "echo " " > %s", fileName);
        system(systemManage);
    }
}
int invokeKeyfunc(char *content,char* retJson) {
    cJSON  *root,*func,*param1,*param2,*param3,*param4,*param5,*param6,*param7,*param8,*param9;

    root = cJSON_Parse(content);
    if(root == NULL) {
		strcpy(retJson,"{\"data\":\"error\"}");
		DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "cJSON_Parse error!");
		return -1;
	}
    func = cJSON_GetObjectItem(root, "func");
	if(!func || func->type!=cJSON_String) {
		strcpy(retJson,"{\"data\":\"error\"}");
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "cJSON_GetObjectItem error!");
		return -1;
	}
    if(!strcmp(func->valuestring, "hello")) {
		strcpy(retJson,"{\"data\":\"hello\"}");
	}
    else if(!strcmp(func->valuestring, "DaIcLogIn")) {
		char *psnID = (char*)malloc(SMALL_Buff);
        if(psnID == NULL) {
            DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "DaIcLogIn malloc error!");
            return -1;
        }
        memset(psnID, 0x00, SMALL_Buff);
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root, "pin");
		if(!param1 || param1->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error0\"}");
			return -1;
		}
		int rv = DaIcLogIn(param1->valuestring, psnID);
		if(rv !=0) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "DaIcLogIn   error!");
            free(psnID);
			return -1;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString(psnID));
		strcpy(retJson, cJSON_Print(returnJson));
        free(psnID);
	}

}