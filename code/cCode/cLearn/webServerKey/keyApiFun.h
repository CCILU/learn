#ifndef KEYAPIFUN_H
#define KEYAPIFUN_H
#include "webFun.h"
#include "SKF_fun.h"

typedef struct keyHandle {
    DEVHANDLE       _DevHandle;
    HAPPLICATION    _AppHandle;
    HCONTAINER      _ConHandle;
}KEYHANDLE, *KEYHANLDEPTR;

static int emumKey(char *_keyName);
static DEVHANDLE connectKey(char *_keyName);
static int enumApplication(char *_appName, DEVHANDLE hDev);
static HAPPLICATION connectApplication(char *_appName,  DEVHANDLE hDev);
static int enumContainer(char *_conName, HAPPLICATION hApplication);
static HCONTAINER connectContainer(char *_conName, HAPPLICATION hApplication);
static int UseKey(KEYHANLDEPTR keyHandle) ;

#endif