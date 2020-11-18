#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "SM3.h"

const int T[64]={0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519,
                0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519, 0x79cc4519,
                0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a,
                0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a,
                0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a,
                0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a,
                0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a,
                0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a, 0x7a879d8a};

#define FF1(x, y, z)  ((x) ^ (y) ^ (z))
#define FF2(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define GG1(x, y, z)  ((x) ^ (y) ^ (z))
#define GG2(x, y, z) (((x) & (y)) | ((~x) & (z)))

#define Cyclic_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define  P0(x)  ((x) ^ (Cyclic_LEFT(x, 9)) ^ (Cyclic_LEFT(x, 17)))
#define  P1(x)  ((x) ^ (Cyclic_LEFT(x, 15)) ^ (Cyclic_LEFT(x, 23)))

void SM3Transform (unsigned int *, unsigned char *);
void MessageExtend(unsigned char *buffer, unsigned int *W0, unsigned int *W1);
static void Encode PROTO_LIST  ((unsigned char *, UINT4 *, unsigned int));
static void Decode PROTO_LIST  ((UINT4 *, unsigned char *, unsigned int));
static void SM3memcpy PROTO_LIST  ((POINTER, POINTER, unsigned int));
static void SM3memset PROTO_LIST  ((POINTER, int, unsigned int));
static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


int SM3_Reset(SM3Context *context) {
	context->count[0] = context->count[1] = 0;


  context->state[0] = 0x7380166f;
  context->state[1] = 0x4914b2b9;
  context->state[2] = 0x172442d7;
  context->state[3] = 0xda8a0600;
  context->state[4] = 0xa96f30bc;
  context->state[5] = 0x163138aa;
  context->state[6] = 0xe38dee4d;
  context->state[7] = 0xb0fb0e4e;

  return 0;
}

int SM3_Input (SM3Context *context, unsigned char *input, unsigned int inputLen) {
  unsigned int i, index, partLen;

  index = (unsigned int)((context->count[1] >> 3) & 0x3F);
  if ((context->count[1] += ((UINT4)inputLen << 3))
      < ((UINT4)inputLen << 3))
      context->count[0]++;
      context->count[0] += ((UINT4)inputLen >> 29);
  partLen = 64 - index;
  if (inputLen >= partLen) {
      SM3memcpy
        ((POINTER)&context->buffer[index], (POINTER)input, partLen);
      SM3Transform (context->state, context->buffer);
    for (i = partLen; i + 63 < inputLen; i += 64)
      SM3Transform (context->state, &input[i]);
    index = 0;
  }
  else
    i = 0;
  SM3memcpy
    ((POINTER)&context->buffer[index], (POINTER)&input[i],
      inputLen-i);
  return 0;
}

int SM3_Result(SM3Context *context, unsigned char digest[32]) {
	unsigned char bits[8];
  unsigned int index, padLen;
  Encode (bits, context->count, 8);
  index = (unsigned int)((context->count[1] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  SM3_Input (context, PADDING, padLen);
  SM3_Input (context, bits, 8);
  Encode (digest, context->state, 32);
  SM3memset ((POINTER)context, 0, sizeof (*context));
  return 0;
}

void SM3Transform(UINT4 *state, unsigned char *buffer) {
  int i;
  UINT4  SS1,SS2,TT1,TT2,SS;
  UINT4  W0[68];
  UINT4  W1[64];
  unsigned int  intMsg[16];
  UINT4  A = state[0], B = state[1], C = state[2], D = state[3],
        E = state[4], F = state[5], G = state[6], H = state[7];
  Decode (intMsg, buffer, 64);
  MessageExtend((unsigned char *)intMsg, W0, W1);
  for (i = 0; i< 64; i++) {

    SS = Cyclic_LEFT(A, 12) + E + Cyclic_LEFT(T[i], i & 0x1f);
          SS1 = Cyclic_LEFT(SS, 7);
    SS2 = SS1 ^ Cyclic_LEFT(A, 12);
    if (i >= 0 && i <= 15) {
        TT1 = FF1(A, B, C)+D+SS2+W1[i];
        TT2 = GG1(E, F, G)+H+SS1+W0[i];
    }
    else{
        TT1 = FF2(A, B, C)+D+SS2+W1[i];
        TT2 = GG2(E, F, G)+H+SS1+W0[i];
    }
    D = C;
    C = Cyclic_LEFT(B, 9);
    B = A;
    A = TT1;
    H = G;
    G = Cyclic_LEFT(F, 19);
    F = E;
    E = P0(TT2);

  }
  state[0] ^= A;
  state[1] ^= B;
  state[2] ^= C;
  state[3] ^= D;
  state[4] ^= E;
  state[5] ^= F;
  state[6] ^= G;
  state[7] ^= H;
}

void MessageExtend(unsigned char *buffer, unsigned int *W0, unsigned int *W1) {
  int i,j;
  unsigned int W;
  for (i = 0; i < 16; i++)
  SM3memcpy((POINTER)(W0+i), &buffer[i*4], 4);
  for (i = 16; i < 68; i++) {
    W = (W0[i-16]) ^ (W0[i-9]) ^ (Cyclic_LEFT((W0[i-3]), (15)));
    W = P1(W);
    W0[i] = (W) ^ (Cyclic_LEFT(W0[i-13], 7)) ^ (W0[i-6]);
  }
  for (j = 0; j < 64; j++) {
    W1[j] = W0[j] ^ W0[j+4];
  }
}

static void Encode (unsigned char *output, UINT4 *input, unsigned int len) {
  unsigned int i, j;
  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j+3] = (unsigned char)(input[i] & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

static void Decode (UINT4 *output, unsigned char *input, unsigned int len) {
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((UINT4)input[j+3]) | (((UINT4)input[j+2]) << 8) |
    (((UINT4)input[j+1]) << 16) | (((UINT4)input[j]) << 24);
}

static void SM3memcpy(POINTER output, POINTER input, unsigned int len) {
  unsigned int i;
  for (i = 0; i < len; i++)
    output[i] = input[i];
}

static void SM3memset(POINTER output, int value, unsigned int len) {
  unsigned int i;
  for (i = 0; i < len; i++)
    ((char *)output)[i] = (char)value;
}

int SM3_Hash(unsigned char* input,unsigned int inputlen,unsigned char* digest) {
	int ret;
	SM3Context* context = NULL;
	context = (SM3Context*)malloc(sizeof(SM3Context));
	if(context == NULL) {
		return -1;
	}
	ret = SM3_Reset(context);
	if(ret != 0) {
		return -2;
	}
	ret = SM3_Input(context,input, inputlen);
	if(ret != 0) {
		return -3;
	}

	ret = SM3_Result(context, digest);
	if(ret != 0) {
		return -4;
	}
	if(context)
		free(context);
	return 0;
}
