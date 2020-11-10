#include "keyApiFun.h"

#define DEBUG_KEYAPI

#define false   -1
#define success 0

#ifdef DEBUG_KEYAPI
int  DTKMServerLevel[5] = {DT_NO_LOG_LEVEL, DT_DEBUG_LEVEL, DT_INFO_LEVEL, DT_WARNING_LEVEL, DT_ERROR_LEVEL};
#else
extern int  DTKMServerLevel[];
#endif

static int enumKey(char *_keyName) { //默认一个设备
    ULONG ret = 0;
    LPSTR KeyName = NULL;
    ULONG pulSize = 0;
    ret = SKF_EnumDev(1, KeyName, &pulSize);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "emumKey SKF_EnumDev error!%X", ret);
        return false;
    }
    KeyName = (char *)malloc(pulSize+1);
    if(KeyName == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "emumKey malloc error!");
        return false;
    }
    memset(KeyName, 0x00, pulSize+1);
    ret = SKF_EnumDev(1, KeyName, &pulSize);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "emumKey SKF_EnumDev error!%X", ret);
        free(KeyName);
        return false;
    }
    memcpy(_keyName, KeyName, pulSize);
    free(KeyName);
    return success;
}

static DEVHANDLE connectKey(char *_keyName) {
    ULONG ret = 0;
    DEVHANDLE devHandle = NULL;
    ret = SKF_ConnectDev (_keyName, &devHandle);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "connectKey SKF_ConnectDev error!%X", ret);
        return NULL;
    }
    return devHandle;
}

static int enumApplication(char *_appName, DEVHANDLE hDev) { //默认为单应用
    ULONG ret = 0;
    LPSTR AppName = NULL;
    ULONG pulSize = 0;
    ret = SKF_EnumApplication(hDev, AppName, &pulSize);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "emumApplication SKF_EnumApplication error!%X", ret);
        return false;
    }
    AppName = (char *)malloc(pulSize+1);
    if(AppName == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "emumApplication malloc error!");
        return false;
    }
    memset(AppName, 0x00, pulSize+1);
    ret = SKF_EnumApplication(hDev, AppName, &pulSize);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "emumApplication SKF_EnumApplication error!%X", ret);
        free(AppName);
        return false;
    }
    memcpy(_appName, AppName, pulSize);
    free(AppName);
    return success;
}

static HAPPLICATION connectApplication(char *_appName,  DEVHANDLE hDev) {
    ULONG ret = 0;
    HANDLE appHandle = NULL;
    ret = SKF_OpenApplication(hDev, _appName, &appHandle);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "connectApplication SKF_OpenApplication error!%X", ret);
        return NULL;
    }
    return appHandle;
}

static int enumContainer(char *_conName, HAPPLICATION hApplication) {//默认为单容器
    ULONG ret = 0;
    LPSTR ConName = NULL;
    ULONG pulSize = 0;
    ret = SKF_EnumContainer(hApplication, ConName, &pulSize);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "enumContainer SKF_EnumContainer error!%X", ret);
        return false;
    }
    ConName = (char*)malloc(pulSize+1);
    memset(ConName, 0x00, pulSize+1);
    ret = SKF_EnumContainer(hApplication, ConName, &pulSize);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "enumContainer SKF_EnumContainer error!%X", ret);
        free(ConName);
        return false;
    }
    memcpy(_conName, ConName, pulSize);
    free(ConName);
    return success;
}

static HCONTAINER connectContainer(char *_conName, HAPPLICATION hApplication) {
    ULONG ret = 0;
    HANDLE conHandle = NULL;
    ret = SKF_OpenContainer(hApplication, _conName, &conHandle);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "connectContainer SKF_OpenContainer error!%X", ret);
        return NULL;
    }
    return conHandle;
}

static KEYHANDLE UseKey() {
    int ret = 1;
    KEYHANDLE keyHandle;
    char* UseString = (char*)malloc(TINY_Buff);
    if(UseString == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey malloc error!");
        return NULL;
    }
    memset(UseString, 0x00, TINY_Buff);
    ret = enumKey(UseString);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey enumKey error!");
        return NULL;
    }
    keyHandle._DevHandle = connectKey(UseString);
    if(keyHandle._DevHandle == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey connectKey error!");
        return NULL;
    }
    memset(UseString, 0x00, TINY_Buff);
    ret = enumApplication(UseString, keyHandle._DevHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey enumApplication error!");
        return NULL;
    }
    keyHandle._AppHandle = connectApplication(UseString,  keyHandle._DevHandle);
    if(keyHandle._AppHandle == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey connectApplication error!");
        SKF_DisConnectDev(keyHandle._DevHandle);
        return NULL;
    }
    memset(UseString, 0x00, TINY_Buff);
    ret = enumContainer(UseString, keyHandle._AppHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey enumContainer error!");
        return NULL;
    }
    keyHandle._ConHandle = connectContainer(UseString, keyHandle._AppHandle);
    if(keyHandle._ConHandle == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey connectContainer error!");
        SKF_DisConnectDev(keyHandle._DevHandle);
        SKF_CloseApplication(keyHandle._AppHandle);
        return NULL;
    }
    return keyHandle;
}

#ifdef DEBUG_KEYAPI
void main() {
    KEYHANLDEPTR keyHandle = NULL;

    keyHandle =  UseKey();
    if(keyHandle !=  NULL) {
        printf("ok \n");
    }
}

#endif