/***************************************************
//���ң��ð�
//�汾��2.0
//����ʱ�䣺2019��12��10��
//�����ˣ�tzy sl
//��ϵ��ʽ��dean_tzy@datech.com.cn   dean_sl@datech.com.cn
****************************************************/
#ifndef __SKF_FUN_H__
#define __SKF_FUN_H__
#ifdef __cplusplus
extern "C"{
#endif

#include "TypeDefine.h"

#define SGD_SM2_1 		0x00020100 	  //��Բ����ǩ���㷨
#define SGD_SM2_3	    0x00020400	  //��Բ���߼����㷨
#define SGD_SM1_ECB	    0x00000101	  //SM1�㷨ECB����ģʽ
#define SGD_SM1_CBC	    0x00000102	  //SM1�㷨CBC����ģʽ
#define SGD_SM4_ECB		0x00000401	  //SM4�㷨ECB����ģʽ
#define SGD_SM4_CBC		0x00000402    //SM4�㷨CBC����ģʽ
#define SGD_SM3	        0x00000001	  //SM3�Ӵ��㷨
//#define DEVAPI			__attribute__((__stdcall__))		 
/*�ļ�����*/
typedef struct Struct_FILEATTRIBUTE{
CHAR	FileName[32];//����
ULONG	FileSize;	 //����
ULONG	ReadRights;  //��Ȩ��
ULONG	WriteRights; //дȨ��
} FILEATTRIBUTE, *PFILEATTRIBUTE;

/*�ǶԳ��㷨SM2*/
//ECC_MAX_XCOORDINATE_LENΪECC�㷨X�������󳤶�
#define ECC_MAX_XCOORDINATE_BITS_LEN 512
//ECC_MAX_YCOORDINATE_LENΪECC�㷨Y�������󳤶�
#define ECC_MAX_YCOORDINATE_BITS_LEN 512
//ECC_MAX_MODULUS_BITS_LENΪECC�㷨ģ������󳤶�
#define ECC_MAX_MODULUS_BITS_LEN 512

//ECC��Կ���ݽṹ
typedef struct Struct_ECCPUBLICKEYBLOB{
ULONG	BitLen;
BYTE	XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
BYTE	YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8];
}ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB;
//ECC˽Կ���ݽṹ
typedef struct Struct_ECCPRIVATEKEYBLOB{
ULONG	BitLen;
BYTE	PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8];
}ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB;

//ECC�������ݽṹ
typedef struct Struct_ECCCIPHERBLOB{
BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8]; 
BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8]; 
BYTE  HASH[32]; 
ULONG CipherLen;
BYTE  Cipher[256]; 
} ECCCIPHERBLOB, *PECCCIPHERBLOB;

//ECC������Կ�Ա����ṹ
typedef struct SKF_ENVELOPEDKEYBLOB{
ULONG Version;                  // ��ǰ�汾Ϊ 1
ULONG ulSymmAlgID;              // �Գ��㷨��ʶ���޶�ECBģʽ
ULONG ulBits;					// ������Կ�Ե���Կλ����
BYTE cbEncryptedPriKey[64];     // ������Կ��˽Կ������
ECCPUBLICKEYBLOB PubKey;        // ������Կ�ԵĹ�Կ
ECCCIPHERBLOB ECCCipherBlob;    // �ñ�����Կ���ܵĶԳ���Կ���ġ�
}ENVELOPEDKEYBLOB, *PENVELOPEDKEYBLOB;

//ECCǩ�����ݽṹ
typedef struct Struct_ECCSIGNATUREBLOB{
BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];
BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];
} ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;

/*�ǶԳ��㷨RSA*/
//ʵ�ʳ���ΪBitLen/8�ֽ�  ģ��n = p * q
#define MAX_RSA_MODULUS_LEN 256
#define MAX_RSA_EXPONENT_LEN 4
//RSA��Կ���ݽṹ
typedef struct Struct_RSAPUBLICKEYBLOB{
ULONG	AlgID;//�㷨��ʶ��
ULONG	BitLen;//ģ����ʵ��λ����
BYTE	Modulus[MAX_RSA_MODULUS_LEN];//ģ��n = p * q
BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];//������Կe	 һ��Ϊ00010001
}RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB;
//MAX_RSA_MODULUS_LENΪ�㷨ģ������󳤶ȣ�
//MAX_RSA_EXPONENT_LENΪ�㷨ָ������󳤶ȡ�

//RSA˽Կ���ݽṹ
typedef struct Struct_RSAPRIVATEKEYBLOB{
ULONG	AlgID;//�㷨��ʶ��
ULONG	BitLen;//ģ����ʵ��λ����	������8�ı���
BYTE	Modulus[MAX_RSA_MODULUS_LEN];//ģ��n = p * q	ʵ�ʳ���ΪBitLen/8�ֽ�
BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];//������Կe	һ��Ϊ00010001
BYTE	PrivateExponent[MAX_RSA_MODULUS_LEN];//˽����Կd	ʵ�ʳ���ΪBitLen/8�ֽ�
BYTE	Prime1[MAX_RSA_MODULUS_LEN/2];//����p	ʵ�ʳ���ΪBitLen/16�ֽ�
BYTE	Prime2[MAX_RSA_MODULUS_LEN/2];//����q	ʵ�ʳ���ΪBitLen/16�ֽ�
BYTE	Prime1Exponent[MAX_RSA_MODULUS_LEN/2];//d mod (p-1)��ֵ	ʵ�ʳ���ΪBitLen/16�ֽ�
BYTE	Prime2Exponent[MAX_RSA_MODULUS_LEN/2];//d mod (q -1)��ֵ	ʵ�ʳ���ΪBitLen/16�ֽ�
BYTE	Coefficient[MAX_RSA_MODULUS_LEN/2];//qģp�ĳ˷���Ԫ	ʵ�ʳ���ΪBitLen/16�ֽ�
}RSAPRIVATEKEYBLOB, *PRSAPRIVATEKEYBLOB;
//MAX_RSA_MODULUS_LENΪRSA�㷨ģ������󳤶ȣ�


//��ʼ������MAX_IV_LENΪ��ʼ����������󳤶�
#define MAX_IV_LEN 32
//�����������
typedef struct Struct_BLOCKCIPHERPARAM{
BYTE	IV[MAX_IV_LEN];
ULONG	IVLen;		 //��ʼ����ʵ�ʳ��ȣ����ֽڼ��㣩
ULONG	PaddingType; //��䷽ʽ��0��ʾ����䣬1��ʾ����PKCS#5��ʽ�������
ULONG	FeedBitLen;	 //����ֵ��λ���ȣ���λ���㣩	ֻ���OFB��CFBģʽ
} BLOCKCIPHERPARAM, *PBLOCKCIPHERPARAM;

