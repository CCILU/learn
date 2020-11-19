/**********************************************
 *编写时间：2020年11月10日
 *编写人：田朝阳
 *联系方式：17602929350
 *版本定义：V0001.0000
 *这个keyApiFun.c文件主要实现调用国标接口来实现key的调用，这个文件的主要依赖库为libskf.so
 *为方便测试和查看，不再进行多文件的区分，也不刻意严格保证一个函数不应该超过一定行数的规则
 *#define DEBUG_KEYAPI定义时，main函数和必要定义会被编译，屏蔽时则作为普通用函数接口被调用
 *此文件尽量使用比较全的英文单词作为函数与参数的命名，以确保在不用编写过多凌乱的注释说明来使
 *阅读者尽量明白函数与参数的功能。
 *注意与警告：
 *1）此文件暂时适配的为SJK1912-G安可环境下的智能密码钥匙，软件库与COS版本均为3.0版本
 *此版本中需要注意的是TypeDefine.h文件中typedef int	INT32;typedef unsigned long ULONG;的定义
 *与其他版本存在差异，使用其他版本libskf.so库有可能会引起段错误。
 *且3.0版本的国标库与COS设置中容器的名称长度为36位，如果cos版本与国标库版本不匹配可能会导致容器可以创建
 *但是在下次使用的时候发生指定容器不存在的错误
 *2）此文件适配的SJK1912-G密码钥匙libskf.so库中的设备句柄宏定义因为一些历史原因原型为typedef int HANDLE;
 *这与一般的typedef void* HANDLE;有所不同，在使用句柄时应有所注意，避免使用错误的指针导致段错误的发生。由其是
 *以此版服务为基础适配其他国标key时更应该注意。
 *3）在枚举时会出现枚举成功但返回字符串为空的情况，此时请关注所枚举的内容是否存在，判断返回字符串是否为\0\0\0
 *以上若有其他问题请联系宋靖 微信号：songjing1807
***********************************************/
#include "keyApiFun.h"

//#define DEBUG_KEYAPI //去除注释可进行单C程序测试

#ifdef DEBUG_KEYAPI
int  DTKMServerLevel[5] = {DT_NO_LOG_LEVEL, DT_DEBUG_LEVEL, DT_INFO_LEVEL, DT_WARNING_LEVEL, DT_ERROR_LEVEL};
#else
extern int  DTKMServerLevel[];
#endif

HANDLE phKey;

static int enumKey(char *_keyName) { //默认一个设备
    ULONG ret = 0;
    LPSTR KeyName = NULL;
    ULONG pulSize = 0;
    ret = SKF_EnumDev(1, KeyName, &pulSize);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "enumKey SKF_EnumDev error!%X", ret);
        return false;
    }
    //printf("pulSize = %d\n",pulSize);
    KeyName = (char *)malloc(pulSize+1);
    if(KeyName == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "enumKey malloc error!");
        return false;
    }
    memset(KeyName, 0x00, pulSize+1);
    ret = SKF_EnumDev(1, KeyName, &pulSize);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "enumKey SKF_EnumDev error!%X", ret);
        free(KeyName);
        return false;
    }
    //printf("pulSize = %d\n",strlen(KeyName));
    //printf("%s\n",KeyName);
    if(_keyName == NULL) {
        printf("_keyName is NULL\n");
        free(KeyName);
        return false;
    }
    memcpy(_keyName,  KeyName,  16);
    free(KeyName);
    return success;
}

static DEVHANDLE connectKey(char *_keyName) {
    ULONG ret = 0;
    DEVHANDLE devHandle = 0;
    ret = SKF_ConnectDev (_keyName, &devHandle);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "connectKey SKF_ConnectDev error!%X", ret);
        return false;
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
    HANDLE appHandle = 0;
    ret = SKF_OpenApplication(hDev, _appName, &appHandle);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "connectApplication SKF_OpenApplication error!%X", ret);
        return false;
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
    HANDLE conHandle = 0;
    ret = SKF_OpenContainer(hApplication, _conName, &conHandle);
    if(ret != 0x00000000) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "connectContainer SKF_OpenContainer error!%X", ret);
        return false;
    }
    return conHandle;
}

