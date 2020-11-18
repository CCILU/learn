#ifndef KEYAPIFUN_H
#define KEYAPIFUN_H
#include "webFun.h"
#include "SKF_fun.h"
#include "pem2der.h"
#include "SM3.h"

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
static int useKey(KEYHANLDEPTR keyHandle);
static void freeAllHandle(KEYHANDLE  keyHandle);

int KeyLogInWithVerifyUserPin(char *KeyPin);
int SignMessageWithEccKeyAndWithoutSm3(char *pbData, ULONG ulDataLen, char *SignOut);//网页调用只传入前两个参数
int SignMessageWithEccKeyAndWithSm3NoPid(char *pbData, ULONG ulDataLen, char *SignOut);//网页调用只传入前两个参数
int SignMessageVerifyWithoutSm3(char *ECCPubKey, char *pbData, ULONG  ulDataLen, char *Signature);
int SignMessageVerifyWithSm3NoPid(char *ECCPubKey, char *pbData, ULONG  ulDataLen, char *Signature);
int GetECCPublicKey(BOOL bSignFlag, char *PublicKey);//网页调用只传入前1个参数
int GetCertificate(BOOL bSignFlag, char *certBuff);//网页调用只传入前1个参数
#endif