/*�豸��Ϣ*/
//�汾
typedef struct Struct_Version{
BYTE major;//���汾��     ���汾�źʹΰ汾���ԡ�.���ָ������� Version 1.0�����汾��Ϊ1���ΰ汾��Ϊ0��Version 2.10�����汾��Ϊ2���ΰ汾��Ϊ10��
BYTE minor;//BYTE	�ΰ汾��
}VERSION;
//�豸��Ϣ
typedef struct Struct_DEVINFO{
VERSION		Version;//�汾�� ���ݽṹ�汾�ţ����ṹ�İ汾��Ϊ1.0
CHAR		Manufacturer[64];//�豸������Ϣ	�ԡ�\0��Ϊ��������ASCII�ַ���
CHAR		Issuer[64];//���г�����Ϣ	�ԡ�\0��Ϊ��������ASCII�ַ���
CHAR		Label[32];//�豸��ǩ	�ԡ�\0��Ϊ��������ASCII�ַ���
CHAR		SerialNumber[32];//���к�	�ԡ�\0��Ϊ��������ASCII�ַ���
VERSION		HWVersion; //�豸Ӳ���汾 
VERSION		FirmwareVersion;//�豸�����̼��汾
ULONG		AlgSymCap;//���������㷨��ʶ
ULONG		AlgAsymCap;//�ǶԳ������㷨��ʶ
ULONG		AlgHashCap;//�����Ӵ��㷨��ʶ
ULONG		DevAuthAlgId;//�豸��֤ʹ�õķ��������㷨��ʶ
ULONG		TotalSpace;//�豸�ܿռ��С
ULONG		FreeSpace;//�û����ÿռ��С
ULONG		MaxECCBufferSize;//�ܹ�������ECC�������ݴ�С
ULONG		MaxBufferSize;//�ܹ������ķ���������Ӵ���������ݴ�С
BYTE  		Reserved[64];//������չ
}DEVINFO,*PDEVINFO;

/*�����붨��*/
#define  SAR_OK											0x00000000  //�ɹ�
#define  SAR_Fail										0x0A000001  //ʧ��
#define  SAR_UnknownErr									0x0A000002  //�쳣����
#define  SAR_NotSupportYetErr							0x0A000003  //��֧�ֵķ���
#define  SAR_FileErr									0x0A000004  //�ļ���������
#define  SAR_InvalidHandleErr							0x0A000005  //��Ч�ľ��
#define  SAR_InvalidParamErr							0x0A000006  //��Ч�Ĳ���
#define  SAR_ReadFileErr								0x0A000007  //���ļ�����
#define  SAR_WriteFileErr								0x0A000008  //д�ļ�����
#define  SAR_NameLenErr									0x0A000009  //���Ƴ��ȴ���
#define  SAR_KeyUsageErr								0x0A00000A  //��Կ��;����
#define  SAR_ModulusLenErr								0x0A00000B  //ģ�ĳ��ȴ���
#define  SAR_NotInitializeErr							0x0A00000C  //δ��ʼ��
#define  SAR_ObjErr										0x0A00000D  //�������
#define  SAR_MemoryErr									0x0A00000E  //�ڴ����
#define  SAR_TimeoutErr									0x0A00000F  //��ʱ
#define  SAR_IndataLenErr								0x0A000010  //�������ݳ��ȴ���
#define  SAR_IndataErr									0x0A000011  //�������ݴ���
#define  SAR_GenRandErr									0x0A000012  //�������������
#define  SAR_HashObjErr									0x0A000013  //HASH�����
#define  SAR_HashErr									0x0A000014  //HASH�������
#define  SAR_GenRsaKeyErr								0x0A000015  //����RSA��Կ��
#define  SAR_RsaModulusLenErr							0x0A000016  //RSA��Կģ������
#define  SAR_RsaEncErr									0x0A000018  //RSA���ܴ���
#define  SAR_RsaDecErr									0x0A000019  //RSA���ܴ���
#define  SAR_HashNotEqualErr							0x0A00001A  //HASHֵ�����
#define  SAR_KeyNotFountErr								0x0A00001B  //��Կδ����
#define  SAR_CertNotFountErr							0x0A00001C  //֤��δ����
#define  SAR_NotExportErr								0x0A00001D  //����δ����
#define  SAR_DecryptPadErr								0x0A00001E  //����ʱ����������
#define  SAR_MacLenErr									0x0A00001F  //MAC���ȴ���
#define  SAR_BUFFER_TOO_SMALL							0x0A000020  //����������
#define  SAR_KeyInfoTypeErr								0x0A000021  //��Կ���ʹ���
#define  sar_not_eventerr								0x0A000022  //���¼�����
#define  SAR_DEVICE_REMOVED								0x0A000023  //�豸���Ƴ�
#define  SAR_PIN_INCORRECT								0x0A000024  //PIN����ȷ
#define  SAR_PIN_LOCKED									0x0A000025  //PIN������
#define  SAR_PIN_INVALID								0x0A000026  //PIN��Ч
#define  SAR_PIN_LEN_RANGE								0x0A000027  //PIN���ȴ���
#define  SAR_USER_ALREADY_LOGGED_IN						0x0A000028  //�û��Ѿ���¼
#define  SAR_USER_PIN_NOT_INITIALIZED					0x0A000029  //û�г�ʼ���û�����
#define  SAR_USER_TYPE_INVALID							0x0A00002A  //PIN���ʹ���
#define  SAR_APPLICATION_NAME_INVALID					0x0A00002B  //Ӧ��������Ч
#define  SAR_APPLICATION_EXISTS							0x0A00002C  //Ӧ���Ѿ�����
#define  SAR_USER_NOT_LOGGED_IN							0x0A00002D  //�û�û�е�¼
#define  SAR_APPLICATION_NOT_EXISTS						0x0A00002E  //Ӧ�ò�����
#define  SAR_FILE_ALREADY_EXIST							0x0A00002F  //�ļ��Ѿ�����
#define  SAR_NO_ROOM									0x0A000030  //�ռ䲻��
#define  SAR_FILE_NOT_EXIST								0x0A000031  //�ļ�������
#define  SAR_REACH_MAX_CONTAINER_COUNT					0x0A000032  //�Ѵﵽ���ɹ���������
#define  SAR_REFERENCE_TO_DATA_INVALID					0x0A000033  //����������Ч
#define  SAR_CERTIFICATION_METHOD_LOCKED				0x0A000034  //��֤��������
#define  SAR_Lc_LENGTH_ERROR							0x0A000035  //���ȴ���
#define  SAR_CERTIFICATION_TIME1_ERROR					0x0A000036  //��֤ʧ�ܣ���ʣ1�����Ի���
#define  SAR_CERTIFICATION_TIME2_ERROR					0x0A000037  //��֤ʧ�ܣ���ʣ2�����Ի���
#define  SAR_CERTIFICATION_TIME3_ERROR					0x0A000038  //��֤ʧ�ܣ���ʣ3�����Ի���
#define  SAR_CERTIFICATION_TIME4_ERROR					0x0A000039  //��֤ʧ�ܣ���ʣ4�����Ի���
#define  SAR_SAFETY_STATE_DISSATISFY					0x0A000040  //��ȫ״̬������
#define  SAR_DAYA_INCOMPLETE_REPEAT						0x0A000041  //���и���������Ҫ�ϴ����ӿڲ����·��ͱ���ָ���ȡ��������
#define  SAR_SPECIFIED_APPLICATION_OPENED				0x0A000042  //ָ��Ӧ���Ѵ�
#define  SAR_DEVICE_NONSUPPORT_OPEN_MULTI_APPLICATION	0x0A000043  //���д򿪵�Ӧ�ã���ǰ�豸��֧��ͬʱ�򿪶��Ӧ��
#define  SAR_Lc_LENGTH_ERROR_LeMust000003				0x0A000044  //Lc���ȴ���LeӦ��Ϊ000003
#define  SAR_NO_APPLICATION_OPENED						0x0A000045  //û�д�Ӧ��
#define  SAR_CONTAINER_EXISTS							0x0A000046	//�������Ѵ���
#define	 SAR_CONTAINER_NOT_EXISTS						0x0A000047  //����������
#define  SAR_CONTAINER_ID_NOT_EXISTS					0x0A000048  //����ID������
#define  SAR_CONTAINER_KEY_NOT_EXISTS					0x0A000049  //������û�ж�Ӧ��Կ
#define  SAR_Certificate_NOT_EXISTS						0x0A000050  //ָ��֤�鲻����
#define  SAR_SUCCESS_BUT_VERIFY_ERROR					0x0A000051  //ִ�гɹ�����ǩʧ��
#define  SAR_ERROR_UIAIGID								0x0A000052  //������㷨��ʶ
#define  SAR_DEVICE_MUL					    			0x0A000053  //ֻ�ܲ�һ��KEY //sj-20190705-add
#define  SAR_INPUT_PARAM_ERR							0x0A000054  //�����������  //sj-20190705-add
#define  SAR_BCAE_NO_ROOM								0x0A000055  //�Գ��㷨���������м仺��������
#define  SAR_REFERENCED_SYM_KEY_NOT_EXISTS				0x0A000056  //���õĶԳ���Կ������
#define  SAR_USAGE_CONDITION_NO_SATISFIED   			0x0A000057  //ʹ������������
#define  SAR_SPECIFIED_CERT_TYPE_ERROR      			0x0A000058  //ָ����֤�����ʹ���
#define  SAR_FULL						    			0x0A000059  //�Ự��Կ��
#define  SAR_SIGN_FAIL                      			0x0A000060  //ǩ��ʧ��
#define  SAR_ENCRYPT_FAIL                   			0x0A000061  //SM2����ʧ��
#define  SAR_DECRYPT_FAIL                   			0x0A000062  //SM2����ʧ��
#define  SAR_SYM_ENCRYPT_FAIL               			0x0A000064  //�ԳƼ���ʧ��
#define  SAR_SYM_DECRYPT_FAIL               			0x0A000065  //�ԳƼ���ʧ��
#define  SM3_NO_INIT									0x0A000066	//sm3δ��ʼ��

/*��������*/
/*************************************************************
��������	��ȡ�豸��һЩ������Ϣ�������豸��ǩ��������Ϣ��֧�ֵ��㷨�ȡ�
����	hDev		[IN] �����豸ʱ���ص��豸�����
		pDevInfo	[OUT] �����豸��Ϣ��
����ֵ	SAR_OK��	�ɹ���
		������		�����롣
**************************************************************/
INT32 SKF_GetDevInfo (DEVHANDLE hDev, DEVINFO *pDevInfo);
/*************************************************************
��������	��õ�ǰϵͳ�е��豸�б���
����	bPresent	[IN] ΪTRUE��ʾȡ��ǰ�豸״̬Ϊ���ڵ��豸�б���ΪFALSE��ʾȡ��ǰ����֧�ֵ��豸�б���
	    szNameList	[OUT] �豸�����б�������ò���ΪNULL������pulSize��������Ҫ���ڴ�ռ��С��ÿ���豸�������Ե�����\0����������˫��\0����ʾ�б��Ľ�����
	    pulSize	    [IN��OUT] ����ʱ��ʾ�豸�����б��Ļ��������ȣ����ʱ��ʾszNameList��ռ�õĿռ��С��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/
INT32 SKF_EnumDev(BOOL bPresent, LPSTR szNameList, ULONG *pulSize);
/*************************************************************
��������	ͨ���豸���������豸�������豸�ľ����
����    szName	   [IN] �豸���ơ�
	    phDev	   [OUT] �����豸���������
����ֵ	SAR_OK��    �ɹ���
        ������		�����롣
**************************************************************/
INT32 SKF_ConnectDev (LPSTR szName, DEVHANDLE *phDev);
/*************************************************************
��������	�Ͽ�һ���Ѿ����ӵ��豸�����ͷž����
����	 hDev	    [IN] �����豸ʱ���ص��豸�����
����ֵ	 SAR_OK��	�ɹ���
         ������		�����롣
��ע	 ������豸�ѱ�����������Ӧ���Ƚ������豸���Ͽ����Ӳ�������Ӱ���豸��Ȩ��״̬��
**************************************************************/
INT32 SKF_DisConnectDev (DEVHANDLE hDev);
/*************************************************************
��������	����ָ�����ȵ��������
����	hDev	    [IN] �豸�����
	    pbRandom	[OUT]���ص��������
	    ulRandomLen	[IN] ��������ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/
INT32 SKF_GenRandom(DEVHANDLE hDev, BYTE *pbRandom,ULONG ulRandomLen);
/*************************************************************
��������	�豸��֤���豸��Ӧ�ó������֤��
����	hDev	    [IN] ����ʱ���ص��豸�����
	    pbAuthData	[IN] ��֤���ݡ�
	    ulLen   	[IN] ��֤���ݵĳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/
INT32 SKF_DevAuth(DEVHANDLE hDev, BYTE *pbAuthData, ULONG ulLen);
/*************************************************************
��������	�޸��豸��֤��Կ
����	hDev	    [IN] ����ʱ���ص��豸�����
	    pbKeyValue	[IN] Ҫ�޸ĵ��豸��֤��Կ��
	    ulKeyLen   	[IN] ��Կ�ĳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/
INT32 SKF_ChangeDevAuthKey(DEVHANDLE hDev, BYTE *pbKeyValue, ULONG ulKeyLen) ;
/*************************************************************
��������	У��PIN�롣У��ɹ��󣬻�����Ӧ��Ȩ�ޣ����PIN����󣬻᷵��PIN������Դ����������Դ���Ϊ0ʱ��ʾPIN���Ѿ�������
����	hApplication[IN] Ӧ�þ����
	    ulPINType   [IN] PIN���͡�
	    szPIN	    [IN] PINֵ��
	    pulRetryCount [OUT] �����󷵻ص����Դ�����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/
INT32 SKF_VerifyPIN (HAPPLICATION hApplication, ULONG  ulPINType, LPSTR szPIN, ULONG *pulRetryCount);
/*************************************************************
��������	��ȡPIN����Ϣ������������Դ�������ǰʣ�����Դ������Լ���ǰPIN���Ƿ�Ϊ����Ĭ��PIN�롣
����	hApplication	    [IN] Ӧ�þ����
	    ulPINType	        [IN] PIN���͡�
     	pulMaxRetryCount	[OUT] ������Դ�����
     	pulRemainRetryCount	[OUT] ��ǰʣ�����Դ�������Ϊ0ʱ��ʾ��������
	    pbDefaultPin	    [OUT] �Ƿ�Ϊ����Ĭ��PIN�롣
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/
INT32 SKF_GetPINInfo(HAPPLICATION hApplication, ULONG  ulPINType, ULONG *pulMaxRetryCount, 
					                        ULONG *pulRemainRetryCount, BOOL *pbDefaultPin);
/*************************************************************
��������	���øú��������޸�Administrator PIN��User PIN��ֵ��
            ���ԭPIN���������֤ʧ�ܣ��ú����᷵����ӦPIN���ʣ�����Դ�������ʣ�����Ϊ0ʱ����ʾPIN�Ѿ���������
����	hApplication    [IN] Ӧ�þ����
	    ulPINType	    [IN] PIN���ͣ���ΪADMIN_TYPE��USER_TYPE��
    	szOldPin	    [IN] ԭPINֵ��
     	szNewPin	    [IN] ��PINֵ��
	    pulRetryCount	[OUT] ���������Դ�����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/		
INT32 SKF_ChangePIN (HAPPLICATION hApplication, ULONG ulPINType, LPSTR szOldPin, LPSTR szNewPin, ULONG *pulRetryCount);
/*************************************************************
��������	���û���PIN��������ͨ�����øú����������û�PIN�롣
            �������û�PIN�뱻���ó���ֵ���û�PIN������Դ���Ҳ�ָ���ԭֵ��
����	hApplication	[IN] Ӧ�þ����
	    szAdminPIN	    [IN] ����ԱPIN�롣
	    szNewUserPIN	[IN] �µ��û�PIN�롣
	    pulRetryCount	[OUT] ����ԱPIN�����ʱ������ʣ�����Դ�����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	��֤�����ԱPIN���ܹ������û�PIN�룬��������Administrator PIN����ȷ�����Ѿ������������ʧ�ܣ�������Administrator PIN�����Դ�����
**************************************************************/		
INT32 SKF_UnblockPIN(HAPPLICATION hApplication, LPSTR szAdminPIN, LPSTR szNewUserPIN, ULONG *pulRetryCount);	
/*************************************************************
��������	���Ӧ�õ�ǰ�İ�ȫ״̬��
����   	hApplication	[IN] Ӧ�þ����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/	
INT32 SKF_ClearSecureState(HAPPLICATION hApplication);	
/*************************************************************
��������	����һ��Ӧ�á� 
����	hDev	                [IN] �����豸ʱ���ص��豸�����
	    szAppName	            [IN] Ӧ�����ơ�
	    szAdminPin	            [IN] ����ԱPIN��
	    dwAdminPinRetryCount	[IN] ����ԱPIN������Դ�����
	    szUserPin	            [IN] �û�PIN��
     	dwUserPinRetryCount	    [IN] �û�PIN������Դ�����
	    dwCreateFileRights	    [IN] �ڸ�Ӧ���´����ļ���������Ȩ�ޣ��μ�6.4.12Ȩ�����͡�Ϊ����Ȩ�޵Ļ�ֵ��
	    phApplication	        [OUT] Ӧ�õľ����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�豸Ȩ�ޡ�
**************************************************************/									
INT32 SKF_CreateApplication(DEVHANDLE hDev, LPSTR szAppName, 
							LPSTR szAdminPin, DWORD dwAdminPinRetryCount,
							LPSTR szUserPin, DWORD dwUserPinRetryCount,
							DWORD dwCreateFileRights, HAPPLICATION *phApplication);