static int useKey(KEYHANLDEPTR keyHandle) {
    int ret = 1;
    char* UseString = (char*)malloc(TINY_Buff);
    if(UseString == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey malloc error!");
        return false;
    }
    memset(UseString, 0x00, TINY_Buff);
    ret = enumKey(UseString);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey enumKey error!");
        free(UseString);
        UseString = NULL;
        return false;
    }
    keyHandle->_DevHandle = connectKey(UseString);
    if(keyHandle->_DevHandle == false) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey connectKey error!");
        free(UseString);
        UseString = NULL;
        return false;
    }
    memset(UseString, 0x00, TINY_Buff);
    ret = enumApplication(UseString, keyHandle->_DevHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey enumApplication error!");
        free(UseString);
        UseString = NULL;
        return false;
    }
    keyHandle->_AppHandle = connectApplication(UseString,  keyHandle->_DevHandle);
    if(keyHandle->_AppHandle == false) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey connectApplication error!");
        SKF_DisConnectDev(keyHandle->_DevHandle);
        free(UseString);
        UseString = NULL;
        return false;
    }
    memset(UseString, 0x00, TINY_Buff);
    ret = enumContainer(UseString, keyHandle->_AppHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey enumContainer error!");
        free(UseString);
        UseString = NULL;
        return false;
    }
    keyHandle->_ConHandle = connectContainer(UseString, keyHandle->_AppHandle);
    if(keyHandle->_ConHandle == false) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "UseKey connectContainer error!");
        free(UseString);
        UseString = NULL;
        return false;
    }

    free(UseString);
    UseString = NULL;
    return success;
}

static void freeAllHandle(KEYHANDLE  keyHandle){
    SKF_CloseContainer(keyHandle._ConHandle);
    SKF_CloseApplication(keyHandle._AppHandle);
    SKF_DisConnectDev(keyHandle._DevHandle);
}

int KeyLogInWithVerifyUserPin(char *KeyPin) {
    KEYHANDLE  keyHandle = {0};
    ULONG pulRetryCount = 0;
    int ret = 3;
    ret = useKey(&keyHandle);//这里多进行了一个打开了一个容器操作，有需要可以把UseKey函数进行拆分,有可能会因为没有容器导致错误
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "KeyLogInWithVerifyUserPin UseKey error!");
        return false;
    }
    ret = SKF_VerifyPIN(keyHandle._AppHandle, 1, KeyPin, &pulRetryCount);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "KeyLogInWithVerifyUserPin SKF_VerifyPIN error! ret is %X, pulRetryCount is %d", ret, pulRetryCount);
        return false;
    }
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "KeyLogInWithVerifyUserPin success! pulRetryCount is %d", pulRetryCount);
    freeAllHandle(keyHandle);
    return success;
}
//函数输出参数时将结构体转换为一个字符串并使用BASE64编码进行输出，避免数据传输时的二次组包
int SignMessageWithEccKeyAndWithoutSm3(char *pbData, ULONG ulDataLen, char *SignOut) {
    KEYHANDLE  keyHandle = {0};
    ULONG pulRetryCount = 0;
    ECCSIGNATUREBLOB pSignature = {0};
    char singMidData[64] = {0};
    int ret = 3;
    ret = useKey(&keyHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 UseKey error!");
        return false;
    }
    ret = SKF_ECCSignData(keyHandle._ConHandle, pbData, ulDataLen, &pSignature);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 SKF_ECCSignData error! ret is %X, ", ret);
        return false;
    }
    memcpy(singMidData, (char *)pSignature.r+32, 32);
    memcpy(singMidData+32, (char *)pSignature.s+32, 32);
    //PrintHex("singMidData", singMidData, 64, 16);
    ret = base64_encode(singMidData, 64, SignOut);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 base64_encode error! ret is %X, ", ret);
        return false;
    }
    freeAllHandle(keyHandle);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SignMessageWithEccKeyAndWithoutSm3 success! SignOut is %s", SignOut);
    return success;
}

