#include<stdio.h>
#include<string.h>

static char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//base64����
static int base64_encode(unsigned char* bin_data, int bin_size, char* base64_data)
{
    printf("  base64_encode start.\n");
    int i,j,k,blk_size,remain_size;
    unsigned char *p, left[3];
	if (bin_data == NULL) 
	{
		printf("  base64_encode bin_data == NULL");
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
    
    printf("  base64_encode end.\n");
	return 0;
}

//base64����
static int base64_decode(char* base64_data, unsigned char* bin_data, int* bin_size)
{
    printf("  base64_decode start.\n");
    
    int i,j,k,m,n,l;
    unsigned char four_bin[4];
    char four_char[4],c;
		
	if(base64_data == NULL) 
	{
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
	
    printf("  base64_decode end.\n");
	return 0;
}

//������ת16����
int AscToHex(unsigned char des[], unsigned char src[], int srclen)
{
    printf("  AscToHex start.\n");
    
    unsigned char ch1,ch2;
    int i;
    for(i=0;i<srclen;i++)
    {
        ch1 = (src[i]&0xF0)>>4;
        ch2 = src[i]&0x0F;

        ch1 += ((ch1>9)?0x37:0x30);
        ch2 += ((ch2>9)?0x37:0x30);

        des[i*2] = ch1;
        des[i*2+1] = ch2;
    }
    printf("  AscToHex end.\n");
    return 0;
}

//16����ת������
int HexToAsc(unsigned char* des, unsigned char* src ,int srclen)
{
    printf("  HexToAsc start.\n");

	unsigned char ch1,ch2;
	int i;
	if (srclen%2 !=0)
	{
		return 1;
	}
	for(i=0;i<srclen/2;i++)
	{
		ch1 = src[i*2];
		ch2 = src[i*2+1];

		(ch1>='a'&&ch1<='z')?(ch1-=32):ch1;
		(ch2>='a'&&ch2<='z')?(ch2-=32):ch2;

    if ((((ch1<=0x39)&&(ch1>=0x30))||((ch1 <=0x46)&&(ch1>=0x41))||((ch1 <=0x66)&&(ch1>=0x61)))
			&&(((ch2<=0x39)&&(ch2>=0x30))||((ch2 <=0x46)&&(ch2>=0x41))||((ch2 <=0x66)&&(ch2>=0x61))))
		{
			ch1 -= ((ch1>(9+0x30))?0x37:0x30);
			ch2 -= ((ch2>(9+0x30))?0x37:0x30);

			des[i]=(ch1<<4)|ch2;
		}
		else
		{
			return 2;
		}
	}
    printf("  HexToAsc end.\n");
	return 0;
}

int enc_dec_menu()
{
    printf("\n");
    printf("  **************************************\n");
	printf("  *   1-Asc_Hex        2-Hex_Asc       *\n");
	printf("  *   3-Asc_Base64     4-Base64_Asc    *\n");
	printf("  *   5-Hex_Base64     6-Base64_Hex    *\n");
    printf("  *   0) Exit                          *\n");
	printf("  **************************************\n");
    printf("\n");
    return 0;
}

int Asc_Hex(unsigned char *srcdata,int srcdataLen,unsigned char *desdata,int *desdataLen)
{
	AscToHex(desdata, srcdata, srcdataLen);
	*desdataLen=srcdataLen*2;
	
	return 0;
}

int Hex_Asc(unsigned char *srcdata,int srcdataLen,unsigned char *desdata,int *desdataLen)
{
	HexToAsc(desdata, srcdata, srcdataLen);
	*desdataLen=srcdataLen/2;
	return 0;
}
int Asc_Base64(unsigned char *srcdata,int srcdataLen,unsigned char *desdata,int *desdataLen)
{
	base64_encode(srcdata, srcdataLen, desdata);
	*desdataLen=strlen(desdata);
			
	return 0;
}
int Base64_Asc(unsigned char *srcdata,int srcdataLen,unsigned char *desdata,int *desdataLen)
{
	base64_decode(srcdata, desdata, &desdataLen);
			
	return 0;
}
int Hex_Base64(unsigned char *srcdata,int srcdataLen,unsigned char *desdata,int *desdataLen)
{
	unsigned char middata[10000]={0};
	int middataLen=0;
	
	HexToAsc(middata, srcdata, srcdataLen);
	middataLen=srcdataLen/2;
	printf("  middataLen: %d\n",middataLen);
	base64_encode(middata, middataLen, desdata);
	desdataLen=strlen(desdata);
	
	return 0;
}
int Base64_Hex(unsigned char *srcdata,int srcdataLen,unsigned char *desdata,int *desdataLen)
{
	unsigned char middata[10000]={0};
	int middataLen=0;
	
	base64_decode(srcdata, middata, &middataLen);
	printf("  middataLen: %d\n", middataLen);
	AscToHex(desdata, middata, middataLen);
	desdataLen=middataLen*2;
	
	return 0;
}

int encode_decode()
{
	enc_dec_menu();
	
	int i;
	
	printf("  please chose: ");
	scanf("   %d",&i);
	
	unsigned char srcdata[10000]={0};
	int srcdataLen=0;
	unsigned char desdata[10000]={0};
	int desdataLen=0;
	
	printf("  srcdata: ");
	scanf("%s",srcdata);
	srcdataLen=strlen(srcdata);
	printf("  srcdataLen: %d\n", srcdataLen);
	
	switch(i)
	{
		case 1:
			Hex_Base64(srcdata,srcdataLen,desdata,&desdataLen);
			break;
		case 2:
			Hex_Base64(srcdata,srcdataLen,desdata,&desdataLen);
			break;
		case 3:
			Hex_Base64(srcdata,srcdataLen,desdata,&desdataLen);
			break;
		case 4:
			Hex_Base64(srcdata,srcdataLen,desdata,&desdataLen);
			break;
		case 5:
			Hex_Base64(srcdata,srcdataLen,desdata,&desdataLen);
			break;
		case 6:
			Hex_Base64(srcdata,srcdataLen,desdata,&desdataLen);
			break;
		case 0:
			return 0;
		case -1:
			exit(0);
		default:
			printf("  choose error!\n");
			break;
	}
	printf("  desdata[%d]: %s\n", desdataLen, desdata);
	return 0;
}
