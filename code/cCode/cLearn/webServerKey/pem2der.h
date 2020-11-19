#ifndef _DTLOG_H_
#define _DTLOG_H_
#include<stdio.h>
#include<string.h>
#include<errno.h>

int base64_encode(unsigned char* bin_data, unsigned long bin_size, char* base64_data);
int base64_decode(char* base64_data, unsigned char* bin_data, unsigned long* bin_size);
void Hex2Byte(unsigned char *src, int src_len, unsigned char *dest);
int PrintHex(char* itemName,void* pInData,unsigned int dataLength,unsigned int rowCount);
int HexToAsc(unsigned char* src ,int srclen, unsigned char* des);

#endif