int SignMessageWithEccKeyAndWithSm3NoPid(char *pbData, ULONG ulDataLen, char *SignOut){
    KEYHANDLE  keyHandle = {0};
    ULONG pulRetryCount = 0;
    ECCSIGNATUREBLOB pSignature = {0};
    char singMidData[64] = {0};
    int ret = 3;
    ret = useKey(&keyHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 UseKey error!");
        return false;
    }
    ret = SM3_Hash(pbData, ulDataLen, singMidData);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithSm3NoPid SM3_Hash error!");
        return false;
    }
    //PrintHex("SM3_Hash", singMidData, 64, 16);
    ret = SKF_ECCSignData(keyHandle._ConHandle, singMidData, 32, &pSignature);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 SKF_ECCSignData error! ret is %X, ", ret);
        return false;
    }
    memset(singMidData, 0x00, 64);
    memcpy(singMidData, (char *)pSignature.r+32, 32);
    memcpy(singMidData+32, (char *)pSignature.s+32, 32);
    //PrintHex("singMidData", singMidData, 64, 16);
    ret = base64_encode(singMidData, 64, SignOut);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 base64_encode error! ret is %X, ", ret);
        return false;
    }
    freeAllHandle(keyHandle);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SignMessageWithEccKeyAndWithoutSm3 success! SignOut is %s", SignOut);
    return success;
}

int SignMessageVerifyWithoutSm3(char *ECCPubKey, char *pbData, ULONG  ulDataLen, char *Signature) {
    KEYHANDLE  keyHandle = {0};
    char       MidData[TINY_Buff] = {0};
    int        ret = 8;
    unsigned long  bin_size = 0;
    //SKF_ECCVerify(DEVHANDLE hDev , ECCPUBLICKEYBLOB* pECCPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);
    ECCSIGNATUREBLOB pSignature = {0};
    ECCPUBLICKEYBLOB ECCPubKeyBlob = {0};
    ret = useKey(&keyHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageVerifyWithoutSm3 UseKey error!");
        return false;
    }
    ret = base64_decode(ECCPubKey, MidData, &bin_size);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageVerifyWithoutSm3 base64_decode ECCPubKey error! ret is %X, ", ret);
        return false;
    }
    memcpy((char *)ECCPubKeyBlob.XCoordinate+32, MidData, 32);
    memcpy((char *)ECCPubKeyBlob.YCoordinate+32, MidData+32, 32);
    memset(MidData, 0x00, TINY_Buff);
    ret = base64_decode(Signature, MidData, &bin_size);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageVerifyWithoutSm3 base64_decode  Signature error! ret is %X, ", ret);
        return false;
    }
    memcpy((char *)pSignature.r+32, MidData, 32);
    memcpy((char *)pSignature.s+32, MidData+32, 32);
    ret = SKF_ECCVerify(keyHandle._DevHandle, &ECCPubKeyBlob, pbData, ulDataLen, &pSignature);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 SKF_ECCVerify error! ret is %X, ", ret);
        return false;
    }
    freeAllHandle(keyHandle);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SignMessageVerifyWithoutSm3 success! ret is %X", ret);
    return success;
}

