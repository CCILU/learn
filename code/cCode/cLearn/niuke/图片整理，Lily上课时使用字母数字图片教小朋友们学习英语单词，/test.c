#include <stdio.h>
#include <string.h>

int main() {
    while(1) {
        char inputStr[1025] = {0};
        int  inputLen = 0;
        fgets(inputStr, 1025, stdin);
        inputLen = strlen(inputStr) - 1;
        if(inputLen <= 0) {
            return 0;
        }
        for(int i = 0; i < inputLen; i++) {
            for(int j = 0; j < i; j++) {
                if(inputStr[i] < inputStr[j]) {
                    char temp = inputStr[i];
                    inputStr[i] = inputStr[j];
                    inputStr[j] = temp;
                }
            }
        }
        printf("%s",inputStr);
    }
    return 0;
}