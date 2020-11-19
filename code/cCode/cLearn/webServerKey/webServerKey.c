/**********************************************
 *编写时间：2020年11月10日
 *编写人：田朝阳
 *联系方式：17602929350
 *版本定义：V0001.0000
 *这个文件中实现main函数，主要启动socket服务，进行端口监听等相应功能
 *注意与警告：
 *1）main函数实现接收参数，第一个参数为PORT,第二个参数为IP地址，对PORT使用atoi()函数进行字符串
 *与整型转换。如若不传入参数或只传入PORT，默认PORT为51234，默认IP为127.0.0.1
 *2）daemon_init()可执行，此为守护进程，使程序在后台执行，正式出版时，可屏蔽打印信息
 *3）logMonitoringThread为一个监视日志的线程，当日志大小大于1GB时清除日志，可根据需要进行大小限定
 *以上若有其他问题请联系宋靖 微信号：songjing1807
 ********************************************/
#include "webFun.h"

int  DTKMServerLevel[5] = {DT_NO_LOG_LEVEL, DT_DEBUG_LEVEL, DT_INFO_LEVEL, DT_WARNING_LEVEL, DT_ERROR_LEVEL};
int sockfd;
char *buff;
char *retJson;
pthread_t logMonitoringThreadId;
char *http_res_tmpl_bak = "HTTP/1.1 200 OK\r\n"
        "Server: Cleey's Server V1.0\r\n"
		"Accept-Ranges: bytes\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "Content-Type: %s\r\n\r\n";
char *http_res_tmpl = "HTTP/1.1 200 OK\r\n"
		"Server: dean's Server V1.0\r\n"
		"Access-Control-Allow-Credentials: true\r\n"
        "Access-Control-Allow-Methods: GET,POST\r\n"
        "Access-Control-Allow-Origin: *\r\n"
		"Content-Type: text/html; charset=GB2312\r\n\r\n";


int main(int argc, char *argv[]) {
    //daemon_init();//守护进程
    int portInt = 0;
    int rv = 0;
    int opt=1;
	int count = 0; // 计数prhread_create();
    //接收自定义信号量
    signal(SIGINT,handle_signal);
    //启动一个线程，用于监控日志的大小，防止长时间使用日志过大，日志路径在/home/
    rv = pthread_create(&logMonitoringThreadId, NULL, (void*)logMonitoringThread, NULL);
    if(rv) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "prhread_create error!");
    }
    // 定义 socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    // 定义 sockaddr_in
    struct sockaddr_in skaddr;
    // ipv4
    skaddr.sin_family = AF_INET;
    if(argc > 1 && argc < 3) {
        portInt = atoi(argv[1]);
        printf("Port = %d\n", portInt);
        skaddr.sin_port   = htons(portInt);
        printf("IP = %s\n", SERV);
        skaddr.sin_addr.s_addr = inet_addr(SERV);
    }
    else if(argc > 2){
        portInt = atoi(argv[1]);
        printf("Port = %d\n",portInt);
        skaddr.sin_port   = htons(portInt);
        printf("IP = %s\n", argv[2]);
        skaddr.sin_addr.s_addr = inet_addr(argv[2]);
    }
    else {
        printf("Port = %d\n", PORT);
        printf("IP = %s\n", SERV);
        skaddr.sin_port   = htons(PORT);
        skaddr.sin_addr.s_addr = inet_addr(SERV);
    }
    // bind，绑定 socket 和 sockaddr_in
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if( bind(sockfd,(struct sockaddr *)&skaddr,sizeof(skaddr)) == -1 ){
            perror("bind error");
            exit(1);
    }
    // listen，开始添加端口
    if( listen(sockfd,QUEUE) == -1 ) {
            perror("listen error");
            exit(1);
    }
    // 客户端信息
    struct sockaddr_in claddr;
    socklen_t length = sizeof(claddr);
    buff = (char *)malloc(BUFF_SIZE+1);
    if(buff == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "buff malloc error!");
        return -1;
    }
	retJson = (char *)malloc(BUFF_SIZE+1);
    if(retJson == NULL) {
        free(buff);
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "retJson malloc error!");
        return -1;
    }
    while(1) {
		memset(retJson, 0, BUFF_SIZE);
        memset(buff, 0, BUFF_SIZE);
        //printf("等待连接...\n");
        int sock_client = accept(sockfd,(struct sockaddr *)&claddr, &length);
        if(sock_client < 0) {
            perror("accept error");
            free(buff);
            free(retJson);
            exit(1);
        }
        int len = recv(sock_client, buff, BUFF_SIZE, 0);
        //int len = recv(sock_client,buff,sizeof(buff),0);
		if( len > 0) {
            printf("buff = %s\n", buff);
        }
		else {
			printf("recv error:%s\n", strerror(errno));
			continue;
		}
		char* json = strstr(buff,"json=");
		if(json != NULL) {
			json = json+5;
			printf("json = %s\n",json);
		}
		else {
			//printf("buffer no json\n");
			continue;
		}
		rv = invokeKeyfunc(json, retJson);
        if(rv != 0) {
            http_send(sock_client,retJson);
            printf("retJson = %s\n",retJson);
            DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "invokeKeyfunc error!");
            continue;
        }
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "invokeKeyfunc rv= %X", rv);
		printf("retJson = %s\n",retJson);
		http_send(sock_client,retJson);
        close(sock_client);
    }
    free(buff);
    free(retJson);
    fputs("Bye Cleey",stdout);
    close(sockfd);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "key service stop");
    pthread_exit(&logMonitoringThreadId);
    return 0;
}