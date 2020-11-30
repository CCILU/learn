#include <stdio.h>
#include <string.h>

int main() {
    while(1) {
        char inputStr[1001] = {0};
        int inputLen = 0;
        fgets(inputStr, 1001, stdin);
        inputLen = strlen(inputStr)-1;
        if(inputLen <= 0) {
            return 0;
        }
        for(int i = 0; i < inputLen; i++) {
            if((inputStr[i] <= 'Z' && inputStr[i] >= 'A') || (inputStr[i] <= 'z' && inputStr[i] >= 'a')) {
                for(int j = 0; j < i; j++) {
                    if((inputStr[j] <= 'Z' && inputStr[j] >= 'A') || (inputStr[j] <= 'z' && inputStr[j] >= 'a')) {
                        if((inputStr[i]-inputStr[j] > 0) || (inputStr[i]+32-inputStr[j] > 0) || (inputStr[i]-32-inputStr[j] > 0)) {
                            char temp = inputStr[i];
                            inputStr[i] = inputStr[j];
                            inputStr[j] = temp;
                        }
                    }
                }
            }
        }
        printf("%s",inputStr);
    }
}