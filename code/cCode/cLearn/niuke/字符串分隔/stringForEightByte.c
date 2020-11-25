#include <stdio.h>
#include <string.h>

int main() {
    char inputString[110] = {0};
    int inputLen = 0;
    while(1){
        fgets(inputString, 102, stdin);
        inputLen = strlen((char *)inputString)-1;
        if(0 >= inputLen) {
            return 0;
        }
        memset(inputString+inputLen, '0', 110-inputLen);
        if(inputLen%8 == 0) {
            inputLen /= 8;
        }
        else {
            inputLen = inputLen/8+1;
        }
        for(int i = 0; i < inputLen; i++) {
            for(int j = 0; j < 8; j++) {
                printf("%c",inputString[i*8+j]);
            }
            printf("\n");
        }
        memset(inputString, 0, 110);
    }
    return 0;
}