/*************************************************************
��������	ö���豸�д��ڵ�����Ӧ�á�
����	hDev	     [IN] �����豸ʱ���ص��豸�����
	    szAppName	 [OUT] ����Ӧ�������б�, ����ò���Ϊ�գ�����pulSize��������Ҫ���ڴ�ռ��С��ÿ��Ӧ�õ������Ե�����\0����������˫��\0����ʾ�б��Ľ�����
	    pulSize      [IN��OUT] ����ʱ��ʾӦ�����ƵĻ��������ȣ����ʱ����szAppName��ռ�õĿռ��С��
����ֵ	SAR_OK��	 �ɹ���
        ������		 �����롣
**************************************************************/	
INT32 SKF_EnumApplication(DEVHANDLE hDev, LPSTR szAppName,ULONG *pulSize);
/*************************************************************
��������	��ָ����Ӧ�á�
����	hDev     	    [IN] �����豸ʱ���ص��豸�����
	    szAppName	    [IN] Ӧ�����ơ�
	    phApplication	[OUT] Ӧ�õľ����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/	
INT32 SKF_OpenApplication(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication);
/*************************************************************
��������	�ر�Ӧ�ò��ͷ�Ӧ�þ����
����	hApplication	[IN]Ӧ�þ����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	�˺�����Ӱ��Ӧ�ð�ȫ״̬��
**************************************************************/	
INT32 SKF_CloseApplication(HAPPLICATION hApplication);
/*************************************************************
��������	ɾ��ָ����Ӧ�á�
����	hDev	    [IN] �����豸ʱ���ص��豸�����
	    szAppName	[IN] Ӧ�����ơ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�豸Ȩ�ޡ�
**************************************************************/	
INT32 SKF_DeleteApplication(DEVHANDLE hDev, LPSTR szAppName);
/*************************************************************
��������	��Ӧ���½���ָ�����Ƶ��������������������
����	hApplication	[IN] Ӧ�þ����
	    szContainerName	[IN] ASCII�ַ�������ʾ���������������ƣ��������Ƶ���󳤶Ȳ��ܳ���64�ֽڡ�
	    phContainer	    [OUT] �������������������������
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�û�Ȩ�ޡ�
**************************************************************/	
INT32 SKF_CreateContainer (HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *phContainer);
/*************************************************************
��������	ö���豸�д��ڵ�����������
����	hApplication	[IN]       Ӧ�þ����
	    szContainerList	[OUT]      ���������б�������ò���ΪNULL������pulSize��������Ҫ���ڴ�ռ��С��ÿ���豸�������Ե�����\0����������˫��\0����ʾ�б��Ľ�����
	    pulSize	        [IN��OUT]  ����ʱ��ʾӦ�����ƵĻ��������ȣ����ʱ����szAppName��ռ�õĿռ��С��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�û�Ȩ�ޡ�
**************************************************************/	
INT32 SKF_EnumContainer(HAPPLICATION hApplication, LPSTR szContainerList, ULONG *pulSize);
/*************************************************************
��������	��ȡ���������
����	hApplication	[IN] Ӧ�þ����
	    szContainerName	[IN] ���������ơ�
	    phContainer  	[OUT] �������������ľ����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/	
INT32 SKF_OpenContainer(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer);
/*************************************************************
��������	�ر�������������ͷ�������������Դ��
����	hContainer	[IN] ���������
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/	
INT32 SKF_CloseContainer(HCONTAINER hContainer);
/*************************************************************
��������	��Ӧ����ɾ��ָ�����Ƶ��������ͷ�������ص���Դ��
����	hApplication	[IN] Ӧ�þ����
	    szContainerName	[IN] ָ��ɾ�����������ơ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�û�Ȩ�ޡ�
**************************************************************/	
INT32 SKF_DeleteContainer(HAPPLICATION hApplication, LPSTR szContainerName);
/*************************************************************
��������	��ȡ����������
����	hContainer	      [IN] ���������
	    pulContainerType  [OUT] ��õ��������͡�ָ��ָ���ֵΪ0��ʾδ������δ�������ͻ���Ϊ��������Ϊ1��ʾΪRSA������Ϊ2��ʾΪECC������
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/	
INT32 SKF_GetContainerType(HCONTAINER hContainer, ULONG *pulContainerType);
/*************************************************************
��������	�����ļ�ʱҪָ���ļ������ƣ���С���Լ��ļ��Ķ�дȨ�ޡ�
����	hApplication	[IN] Ӧ�þ����
	    szFileName	    [IN] �ļ����ƣ����Ȳ��ô���32���ֽڡ�
	    ulFileSize	    [IN] �ļ���С��
	    ulReadRights	[IN] �ļ���Ȩ�ޣ��μ�6.4.12 Ȩ�����͡���Ϊ����Ȩ�޵Ļ�ֵ��
	    ulWriteRights	[IN] �ļ�дȨ�ޣ��μ�6.4.12Ȩ�����͡���Ϊ����Ȩ�޵Ļ�ֵ��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	�����ļ���ҪӦ��ָ���Ĵ����ļ�Ȩ�ޡ�
**************************************************************/	
INT32 SKF_CreateFile(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulFileSize, ULONG ulReadRights, ULONG ulWriteRights);
/*************************************************************
��������	ö��һ��Ӧ���´��ڵ������ļ���
����	hApplication	[IN] Ӧ�þ����
	    szFileList	    [OUT] �����ļ������б����ò���Ϊ�գ���pulSize�����ļ���Ϣ����Ҫ�Ŀռ��С��ÿ���ļ������Ե�����\0����������˫��\0����ʾ�б��Ľ�����
	    pulSize	        [IN��OUT] ����ʱ��ʾ���ݻ������Ĵ�С�����ʱ��ʾʵ���ļ������б��ĳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/	
INT32 SKF_EnumFiles (HAPPLICATION hApplication, LPSTR szFileList, ULONG *pulSize);
/*************************************************************
��������	��ȡ�ļ���Ϣ����ȡӦ���ļ���������Ϣ�������ļ��Ĵ�С��Ȩ�޵ȡ�
����	hApplication	[IN] �ļ�����Ӧ�õľ����
     	szFileName	    [IN] �ļ����ơ�
	    pFileInfo	    [OUT] �ļ���Ϣ��ָ���ļ����Խṹ��ָ�롣
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
**************************************************************/	
INT32 SKF_GetFileInfo (HAPPLICATION hApplication, LPSTR szFileName, FILEATTRIBUTE *pFileInfo);
/*************************************************************
��������	��ȡ�ļ����ݡ�
����	hApplication	[IN] Ӧ�þ����
     	szFileName	    [IN] �ļ�����
	    ulOffset	    [IN] �ļ���ȡƫ��λ�á�
     	ulSize	        [IN] Ҫ��ȡ�ĳ��ȡ�
     	pbOutData	    [OUT] �������ݵĻ�������
     	pulOutLen	    [IN��OUT]����ʱ��ʾ�����Ļ�������С�����ʱ��ʾʵ�ʶ�ȡ���ص����ݴ�С��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����߱��Ը��ļ��Ķ�Ȩ�ޡ�
**************************************************************/	
INT32 SKF_ReadFile(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulOffset, ULONG ulSize, BYTE * pbOutData, ULONG *pulOutLen);
/*************************************************************
��������	д���ݵ��ļ��С�
����	hApplication	[IN] Ӧ�þ����
	    szFileName	    [IN] �ļ�����
	    ulOffset	    [IN] д���ļ���ƫ������
	    pbData	        [IN] д�����ݻ�������
	    ulSize      	[IN] д�����ݵĴ�С��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����߱����ļ���дȨ�ޡ�
**************************************************************/	
INT32 SKF_WriteFile (HAPPLICATION hApplication, LPSTR szFileName, ULONG  ulOffset, BYTE *pbData, ULONG ulSize);
/*************************************************************
��������	ɾ��ָ���ļ����ļ�ɾ�����ļ���д���������Ϣ����ʧ���ļ����豸�е�ռ�õĿռ佫���ͷš�
����	hApplication	[IN] Ҫɾ���ļ����ڵ�Ӧ�þ����
	    szFileName	    [IN] Ҫɾ���ļ������ơ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ��ɾ��һ���ļ�Ӧ���жԸ��ļ��Ĵ���Ȩ�ޡ�
************************************************************/
INT32 SKF_DeleteFile (HAPPLICATION hApplication, LPSTR szFileName);
/*************************************************************
��������	�������ڵ�������֤�顣
����	hContainer	[IN] ���������
	    bSignFlag	[IN] TRUE��ʾǩ��֤�飬FALSE��ʾ����֤�顣
     	pbCert	    [IN] ָ��֤�����ݻ�������
     	ulCertLen	[IN] ֤�鳤�ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_ImportCertificate(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG ulCertLen);
/*************************************************************
��������	�������ڵ�������֤�顣
����	hContainer	[IN] ���������
	    bSignFlag	[IN] TRUE��ʾǩ��֤�飬FALSE��ʾ����֤�顣
	    pbCert	    [OUT] ָ��֤�����ݻ�����������˲���ΪNULLʱ��pulCertLen��ʾ������������Ҫ�������ĳ��ȣ�����˲�����ΪNULLʱ����������֤�����ݡ�
	    pulCertLen	[IN/OUT] ����ʱ��ʾpbCert�������ĳ��ȣ����ʱ��ʾ֤�����ݵĳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_ExportCertificate(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG *pulCertLen);
/*************************************************************
��������	����ECCǩ����Կ�Բ����ǩ����Կ��
����	hContainer	[IN] ��Կ���������
	    ulAlgId	    [IN] �㷨��ʶ��ֻ֧��SGD_SM2_1�㷨��
	    pBlob	    [OUT] ����ECC��Կ���ݽṹ��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�û�Ȩ�ޡ�
************************************************************/
INT32 SKF_GenECCKeyPair (HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pBlob);
/*************************************************************
��������	���������е�ǩ����Կ���߼��ܹ�Կ��
����	hContainer	[IN] ��Կ���������
	    bSignFlag	[IN] TRUE��ʾ����ǩ����Կ��FALSE��ʾ�������ܹ�Կ��
     	pbBlob	    [OUT] ָ��RSA��Կ�ṹ��RSAPUBLICKEYBLOB������ECC��Կ�ṹ��ECCPUBLICKEYBLOB��������˲���ΪNULLʱ����pulBlobLen����pbBlob�ĳ��ȡ�
     	pulBlobLen	[IN��OUT] ����ʱ��ʾpbBlob�������ĳ��ȣ����ʱ��ʾ������Կ�ṹ�Ĵ�С��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_ExportPublicKey(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbBlob, ULONG* pulBlobLen);
/*************************************************************
��������	����ECC��˽Կ�ԡ�
����	hContainer	        [IN] ��Կ���������
	    pEnvelopedKeyBlob	[IN] �ܱ����ļ�����Կ�ԡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�û�Ȩ�ޡ�
************************************************************/
INT32 SKF_ImportECCKeyPair(HCONTAINER hContainer, PENVELOPEDKEYBLOB pEnvelopedKeyBlob);
/*************************************************************
��������	ECC����ǩ��������ECC�㷨��ָ��˽ԿhKey����ָ������pbData��������ǩ����ǩ����Ľ����ŵ�pSignature�С�
����	hContainer	[IN] ��Կ���������
	    pbData	    [IN] ��ǩ�������ݡ�
	    ulDataLen	[IN] ��ǩ�����ݳ��ȣ�����С����Կģ����
	    pSignature	[OUT] ǩ��ֵ��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�û�Ȩ�ޡ���������Ϊ��ǩ���ݵ��Ӵ�ֵ����ʹ��SM2�㷨ʱ������������Ϊ��ǩ���ݾ���SM2ǩ��Ԥ�����Ľ����Ԥ����������ѭ����Կ���������ʩӦ�ü�����ϵ SM2�㷨����ʹ�ù淶����
************************************************************/
INT32 SKF_ECCSignData(HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);
/*************************************************************
��������	��ECC��Կ�����ݽ�����ǩ��
����	hDev	        [IN] �豸�����
	    pECCPubKeyBlob	[IN] ECC��Կ���ݽṹ��
	    pbData	        [IN] ����֤ǩ�������ݡ�
     	ulDataLen	    [IN] ���ݳ��ȡ�
     	pSignature	    [IN] ����֤ǩ��ֵ��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	��������Ϊ��ǩ���ݵ��Ӵ�ֵ����ʹ��SM2�㷨ʱ������������Ϊ��ǩ���ݾ���SM2ǩ��Ԥ�����Ľ����Ԥ����������ѭ����Կ���������ʩӦ�ü�����ϵ SM2�㷨����ʹ�ù淶����
************************************************************/
INT32 SKF_ECCVerify(DEVHANDLE hDev , ECCPUBLICKEYBLOB* pECCPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);
/*************************************************************
��������	���ɻỰ��Կ�����ⲿ��Կ���ܵ�����
����	hContainer	    [IN] ���������
	    ulAlgId	        [IN] �Ự��Կ�㷨��ʶ��
	    pPubKey	        [IN] �ⲿ����Ĺ�Կ�ṹ��
	    pData	        [OUT] �Ự��Կ���ġ�
	    phSessionKey	[OUT] �Ự��Կ�����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_ECCExportSessionKey (HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pPubKey, PECCCIPHERBLOB pData, HANDLE *phSessionKey);
/*************************************************************
��������	ʹ���ⲿ�����ECC��Կ�������������������㲢��������
����	hDev	        [IN] �豸�����
	    pECCPubKeyBlob	[IN] ECC��Կ���ݽṹ��
	    pbPlainText	    [IN] �����ܵ��������ݡ�
    	ulPlainTextLen	[IN] �������������ݵĳ��ȡ�
	    pCipherText	    [OUT] �������ݡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_ExtECCEncrypt (DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbPlainText, ULONG ulPlainTextLen, PECCCIPHERBLOB pCipherText);
/*************************************************************
��������	ʹ���ⲿ�����ECC˽Կ�������������������㲢��������
����	hDev	        [IN] �豸�����
	    pECCPriKeyBlob	[IN] ECC˽Կ���ݽṹ��
	    pCipherText   	[IN] �����ܵ��������ݡ�
	    pbPlainText	    [OUT] �����������ݣ�����ò���ΪNULL������pulPlainTextLen�����������ݵ�ʵ�ʳ��ȡ�
	    pulPlainTextLen	[IN��OUT] ����ʱ��ʾpbPlainText�������ĳ��ȣ����ʱ��ʾ�������ݵ�ʵ�ʳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	�����������ڲ��Ժ͵��ԣ�����������ʵ�ʵ��������
************************************************************/
INT32 SKF_ExtECCDecrypt(DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, 
						 PECCCIPHERBLOB pCipherText, BYTE* pbPlainText, ULONG* pulPlainTextLen);