int SignMessageVerifyWithSm3NoPid(char *ECCPubKey, char *pbData, ULONG  ulDataLen, char *Signature) {
    KEYHANDLE  keyHandle = {0};
    char       MidData[TINY_Buff] = {0};
    int        ret = 8;
    unsigned long  bin_size = 0;
    char       hashData[32] = {0};
    //SKF_ECCVerify(DEVHANDLE hDev , ECCPUBLICKEYBLOB* pECCPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);
    ECCSIGNATUREBLOB pSignature = {0};
    ECCPUBLICKEYBLOB ECCPubKeyBlob = {0};
    ret = useKey(&keyHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageVerifyWithoutSm3 UseKey error!");
        return false;
    }
    ret = SM3_Hash(pbData, ulDataLen, hashData);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithSm3NoPid SM3_Hash error!");
        return false;
    }
    ret = base64_decode(ECCPubKey, MidData, &bin_size);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageVerifyWithoutSm3 base64_decode ECCPubKey error! ret is %X, ", ret);
        return false;
    }
    memcpy((char *)ECCPubKeyBlob.XCoordinate+32, MidData, 32);
    memcpy((char *)ECCPubKeyBlob.YCoordinate+32, MidData+32, 32);
    memset(MidData, 0x00, TINY_Buff);
    ret = base64_decode(Signature, MidData, &bin_size);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageVerifyWithoutSm3 base64_decode  Signature error! ret is %X, ", ret);
        return false;
    }
    memcpy((char *)pSignature.r+32, MidData, 32);
    memcpy((char *)pSignature.s+32, MidData+32, 32);
    ret = SKF_ECCVerify(keyHandle._DevHandle, &ECCPubKeyBlob, hashData, 32, &pSignature);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 SKF_ECCVerify error! ret is %X, ", ret);
        return false;
    }
    freeAllHandle(keyHandle);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SignMessageVerifyWithoutSm3 success! ret is %X", ret);
    return success;
}

int GetECCPublicKey(BOOL bSignFlag, char *PublicKey) {//默认一个应用，一个容器 1:签名 0：加密
    KEYHANDLE  keyHandle = {0};
    int        ret = 8;
    char       MidData[TINY_Buff] = {0};
    ULONG      pulBlobLen = 0;
    ret = useKey(&keyHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetECCPublicKey UseKey error!");
        return false;
    }
    ret = SKF_ExportPublicKey(keyHandle._ConHandle, bSignFlag, PublicKey, &pulBlobLen);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetECCPublicKey SKF_ExportPublicKey error! ret is %X, ", ret);
        return false;
    }
    memcpy(MidData, PublicKey+4+32, 32);
    memcpy(MidData+32, PublicKey+4+32+32+32, 32);
    //PrintHex("GetECCPublicKey", MidData, 64, 16);
    memset(PublicKey, 0x00, TINY_Buff+16);
    ret = base64_encode(MidData, 64, PublicKey);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SignMessageWithEccKeyAndWithoutSm3 base64_encode error! ret is %X, ", ret);
        return false;
    }
    freeAllHandle(keyHandle);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "GetECCPublicKey success! PublicKey is %s", PublicKey);
    return success;
}

int SetSessionKeyAndMessageEncrypt(BYTE* SessionKey,BYTE *pbData, ULONG ulDataLen, char* pbEncryptedData) { //最大传入长度512字节 //网页调用前三个参数传入
    KEYHANDLE        keyHandle = {0};
    BLOCKCIPHERPARAM EncryptParam;
    ECCCIPHERBLOB 	 pbWrapedData = {0};
    ULONG            pulBlobLen = 0;
    ULONG            pulEncryptedLen = 0;
    char             MidData[MEDIUM_Buff] = {0};
    char             PublicKey[TINY_Buff] = {0};
    ECCPUBLICKEYBLOB ECCPubKeyBlob = {0};
    int              ret = 8;
    if(ulDataLen > 512) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageEncrypt inData too long ");
        return false;
    }
    ret = useKey(&keyHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKey UseKey error!");
        return false;
    }
    ret = SKF_ExportPublicKey(keyHandle._ConHandle, 0, PublicKey, &pulBlobLen);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageEncrypt SKF_ExportPublicKey error! ret is %X, ", ret);
        return false;
    }
    memcpy(ECCPubKeyBlob.XCoordinate+32, PublicKey+4+32, 32);
    memcpy(ECCPubKeyBlob.YCoordinate+32, PublicKey+4+32+32+32, 32);
    ret = SKF_ExtECCEncrypt (keyHandle._DevHandle, &ECCPubKeyBlob, SessionKey, 16, &pbWrapedData);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageEncrypt SKF_ExtECCEncrypt error! ret is %X, ", ret);
        return false;
    }
    ret = SKF_ImportSessionKey (keyHandle._ConHandle, SGD_SM4_ECB , &pbWrapedData, 16, &phKey);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageEncrypt SKF_ImportSessionKey error! ret is %X, ", ret);
        return false;
    }
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SetSessionKeyAndMessageEncrypt success! ImportSessionKey handle is %X", phKey);
    ret = SKF_EncryptInit (phKey, EncryptParam);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "MessageEncrypt SKF_EncryptInit error! ret is %X, ", ret);
        return false;
    }
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SetSessionKeyAndMessageEncrypt success! SKF_EncryptInit is %X", ret);
    ret = SKF_Encrypt(phKey, pbData, ulDataLen, MidData, &pulEncryptedLen);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "MessageEncrypt SKF_Encrypt error! ret is %X, ", ret);
        return false;
    }
    ret = base64_encode(MidData, pulEncryptedLen, pbEncryptedData);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "MessageEncrypt base64_encode error! ret is %X, ", ret);
        return false;
    }
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SetSessionKeyAndMessageEncrypt success! SKF_Encrypt pbEncryptedData is %s", pbEncryptedData);
    freeAllHandle(keyHandle);
    return success;
}

