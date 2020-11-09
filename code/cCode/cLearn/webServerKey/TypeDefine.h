#ifndef __TYPEDEFINE_H__
#define __TYPEDEFINE_H__


#define DA_API				//API Function's Flag
#define IN					//Parameter's IN Flag
#define OUT					//Parameter's OUT Flag

#define ULONG _UINT64
#define INT64 long
#define LONG  long
#define BOOL  char

#define	DEBUG					0

typedef void                    T_VOID;
typedef unsigned char           UINT8;
typedef unsigned short          UINT16;
typedef unsigned int			UINT32;
typedef unsigned int            ULONG;

typedef char                    INT8;
typedef short                   INT16;
typedef int						INT32;


typedef UINT8					UCHAR;
typedef UINT8					BYTE;
typedef UINT8					CHAR;
typedef INT16					SHORT;
typedef UINT16					USHORT;

typedef UINT16					WORD;
typedef ULONG					DWORD;
typedef UINT32					FLAGS;
typedef CHAR *					LPSTR;

typedef    int				    HANDLE;
typedef HANDLE					DEVHANDLE;
typedef HANDLE					HAPPLICATION;
typedef HANDLE					HCONTAINER;

#define	FALSE			     	0
#define	TRUE					1


#define ChkDR(expr) {\
            dr = (expr);\
            if ( (T_RESULT)(dr)<0 )\
            {\
                goto ErrorExit;\
            }\
        }
        
#define ChkBOOL(fExpr,err){\
            if (!(fExpr))\
            {\
                dr = (err);\
                goto ErrorExit;\
            }\
        }



#endif
