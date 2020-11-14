#ifndef webFUN_H
#define webFUN_H
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
#include <pthread.h>
#include <sys/stat.h>
#include <errno.h>
#include "DTlog.h"
#include "cJSON.h"

#define PORT 51234
#define SERV "127.0.0.1"
#define QUEUE 20
#define BUFF_SIZE   4096
#define SMALL_Buff  512
#define MEDIUM_Buff 1024
#define LARGE_Buff  2048
#define HUGE_Buff   4096
#define TINY_Buff   128

#define false   -1
#define success 0

void handle_signal(int sign); // 退出信号处理
void http_send(int sock,char *content); // http 发送相应报文
void logMonitoringThread(void); //线程函数
int invokeKeyfunc(char *content,char* retJson);


#endif