int SetSessionKeyAndMessageDecrypt(BYTE* SessionKey, BYTE *pbData, ULONG ulDataLen, char* pbDecryptData) { //最大传入长度512字节BASE64编码后长度 //网页调用前三个参数传入
    KEYHANDLE        keyHandle = {0};
    BLOCKCIPHERPARAM EncryptParam;
    ECCCIPHERBLOB 	 pbWrapedData = {0};
    ULONG            pulBlobLen = 0;
    ULONG            pulEncryptedLen = 0;
    char             MidData[MEDIUM_Buff] = {0};
    char             PublicKey[TINY_Buff] = {0};
    ECCPUBLICKEYBLOB ECCPubKeyBlob = {0};
    ULONG            pulDataLen = 0;
    unsigned long    bin_size = 0;
    int              ret = 8;
    if(ulDataLen > 700) { //512字节BASE64加密后输出长度为684
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt inData too long ");
        return false;
    }
    ret = useKey(&keyHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt UseKey error!");
        return false;
    }
    ret = SKF_ExportPublicKey(keyHandle._ConHandle, 0, PublicKey, &pulBlobLen);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt SKF_ExportPublicKey error! ret is %X, ", ret);
        return false;
    }
    memcpy(ECCPubKeyBlob.XCoordinate+32, PublicKey+4+32, 32);
    memcpy(ECCPubKeyBlob.YCoordinate+32, PublicKey+4+32+32+32, 32);
    ret = SKF_ExtECCEncrypt (keyHandle._DevHandle, &ECCPubKeyBlob, SessionKey, 16, &pbWrapedData);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt SKF_ExtECCEncrypt error! ret is %X, ", ret);
        return false;
    }
    ret = SKF_ImportSessionKey (keyHandle._ConHandle, SGD_SM4_ECB , &pbWrapedData, 16, &phKey);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt SKF_ImportSessionKey error! ret is %X, ", ret);
        return false;
    }
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SetSessionKeyAndMessageDecrypt success! ImportSessionKey handle is %X", phKey);
    ret = SKF_DecryptInit (phKey, EncryptParam);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt SKF_DecryptInit error! ret is %X, ", ret);
        return false;
    }
    ret = base64_decode(pbData, MidData, &bin_size);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt base64_decode error! ret is %X, ", ret);
        return false;
    }
    ret = SKF_Decrypt(phKey, MidData, bin_size, pbDecryptData, &pulDataLen);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "SetSessionKeyAndMessageDecrypt SKF_Decrypt error! ret is %X, ", ret);
        return false;
    }
    //printf("SignMessageWithEccKeyAndWithSm3NoPid = %s\n", pbDecryptData);
    //PrintHex("beforeOutData", beforeOutData, 64, 16);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "SetSessionKeyAndMessageDecrypt success! SKF_Decrypt pbDecryptData is %s", pbDecryptData);
    freeAllHandle(keyHandle);
    return success;
}