/*************************************************************
��������	ʹ���ⲿ�����ECC˽Կ������������ǩ�����㲢��������
����	hDev	        [IN] �豸�����
	    pECCPriKeyBlob	[IN] ECC˽Կ���ݽṹ��
	    pbData	        [IN] ��ǩ�����ݡ�
	    ulDataLen	    [IN] ��ǩ�����ݵĳ��ȡ�
	    pSignature	    [OUT]ǩ��ֵ��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	��������Ϊ��ǩ���ݵ��Ӵ�ֵ����ʹ��SM2�㷨ʱ������������Ϊ��ǩ���ݾ���SM2ǩ��Ԥ�����Ľ����Ԥ����������ѭ����Կ���������ʩӦ�ü�����ϵ SM2�㷨����ʹ�ù淶����
��ע	�����������ڲ��Ժ͵��ԣ�����������ʵ�ʵ��������
************************************************************/	 
INT32 SKF_ExtECCSign(DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
/*************************************************************
��������	�ⲿʹ�ô����ECC��Կ��ǩ����֤��
����	hDev	        [IN] �豸�����
	    pECCPubKeyBlob	[IN] ECC��Կ���ݽṹ��
	    pbData	        [IN] ����֤���ݡ�
	    ulDataLen	    [IN] ����֤���ݵĳ��ȡ�
	    pSignature	    [IN] ǩ��ֵ��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע 	��������Ϊ��ǩ���ݵ��Ӵ�ֵ����ʹ��SM2�㷨ʱ������������Ϊ��ǩ���ݾ���SM2ǩ��Ԥ�����Ľ����Ԥ����������ѭ����Կ���������ʩӦ�ü�����ϵ SM2�㷨����ʹ�ù淶����
************************************************************/
INT32 SKF_ExtECCVerify(DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
/*************************************************************
��������	����Ự��Կ���ģ�ʹ�������еļ���˽Կ���ܵõ��Ự��Կ��
����	hContainer	    [IN] ���������
	    ulAlgId	        [IN] �Ự��Կ�㷨��ʶ��
	    pbWrapedData	[IN] Ҫ����ĻỰ��Կ���ġ�������ΪECC����ʱ���˲���ΪECCCIPHERBLOB�������ݣ�������ΪRSA����ʱ���˲���ΪRSA��Կ���ܺ�����ݡ�
	    ulWrapedLen	    [IN] �Ự��Կ���ĳ��ȡ�
	    phKey	        [OUT] ���ػỰ��Կ�����
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	Ȩ��Ҫ����Ҫ�û�Ȩ�ޡ�
************************************************************/
INT32 SKF_ImportSessionKey (HCONTAINER hContainer, ULONG ulAlgId,ECCCIPHERBLOB *pbWrapedData,ULONG ulWrapedLen,HANDLE *phKey);
/*************************************************************
��������	���ݼ��ܳ�ʼ�����������ݼ��ܵ��㷨��ز�����
����	hKey	        [IN] ������Կ�����
	    EncryptParam	[IN] ���������㷨��ز�������ʼ��������ʼ�������ȡ���䷽��������ֵ��λ���ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_EncryptInit (HANDLE hKey,BLOCKCIPHERPARAM EncryptParam);
/*************************************************************
��������	��һ�������ݵļ��ܲ�������ָ��������Կ��ָ�����ݽ��м��ܣ������ܵ�����ֻ����һ�����飬���ܺ�����ı��浽ָ���Ļ������С�
            SKF_Encryptֻ�Ե����������ݽ��м��ܣ��ڵ���SKF_Encrypt֮ǰ���������SKF_EncryptInit��ʼ�����ܲ�����
			SKF_Encypt�ȼ����ȵ���SKF_EncryptUpdate�ٵ���SKF_EncryptFinal��
����	hKey 	        [IN] ������Կ�����
     	pbData	        [IN] ���������ݡ�
	    ulDataLen	    [IN] ���������ݳ��ȡ�
	    pbEncryptedData	[OUT] ���ܺ�����ݻ�����ָ�룬����ΪNULL�����ڻ�ü��ܺ����ݳ��ȡ�
	    pulEncryptedLen	[IN��OUT] ����ʱ��ʾ������ݻ��������ȣ����ʱ��ʾ�������ʵ�ʳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_Encrypt(HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
/*************************************************************
��������	����������ݵļ��ܲ�������ָ��������Կ��ָ�����ݽ��м��ܣ������ܵ����ݰ���������飬���ܺ�����ı��浽ָ���Ļ������С�
            SKF_EncryptUpdate�Զ���������ݽ��м��ܣ��ڵ���SKF_EncryptUpdate֮ǰ���������SKF_EncryptInit��ʼ�����ܲ�����
			�ڵ���SKF_EncryptUpdate֮�󣬱������SKF_EncryptFinal�������ܲ�����
����	hKey         	[IN] ������Կ�����
        pbData       	[IN] ���������ݡ�
	    ulDataLen	    [IN] ���������ݳ��ȡ�
	    pbEncryptedData	[OUT] ���ܺ�����ݻ�����ָ�롣
	    pulEncryptedLen	[OUT] ���ؼ��ܺ�����ݳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_EncryptUpdate(HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
/*************************************************************
��������	��������������ݵļ��ܣ�����ʣ����ܽ�����ȵ���SKF_EncryptInit��ʼ�����ܲ������ٵ���SKF_EncryptUpdate�Զ���������ݽ��м��ܣ�
            ������SKF_EncryptFinal��������������ݵļ��ܡ�
����	hKey             	[IN] ������Կ�����
	    pbEncyptedData	    [OUT] ���ܽ���Ļ�������
	    ulEncyptedDataLen	[OUT] ���ܽ���ĳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_EncryptFinal (HANDLE hKey, BYTE *pbEncryptedData, ULONG *ulEncryptedDataLen );
/*************************************************************
��������	���ݽ��ܳ�ʼ�������ý�����Կ��ز���������SKF_DecryptInit֮�󣬿��Ե���SKF_Decrypt�Ե����������ݽ��н��ܣ�
            Ҳ���Զ�ε���SKF_DecryptUpdate֮���ٵ���SKF_DecryptFinal��ɶԶ���������ݵĽ��ܡ�
����	hKey	         [IN] ������Կ�����
	    DecryptParam	 [IN] ���������㷨��ز�������ʼ��������ʼ�������ȡ���䷽��������ֵ��λ���ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_DecryptInit (HANDLE hKey, BLOCKCIPHERPARAM DecryptParam);
/*************************************************************
��������	�����������ݵĽ��ܲ�������ָ��������Կ��ָ�����ݽ��н��ܣ������ܵ�����ֻ����һ�����飬���ܺ�����ı��浽ָ���Ļ������С�
            SKF_Decryptֻ�Ե����������ݽ��н��ܣ��ڵ���SKF_Decrypt֮ǰ���������SKF_DecryptInit��ʼ�����ܲ�����
			SKF_Decypt�ȼ����ȵ���SKF_DecryptUpdate�ٵ���SKF_DecryptFinal��
����	hKey 	        [IN] ������Կ�����
	    pbEncryptedData	[IN] ���������ݡ�
	    ulEncryptedLen	[IN] ���������ݳ��ȡ�
	    pbData	        [OUT] ָ����ܺ�����ݻ�����ָ�룬��ΪNULLʱ�ɻ�ý��ܺ�����ݳ��ȡ�
	    pulDataLen	    [IN��OUT] ����ʱ��ʾ������ݻ��������ȣ����ʱ��ʾ�������ʵ�ʳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_Decrypt(HANDLE hKey, BYTE * pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen);
/*************************************************************
��������	����������ݵĽ��ܲ�������ָ��������Կ��ָ�����ݽ��н��ܣ������ܵ����ݰ���������飬���ܺ�����ı��浽ָ���Ļ������С�
            SKF_DecryptUpdate�Զ���������ݽ��н��ܣ��ڵ���SKF_DecryptUpdate֮ǰ���������SKF_DecryptInit��ʼ�����ܲ�����
			�ڵ���SKF_DecryptUpdate֮�󣬱������SKF_DecryptFinal�������ܲ�����
����	hKey          	[IN] ������Կ�����
	    pbEncryptedData	[IN] ���������ݡ�
	    ulEncryptedLen	[IN] ���������ݳ��ȡ�
	    pbData	        [OUT] ָ����ܺ�����ݻ�����ָ�롣
	    pulDataLen	    [IN��OUT] ����ʱ��ʾ������ݻ��������ȣ����ʱ��ʾ�������ʵ�ʳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_DecryptUpdate(HANDLE hKey, BYTE * pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen);
/*************************************************************
��������	��������������ݵĽ��ܡ��ȵ���SKF_DecryptInit��ʼ�����ܲ������ٵ���SKF_DecryptUpdate�Զ���������ݽ��н��ܣ�
            ������SKF_DecryptFinal��������������ݵĽ��ܡ�
����	hKey	            [IN] ������Կ�����
	    pbDecryptedData	    [OUT] ָ����ܽ���Ļ�����������˲���ΪNULLʱ����pulDecryptedDataLen���ؽ��ܽ���ĳ��ȡ�
	    pulDecryptedDataLen	[IN��OUT] ����ʱ��ʾpbDecryptedData�������ĳ��ȣ����ʱ��ʾ���ܽ���ĳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_DecryptFinal (HANDLE hKey, BYTE *pbDecryptedData, ULONG *pulDecryptedDataLen);
/*************************************************************
��������	��ʼ�������Ӵռ��������ָ�����������Ӵյ��㷨��
����	hDev	    [IN] �����豸ʱ���ص��豸�����
	    ulAlgID	    [IN] �����Ӵ��㷨��ʶ��
	    pPubKey	    [IN] ǩ���߹�Կ����ulAlgIDΪSGD_SM3ʱ��Ч��
	    pucID	    [IN] ǩ���ߵ�IDֵ����ulAlgIDΪSGD_SM3ʱ��Ч��
	    ulIDLen	    [IN] ǩ����ID�ĳ��ȣ���ulAlgIDΪSGD_SM3ʱ��Ч��
	    phHash	    [OUT] �����Ӵն�������
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	��ulAlgIDΪSGD_SM3��ulIDLen��Ϊ0�������pPubKey��pucID��Ч��ִ��SM2�㷨ǩ��Ԥ����1������
        ���������ѭ����Կ���������ʩӦ�ü�����ϵ SM2�㷨����ʹ�ù淶����
************************************************************/
INT32 SKF_DigestInit(DEVHANDLE hDev, ULONG ulAlgID,  ECCPUBLICKEYBLOB *pPubKey, unsigned char *pucID, ULONG ulIDLen, HANDLE *phHash);
/*************************************************************
��������	�Ե�һ�������Ϣ���������Ӵռ��㡣����SKF_Digest֮ǰ���������SKF_DigestInit��ʼ�������Ӵռ��������SKF_Digest�ȼ��ڶ�ε���SKF_DigestUpdate֮���ٵ���SKF_DigestFinal��
����	hHash	    [IN] �����Ӵն�������
	    pbData	    [IN] ָ����Ϣ���ݵĻ�������
	    ulDataLen	[IN] ��Ϣ���ݵĳ��ȡ�
	    pbHashData	[OUT] �����Ӵ����ݻ�����ָ�룬���˲���ΪNULLʱ����pulHashLen���������Ӵս���ĳ��ȡ�
     	pulHashLen	[IN��OUT] ����ʱ��ʾ������ݻ��������ȣ����ʱ��ʾ�������ʵ�ʳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_Digest (HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *pbHashData, ULONG *pulHashLen);
/*************************************************************
��������	�Զ���������Ϣ���������Ӵռ��㡣����SKF_DigestUpdate֮ǰ���������SKF_DigestInit��ʼ�������Ӵռ��������
            ����SKF_DigestUpdate֮�󣬱������SKF_DigestFinal���������Ӵռ��������
����	hHash	    [IN] �����Ӵն�������
	    pbData	    [IN] ָ����Ϣ���ݵĻ�������
	    ulDataLen	[IN] ��Ϣ���ݵĳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_DigestUpdate (HANDLE hHash, BYTE *pbData, ULONG  ulDataLen);
/*************************************************************
��������	�������������Ϣ�������Ӵռ���������������Ӵս�����浽ָ���Ļ�������
����	hHash	    [IN] �����Ӵն�������
	    pHashData	[OUT] ���ص������Ӵս��������ָ�룬����˲���NULLʱ����pulHashLen�����Ӵս���ĳ��ȡ�
	    pulHashLen	[IN��OUT] ����ʱ��ʾ�Ӵս���������ĳ��ȣ����ʱ��ʾ�����Ӵս���ĳ��ȡ�
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
��ע	SKF_DigestFinal��������SKF_DigestUpdate֮��
************************************************************/
INT32 SKF_DigestFinal (HANDLE hHash, BYTE *pHashData, ULONG  *pulHashLen);
/*************************************************************
��������	�رջỰ��Կ�������Ӵն�����Ϣ���������ECC��ԿЭ�̵Ⱦ����
����	hHandle	[IN] Ҫ�رյĶ�������
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_CloseHandle(HANDLE hHandle);
/*************************************************************
��������    ɾ���Ự��Կ
����	hkey	[IN] �Ự��Կ�������Ϊ0���������ǰ�Ự�ڵ�������Կ��
����ֵ	SAR_OK��	�ɹ���
        ������		�����롣
************************************************************/
INT32 SKF_EraseSessionKey(DEVHANDLE hKey);

INT32 SKF_SetSymmKey(DEVHANDLE hDev, BYTE* pbKey, ULONG ulAlgID, HANDLE* phKey);

#ifdef __cplusplus
}
#endif

#endif