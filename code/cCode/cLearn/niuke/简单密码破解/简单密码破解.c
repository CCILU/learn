#include <stdio.h>
#include <string.h>

int main() {
    char inputStr[101] = {0};
    char outStr[101] = {0};
    int inputLen = 0;
    
    fgets(inputStr, 101, stdin);
    inputLen = strlen(inputStr)-1;
    if(inputLen <= 0) {
        return 0;
    }
    for(int i = 0; i < inputLen; i++) {
        if(inputStr[i] >= '0' && inputStr[i] <= '9') {
            outStr[i] = inputStr[i];
        }
        else if(inputStr[i] >= 'a' && inputStr[i] <= 'c') {
            outStr[i] = '2';
        }
        else if(inputStr[i] >= 'd' && inputStr[i] <= 'f') {
            outStr[i] = '3';
        }
        else if(inputStr[i] >= 'g' && inputStr[i] <= 'i') {
            outStr[i] = '4';
        }
        else if(inputStr[i] >= 'j' && inputStr[i] <= 'l') {
            outStr[i] = '5';
        }
        else if(inputStr[i] >= 'm' && inputStr[i] <= 'o') {
            outStr[i] = '6';
        }
        else if(inputStr[i] >= 'p' && inputStr[i] <= 's') {
            outStr[i] = '7';
        }
        else if(inputStr[i] >= 't' && inputStr[i] <= 'v') {
            outStr[i] = '8';
        }
        else if(inputStr[i] >= 'w' && inputStr[i] <= 'z') {
            outStr[i] = '9';
        }
        else if(inputStr[i] >= 'A' && inputStr[i] <= 'Z') {
            if(inputStr[i] == 'Z') {
                outStr[i] = 'a';
            }
            else {
                outStr[i] = inputStr[i] + 32+1;
            }
        }
    }
    printf("%s", outStr);
    return 0;
}