int GetCertificate(BOOL bSignFlag, char *certBuff) {//默认一个应用，一个容器 1:签名 0：加密 //传入certBuff长度应大于mid防止base64加密后长度变长，导致的段错误
    KEYHANDLE  keyHandle = {0};
    int        ret = 8;
    ULONG      pulCertLen = 0;
    char       *midData = NULL;
    ret = useKey(&keyHandle);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetCertificate UseKey error!");
        return false;
    }
    ret = SKF_ExportCertificate(keyHandle._ConHandle, bSignFlag,  midData, &pulCertLen);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetCertificate SKF_ExportCertificate error! ret is %X, ", ret);
        return false;
    }
    midData = (char *)malloc(pulCertLen+64);
    if(midData == NULL) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetCertificate malloc error!");
        return false;
    }
    memset(midData, 0x00, pulCertLen+64);
    ret = SKF_ExportCertificate(keyHandle._ConHandle, bSignFlag,  midData, &pulCertLen);
    if(ret != 0x00) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetCertificate SKF_ExportCertificate error! ret is %X, ", ret);
        return false;
    }
    ret = base64_encode(midData, pulCertLen, certBuff);
    if(ret != success) {
        DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[4], 0, "GetCertificate base64_encode error! ret is %X, ", ret);
        return false;
    }
    freeAllHandle(keyHandle);
    DTKMServer_Log(__FILE__, __LINE__, DTKMServerLevel[2], 0, "GetCertificate success! Certificate is %s", certBuff);
    return success;
}

#ifdef DEBUG_KEYAPI
void main() {
    int ret = 3;
    char indata[] = "12345678123456781234567812345678";
    char indata2[] = "1234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678";
    char oudata[128] = {0};
    char PublicKey[TINY_Buff+16] = {0};
    char pbEncryptedData[MEDIUM_Buff+64] = {0};
    char pbDecryptData[MEDIUM_Buff] = {0};
    char certBuff[LARGE_Buff] = {0};
    ret = KeyLogInWithVerifyUserPin("111111");
    printf("KeyLogInWithVerifyUserPin ret = %d\n", ret);
    printf("\n");

    ret = SignMessageWithEccKeyAndWithoutSm3(indata, 32, oudata);
    printf("SignMessageWithEccKeyAndWithoutSm3 ret = %d\n", ret);
    printf("SignMessageWithEccKeyAndWithoutSm3 = %s\n", oudata);
    printf("\n");

    ret = GetECCPublicKey(1,PublicKey);
    printf("GetECCPublicKey ret = %d\n", ret);
    printf("PublicKey = %s\n", PublicKey);
    printf("\n");

    ret = SignMessageVerifyWithoutSm3(PublicKey, indata, 32, oudata);
    printf("SignMessageVerifyWithoutSm3 ret = %d\n", ret);
    printf("\n");

    ret = SetSessionKeyAndMessageEncrypt("1111111111111111", indata2, 512, pbEncryptedData);
    printf("SetSessionKeyAndMessageEncrypt ret = %d\n", ret);
    printf("pbEncryptedData = %s\n", pbEncryptedData);
    printf("pbEncryptedData len is %ld\n", strlen(pbEncryptedData));
    printf("\n");

    ret = SetSessionKeyAndMessageDecrypt("1111111111111111", pbEncryptedData, strlen(pbEncryptedData), pbDecryptData);
    printf("SetSessionKeyAndMessageDecrypt ret = %d\n", ret);
    printf("pbDecryptData = %s\n", pbDecryptData);
    printf("pbDecryptData len is %ld\n", strlen(pbDecryptData));
    printf("\n");

    memset(oudata, 0x00, 128);
    ret = SignMessageWithEccKeyAndWithSm3NoPid(indata2, 1024, oudata);
    printf("SignMessageWithEccKeyAndWithSm3NoPid ret = %d\n", ret);
    printf("SignMessageWithEccKeyAndWithSm3NoPid = %s\n", oudata);
    printf("\n");

    ret = SignMessageVerifyWithSm3NoPid(PublicKey, indata2, 1024, oudata);
    printf("SignMessageVerifyWithSm3NoPid ret = %d\n", ret);
    printf("\n");

    ret = GetCertificate(1, certBuff);
    printf("GetCertificate ret = %d\n", ret);
    printf("GetCertificate ret = %s\n", certBuff);
    printf("\n");
}

#endif
