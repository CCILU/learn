#ifndef _SM3_H_
#define _SM3_H_ 1

#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned char *POINTER;
typedef unsigned short int UINT2;
typedef unsigned int UINT4;


/* SM3 context. */
typedef struct {
	UINT4 state[8];                                   /* state (ABCDEFGH) */
	UINT4 count[2];                                   /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                         /* input buffer */
} SM3Context;


int SM3_Reset(SM3Context *);
int SM3_Input(SM3Context *, unsigned char *, unsigned int);
int SM3_Result(SM3Context *,unsigned char [64]);
int SM3_Hash(unsigned char* input,unsigned int inputlen,unsigned char* digest);

#ifdef __cplusplus
}
#endif

#endif
