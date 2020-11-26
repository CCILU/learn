#include <stdio.h>

int main() {
    int inputLen = 0;
    int inputData[1000][2] = {0};
    int midData[1][2] = {0};
    for(int i = 0;i < 1000; i++) {
        inputData[i][0] = -1;
    }
    scanf("%d", &inputLen);
    for(int i = 0;i < inputLen; i++) {
        scanf("%d %d",&(midData[0][0]),&(midData[0][1]));
        inputData[midData[0][0]][1] += midData[0][1];
        inputData[midData[0][0]][0] = midData[0][0];
    }
    for(int i = 0;i < 1000; i++) {
        if(inputData[i][0] != -1) {
            printf("%d %d\n", inputData[i][0], inputData[i][1]);
        }
    }
    return 0;
}