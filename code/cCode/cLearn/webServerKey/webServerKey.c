#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>
#include "DTlog.h"

int  DTKMServerLevel[5] = {DT_NO_LOG_LEVEL, DT_DEBUG_LEVEL, DT_INFO_LEVEL, DT_WARNING_LEVEL, DT_ERROR_LEVEL};
int sockfd;

#define PORT 8888
#define SERV "127.0.0.1"
#define QUEUE 20
#define BUFF_SIZE 4096

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

void handle_signal(int sign); // 退出信号处理
void http_send(int sock,char *content); // http 发送相应报文
void http_send(int sock_client,char *content)
{
	char HTTP_HEADER[BUFF_SIZE],HTTP_INFO[BUFF_SIZE];
	int len = strlen(content);
	sprintf(HTTP_HEADER, http_res_tmpl);
	len = sprintf(HTTP_INFO, "%s%s", HTTP_HEADER,content);
	//printf("\nsend ok!\n");
	send(sock_client,HTTP_INFO,len,0);
}
void handle_signal(int sign)
{
    fputs("\nSIGNAL INTERRUPT \nBye Cleey! \nSAFE EXIT\n",stdout);
    close(sockfd);
    exit(0);
}

int main(int argc, char *argv[]) {
    int portInt = 0;
    int opt=1;
	int count = 0; // 计数

    signal(SIGINT,handle_signal);
    // 定义 socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    // 定义 sockaddr_in
    struct sockaddr_in skaddr;
    // ipv4
    skaddr.sin_family = AF_INET;
    if(argc > 1) {
        portInt = atoi(argv[1]);
        skaddr.sin_port   = htons(portInt);
        skaddr.sin_addr.s_addr = inet_addr(SERV);
    }
    else if(argc > 2){
        portInt = atoi(argv[1]);
        skaddr.sin_port   = htons(PORT);
        skaddr.sin_addr.s_addr = inet_addr(argv[2]);
    }
    else {
        skaddr.sin_port   = htons(portInt);
        skaddr.sin_addr.s_addr = inet_addr(SERV);
    }
    // bind，绑定 socket 和 sockaddr_in
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if( bind(sockfd,(struct sockaddr *)&skaddr,sizeof(skaddr)) == -1 ){
            perror("bind error");
            exit(1);
    }
    // listen，开始添加端口
    if( listen(sockfd,QUEUE) == -1 ){
            perror("listen error");
            exit(1);
    }
}