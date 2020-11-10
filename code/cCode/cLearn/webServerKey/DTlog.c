#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "DTlog.h"

//Level的名称
char DTKMServer_LevelName[5][10] = {"NOLOG", "DEBUG", "INFO", "WARNING", "ERROR"};
//实际使用的Level
//int  DTKMServerLevel[5] = {DT_NO_LOG_LEVEL, DT_DEBUG_LEVEL, DT_INFO_LEVEL, DT_WARNING_LEVEL, DT_ERROR_LEVEL};

static int DTKMServer_Error_GetCurTime(char* strTime)
{
	struct tm*		tmTime = NULL;
	size_t			timeLen = 0;
	time_t			tTime = 0;
	struct timeval tv;
	struct tm* ptm;
	long milliseconds;
	char time_string[40]={0};

	gettimeofday (&tv, NULL);
	ptm = localtime (&tv.tv_sec);
	//tTime = time(NULL);
	//tmTime = localtime(&tTime);
	//timeLen = strftime(strTime, 33, "%Y(Y)%m(M)%d(D)%H(H)%M(M)%S(S)", tmTime);
	timeLen = strftime(time_string, 33, "%Y.%m.%d %H:%M:%S", ptm);
	milliseconds = tv.tv_usec/1000;
	sprintf(strTime,"%s:%03ld",time_string, milliseconds);
	return timeLen;
}


static int DTKMServer_Error_OpenFile(int* pf)
{
	char	fileName[256];

	memset(fileName, 0, sizeof(fileName));
	//printf("start log!\n");
	sprintf(fileName, "%s/%s", getenv("HOME"), DTAU_DEBUG_FILE_);
    *pf = open(fileName, O_WRONLY|O_CREAT|O_APPEND, 0666);
    if(*pf < 0)
    {
		printf("open file fail!\n");
        return-1;
    }
	return 0;
}

static void DTKMServer_Error_Core(const char *file, int line, int level, int status, const char *fmt, va_list args)
{
    char str[DTAU_MAX_STRING_LEN];
    int	 strLen = 0;
    char tmpStr[64];
    int	 tmpStrLen = 0;
    int  pf = 0;
    //初始化
    memset(str, 0, DTAU_MAX_STRING_LEN);
    memset(tmpStr, 0, 64);
    //加入LOG时间
    tmpStrLen = DTKMServer_Error_GetCurTime(tmpStr);
    tmpStrLen = sprintf(str, "[%s] ", tmpStr);
    strLen = tmpStrLen;

    //加入LOG等级
    if(level == DT_DEBUG_LEVEL)
    {
        tmpStrLen = sprintf(str+strLen, "[%s] ", DTKMServer_LevelName[level]);
    }
    else
    {
        tmpStrLen = sprintf(str+strLen, "[**%s**] ", DTKMServer_LevelName[level]);
    }
    strLen += tmpStrLen;
    //加入LOG状态
    if (status != 0)
    {
        tmpStrLen = sprintf(str+strLen, "[ERRNO is %d] ", status);
    }
    else
    {
        tmpStrLen = sprintf(str+strLen, "[SUCCESS] ");
    }
    strLen += tmpStrLen;

    //加入LOG信息
    tmpStrLen = vsprintf(str+strLen, fmt, args);
    strLen += tmpStrLen;

    //加入LOG发生文件
    tmpStrLen = sprintf(str+strLen, " [%s]", file);
    strLen += tmpStrLen;

    //加入LOG发生行数
    tmpStrLen = sprintf(str+strLen, " [%d]\n", line);
    strLen += tmpStrLen;
    //打开LOG文件
    if(DTKMServer_Error_OpenFile(&pf))
	{
		return ;
	}
    //写入LOG文件
    write(pf, str, strLen);
    //关闭文件
    close(pf);
    return ;
}


void DTKMServer_Log(const char *file, int line, int level, int status, const char *fmt, ...)
{
    va_list args;
	if(level == DT_NO_LOG_LEVEL)
	{
		return ;
	}
	//调用核心的写LOG函数
    va_start(args, fmt);
    DTKMServer_Error_Core(file, line, level, status, fmt, args);
    va_end(args);
    return ;
}

