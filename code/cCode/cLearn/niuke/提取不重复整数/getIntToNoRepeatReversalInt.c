#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
    int inData = 0;
    int flag = 0;
    int count = 0;
    int copyInData = 0;
    char midData[10] = {0};
    scanf("%d", &inData);
    copyInData = inData;
    while(copyInData) {
        for(int i = 0; i < count; i++) {
            if(copyInData%10 == midData[i]-0x30) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            midData[count] = copyInData%10 + 0x30;
            count++;
        }
        flag = 0;
        copyInData /= 10;
    }
    printf("midData = %s\n",midData);
    inData = atoi(midData);
    printf("%d\n",inData);
}