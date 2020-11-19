#include "pem2der.h"


static char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


int PrintHex(char* itemName,void* pInData,unsigned int dataLength,unsigned int rowCount)
{
		int i,j;
		unsigned char *sourceData = (unsigned char *)pInData;

		if((sourceData == NULL) || (rowCount == 0) || (dataLength == 0))
				return -1;

		if(itemName != NULL)
				printf("%s[%d]:\n",itemName,dataLength);

		for(i=0;i<(int)(dataLength/rowCount);i++)
		{
				printf("%08x  ",i*rowCount);
				for(j=0;j<(int)rowCount;j++)
				{
						printf("%02x ",*(sourceData+i*rowCount+j));
				}
				printf("\n");
		}
		if (!(dataLength%rowCount))
				return 0;

		printf("%08x  ",(dataLength/rowCount)*rowCount);
		for(j=0;j<(int)(dataLength%rowCount);j++)
		{
				printf("%02x ",*(sourceData+(dataLength/rowCount)*rowCount+j));
		}
		printf("\n");
		return 0;
}

void Hex2Byte(unsigned char *src, int src_len, unsigned char *dest)
{
		int i=0;
		int a,b;
		for(i=0; i<src_len; ++i)
		{
				if(src[i] >='0' && src[i] <='9')
						a = src[i] - '0';
				else if(src[i] >='a'&& src[i] <='f')
						a = src[i] - 'a'+10;
				else if(src[i] >='A'&& src[i] <='F')
						a = src[i] - 'A'+10;
				if(i%2 ==0)
						b = a*16;
				else if(i%2 ==1)
				{
						dest[i/2] = b+a;
				}
		}
}
int base64_encode(unsigned char* bin_data, unsigned long bin_size, char* base64_data)
{
		unsigned long i,j,k,blk_size,remain_size;
		unsigned char *p, left[3];


		if (bin_data == NULL)
		{
				printf(" base64_encode bin_data == NULL \n");
				return -1;
		}

		blk_size = bin_size / 3;
		remain_size = bin_size % 3;

		p = bin_data;
		j = 0;

		for(i=0;i<blk_size;i++)
		{
				k = (p[0] & 0xFC) >> 2;
				base64_data[j++] = base64_table[k];
				k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
				base64_data[j++] = base64_table[k];
				k = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
				base64_data[j++] = base64_table[k];
				k = p[2] & 0x3F;
				base64_data[j++] = base64_table[k];
				p += 3;
		}

		switch(remain_size)
		{
				case 0:
						break;

				case 1:
						left[0] = p[0];
						left[1] = 0;
						p = left;

						k = (p[0] & 0xFC) >> 2;
						base64_data[j++] = base64_table[k];
						k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
						base64_data[j++] = base64_table[k];

						base64_data[j++] = '=';
						base64_data[j++] = '=';
						break;

				case 2:
						left[0] = p[0];
						left[1] = p[1];
						left[2] = 0;
						p = left;

						k = (p[0] & 0xFC) >> 2;
						base64_data[j++] = base64_table[k];
						k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
						base64_data[j++] = base64_table[k];
						k = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
						base64_data[j++] = base64_table[k];
						base64_data[j++] = '=';
						break;

				default:
						break;
		}

		base64_data[j] = 0;

		return 0;
}


/*base64解码函数*/
int base64_decode(char* base64_data, unsigned char* bin_data, unsigned long* bin_size)
{
	unsigned long i,j,k,m,n,l;
	unsigned char four_bin[4];
	char four_char[4],c;


	if(base64_data == NULL)
	{
			printf(" base64_decode bin_data == NULL \n");
			return -1;
	}


	j = strlen(base64_data);
	i = 0;
	l = 0;
	for(;;)
	{
		if((i+4) > j)
		{
			break;
		}

		for(k=0;k<4;k++)
		{
			if(i == j)
			{
				break;
			}

			c = base64_data[i++];
			if((c == '+') || (c == '/') || (c == '=') ||
						((c >= '0') && (c <= '9')) ||
						((c >= 'A') && (c <= 'Z')) ||
						((c >= 'a') && (c <= 'z')))
			{
				four_char[k] = c;
			}
		}
		if(k != 4)
		{
			printf(" base64_decode k != 4 \n");
			return -1;
		}

		n = 0;
		for(k=0;k<4;k++)
		{
			if(four_char[k] != '=')
			{
				for(m=0;m<64;m++)
				{
					if(base64_table[m] == four_char[k])
					{
						four_bin[k] = (unsigned char)m;
						break;
					}
				}
			}
			else
			{
				n++;
			}
		}

		switch(n)
		{
			case 0:
				bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
				bin_data[l++] = (four_bin[1] << 4) | (four_bin[2] >> 2);
				bin_data[l++] = (four_bin[2] << 6) | four_bin[3];
				break;
			case 1:
				bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
				bin_data[l++] = (four_bin[1] << 4) | (four_bin[2] >> 2);
				break;
			case 2:
				bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
				break;
			default:
				break;
		}
		if(n != 0)
		{
			break;
		}
	}


	*bin_size = l;
	return 0;
}
int HexToAsc(unsigned char* src ,int srclen, unsigned char* des)
{
	unsigned char ch1,ch2;
	int i;
	if (srclen%2 !=0) {
		return 1;
	}
	for(i=0;i<srclen/2;i++) {
		ch1 = src[i*2];
		ch2 = src[i*2+1];

		(ch1>='a'&&ch1<='z')?(ch1-=32):ch1;
		(ch2>='a'&&ch2<='z')?(ch2-=32):ch2;

    if ((((ch1<=0x39)&&(ch1>=0x30))||((ch1 <=0x46)&&(ch1>=0x41))||((ch1 <=0x66)&&(ch1>=0x61)))
			&&(((ch2<=0x39)&&(ch2>=0x30))||((ch2 <=0x46)&&(ch2>=0x41))||((ch2 <=0x66)&&(ch2>=0x61)))) {
			ch1 -= ((ch1>(9+0x30))?0x37:0x30);
			ch2 -= ((ch2>(9+0x30))?0x37:0x30);

			des[i]=(ch1<<4)|ch2;
		}
		else {
			return 2;
		}
	}
	return 0;
}
