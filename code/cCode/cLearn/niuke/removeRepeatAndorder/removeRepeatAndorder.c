#include <stdio.h>
#include <stdlib.h>

int *removeRepeatAndorder(int *numberData, int numberLen, int *outDataLen){
    int *midData = (int*)malloc(numberLen);
    int count = 0;
    for(int i = 0; i < numberLen; i++) {
        int flag = 1;
        for(int j = 0; j < count; j++) {
            if(numberData[i] == midData[j]) {
                flag = 0;
                break;
            }
        }
        if(flag) {
            midData[count] = numberData[i];
            count++;
        }
    }
    for(int i = 0; i < count-1; i++) {
        for(int j = 0; j < count-i-1; j++) {
            if(midData[j] > midData[j+1]) {
                int temp = midData[j];
                midData[j] = midData[j+1];
                midData[j+1] = temp;
            }
        }
    }
    *outDataLen = count;
    return midData;
}
void deletData(int *midData) {
    free(midData);
}

int main() {
    int count = 0;
    int numberLen = 0;
    int outDataLen = 0;
    int numberData[1000] = {0};
    int *p = NULL;
    while(1) {
        scanf("%d",&count);
        if(count <= 0) {
            break;
        }
        for(int i = 0; i < count; i++) {
            scanf("%d",&(numberData[numberLen]));
            numberLen++;
           // printf("numberLen = %d\n",numberLen);
        }
    }
    p = removeRepeatAndorder(numberData, numberLen, &outDataLen);
    for(int i = 0; i < outDataLen; i++) {
        printf("%d\n",p[i]);
    }
    deletData(p);
    return 0;
}