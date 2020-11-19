#ifndef _DTLOG_H_
#define _DTLOG_H_

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
extern char DTKMServer_LevelName[5][10] ;

//Level类别
#define DT_NO_LOG_LEVEL			0
#define DT_DEBUG_LEVEL			1
#define DT_INFO_LEVEL			2
#define DT_WARNING_LEVEL		3
#define DT_ERROR_LEVEL			4

#define DTAU_DEBUG_FILE_	"invokeKey.log"
#define DTAU_MAX_STRING_LEN 		10240

void DTKMServer_Log(const char *file, int line, int level, int status, const char *fmt, ...);
void func();
#endif
