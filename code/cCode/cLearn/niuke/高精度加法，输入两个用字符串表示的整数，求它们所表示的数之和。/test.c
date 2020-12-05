#include <stdio.h>

int main()
{
    char str1[1000];
    while(scanf("%s",str1)!=EOF){
        char str2[1000];
        scanf("%s",str2);
        int len1 = strlen(str1);
        int a1[1000] = {0};
        int j = 0;
        for(int i=len1-1;i>=0;i--){
            a1[i] = str1[j] - '0';//a7=1 a6=2 a5=3 a4=4 a3=5 a2=6 a1=7 a0=8
            j++;
        }
        int len2 = strlen(str2);
        int a2[1000] = {0};
        j = 0;
        for(int i=len2-1;i>=0;i--){//b0=1;
            a2[i] = str2[j] - '0';
            j++;
        }
        int max = 0;
        int str3[1000] = {0};
        max = len1>len2?len1:len2;//max = 8
        int RtL;
        for(RtL=0;RtL<max;RtL++)
        {
            str3[RtL] += a1[RtL] + a2[RtL];
            if(str3[RtL] >= 10)
            {
                str3[RtL] = str3[RtL] % 10;
                str3[RtL+1] = 1;
            }
        }
        if(str3[RtL] != 0) 
            max++;	
        for(int i=max-1;i>=0;i--) {
            printf("%d",str3[i]);
        }
        printf("\n");
    }
    return 0;
}