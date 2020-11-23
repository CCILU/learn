#include <stdio.h>

int main() {
    int inputLen = 0;
    int inputData[100][2] = {0};
    scanf("%d", &inputLen);
    for(int i = 0;i < inputLen; i++) {
        scanf("%d %d",&(inputData[i][0]),&(inputData[i][1]));
    }
}