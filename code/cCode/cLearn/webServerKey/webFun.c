/**********************************************
 *编写时间：2020年11月10日
 *编写人：田朝阳
 *联系方式：17602929350
 *版本定义：V0001.0000
 *这个webFunc.c文件主要实现webServerKey.c中需求函数的实现，invokeKeyfunc调用keyApiFun.c中函数
 *实现主要对入包的分析以及对智能密码钥匙的调用
 *为方便测试和查看，不再进行多文件的区分，也不刻意严格保证一个函数不应该超过一定行数的规则
 *此文件尽量使用比较全的英文单词作为函数与参数的命名，以确保在不用编写过多凌乱的注释说明来使
 *阅读者尽量明白函数与参数的功能。
 *注意与警告：
 *以上若有其他问题请联系宋靖 微信号：songjing1807
 ***********************************************/
#include "webFun.h"
#include "keyApiFun.h"


extern int  DTKMServerLevel[];
extern int  sockfd;
extern char *buff;
extern char *retJson;
extern pthread_t logMonitoringThreadId;
extern char *http_res_tmpl_bak;
extern char *http_res_tmpl;

//守护进程
int daemon_init() {
	pid_t pid;
	if((pid=fork())<0)
		return -1;
	else if(pid!=0)
		exit(0);
	setsid();
	chdir("/");
	umask(0);
	return 0;
}
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
    close(sockfd);
	pthread_exit(&logMonitoringThreadId);
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
		return false;
	}
    func = cJSON_GetObjectItem(root, "func");
	if(!func || func->type!=cJSON_String) {
		strcpy(retJson,"{\"data\":\"error\"}");
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "cJSON_GetObjectItem error!");
		return false;
	}
	//函数判断
    if(!strcmp(func->valuestring, "hello")) {
		strcpy(retJson,"{\"data\":\"hello\"}");
		return success;
	}
	//int KeyLogInWithVerifyUserPin(char *KeyPin);
    else if(!strcmp(func->valuestring, "KeyLogInWithVerifyUserPin")) {
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root, "KeyPin");
		if(!param1 || param1->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		int rv = KeyLogInWithVerifyUserPin(param1->valuestring);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "KeyLogInWithVerifyUserPin   error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("success"));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	//int SignMessageWithEccKeyAndWithoutSm3(char *pbData, ULONG ulDataLen, char *SignOut);
	else if(!strcmp(func->valuestring, "SignMessageWithEccKeyAndWithoutSm3")) {
		char SignOut[TINY_Buff] = {0};
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root, "pbData");
		if(!param1 || param1->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param2 = cJSON_GetObjectItem(root,"ulDataLen");
		if(!param2 || param2->type != cJSON_Number)
		{
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error7\"}");
			return -1;
		}
		int rv = SignMessageWithEccKeyAndWithoutSm3(param1->valuestring, param2->valueint, SignOut);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3  error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString(SignOut));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	//int SignMessageWithEccKeyAndWithSm3NoPid(char *pbData, ULONG ulDataLen, char *SignOut);
	else if(!strcmp(func->valuestring, "SignMessageWithEccKeyAndWithSm3NoPid")) {
		char SignOut[TINY_Buff] = {0};
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root, "pbData");
		if(!param1 || param1->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param2 = cJSON_GetObjectItem(root,"ulDataLen");
		if(!param2 || param2->type != cJSON_Number)
		{
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error7\"}");
			return -1;
		}
		int rv = SignMessageWithEccKeyAndWithSm3NoPid(param1->valuestring, param2->valueint, SignOut);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithSm3NoPid  error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString(SignOut));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	//int SignMessageVerifyWithoutSm3(char *ECCPubKey, char *pbData, ULONG  ulDataLen, char *Signature);
	else if(!strcmp(func->valuestring, "SignMessageVerifyWithoutSm3")) {
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root, "ECCPubKey");
		if(!param1 || param1->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param2 = cJSON_GetObjectItem(root, "pbData");
		if(!param2 || param2->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param3 = cJSON_GetObjectItem(root,"ulDataLen");
		if(!param3 || param3->type!=cJSON_Number)
		{
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error7\"}");
			return -1;
		}
		param4 = cJSON_GetObjectItem(root, "Signature");
		if(!param4 || param4->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		int rv = SignMessageVerifyWithoutSm3(param1->valuestring, param2->valuestring, param3->valueint, param4->valuestring);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageVerifyWithoutSm3  error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("success"));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	//int SignMessageVerifyWithSm3NoPid(char *ECCPubKey, char *pbData, ULONG  ulDataLen, char *Signature);
	else if(!strcmp(func->valuestring, "SignMessageVerifyWithSm3NoPid")) {
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root, "ECCPubKey");
		if(!param1 || param1->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param2 = cJSON_GetObjectItem(root, "pbData");
		if(!param2 || param2->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param3 = cJSON_GetObjectItem(root,"ulDataLen");
		if(!param3 || param3->type!=cJSON_Number)
		{
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error7\"}");
			return -1;
		}
		param4 = cJSON_GetObjectItem(root, "Signature");
		if(!param4 || param4->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		int rv = SignMessageVerifyWithSm3NoPid(param1->valuestring, param2->valuestring, param3->valueint, param4->valuestring);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageVerifyWithSm3NoPid  error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("success"));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	//int GetECCPublicKey(BOOL bSignFlag, char *PublicKey);//网页调用只传入前1个参数
	else if(!strcmp(func->valuestring, "GetECCPublicKey")) {
		char PublicKey[TINY_Buff+16] = {0};
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root,"bSignFlag");
		if(!param1 || param1->type != cJSON_Number)
		{
			printf ("param1->valueint = %d, param1->valuestring = %s \n",param1->valueint, param1->valuestring);
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error7\"}");
			return -1;
		}
		int rv = GetECCPublicKey(param1->valueint, PublicKey);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetECCPublicKey  error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString(PublicKey));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	//int GetCertificate(BOOL bSignFlag, char *certBuff)
	else if(!strcmp(func->valuestring, "GetCertificate")) {
		char certBuf[LARGE_Buff] = {0};
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root,"bSignFlag");
		if(!param1 || param1->type != cJSON_Number)
		{
			printf ("param1->valueint = %d, param1->valuestring = %s \n",param1->valueint, param1->valuestring);
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error7\"}");
			return -1;
		}
		int rv = GetCertificate(param1->valueint, certBuf);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetCertificate  error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString(certBuf));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	//int SetSessionKeyAndMessageEncrypt(BYTE* SessionKey,BYTE *pbData, ULONG ulDataLen, char* pbEncryptedData);
	else if(!strcmp(func->valuestring, "SetSessionKeyAndMessageEncrypt")) {
		char pbEncryptedData[MEDIUM_Buff] = {0};
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root, "SessionKey");
		if(!param1 || param1->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param2 = cJSON_GetObjectItem(root, "pbData");
		if(!param2 || param2->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param3 = cJSON_GetObjectItem(root,"ulDataLen");
		if(!param3 || param3->type!=cJSON_Number)
		{
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error7\"}");
			return -1;
		}
		int rv = SetSessionKeyAndMessageEncrypt(param1->valuestring, param2->valuestring, param3->valueint, pbEncryptedData);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageEncrypt  error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString(pbEncryptedData));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	//int SetSessionKeyAndMessageDecrypt(BYTE* SessionKey, BYTE *pbData, ULONG ulDataLen, char* pbDecryptData);
	else if(!strcmp(func->valuestring, "SetSessionKeyAndMessageDecrypt")) {
        char pbDecryptData[MEDIUM_Buff] = {0};
		cJSON * returnJson =  cJSON_CreateObject();
		param1 = cJSON_GetObjectItem(root, "SessionKey");
		if(!param1 || param1->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param2 = cJSON_GetObjectItem(root, "pbData");
		if(!param2 || param2->type != cJSON_String) {
			strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error0\"}");
			return false;
		}
		param3 = cJSON_GetObjectItem(root,"ulDataLen");
		if(!param3 || param3->type!=cJSON_Number)
		{
			strcpy(retJson,"{\"rtnCode\":-1,\"data\":\"error7\"}");
			return -1;
		}
		int rv = SetSessionKeyAndMessageDecrypt(param1->valuestring, param2->valuestring, param3->valueint, pbDecryptData);
		if(rv != success) {
			cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(rv));
			cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString("error"));
			strcpy(retJson, cJSON_Print(returnJson));
			DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt  error!");
			return false;
		}
		cJSON_AddItemToObject(returnJson, "rtnCode", cJSON_CreateNumber(0));
		cJSON_AddItemToObject(returnJson, "data", cJSON_CreateString(pbDecryptData));
		strcpy(retJson, cJSON_Print(returnJson));
		return success;
	}
	else{//end
		strcpy(retJson,"{\"rtnCode\":false,\"data\":\"error60\"}");
		DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "function name  error!");
		printf("func->valuestring = %s\n",func->valuestring);
		return false;
	}
}