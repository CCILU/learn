#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    char inputString[100] = {0};
    int  inputLen = 0;
    long output = 0;
    while(1) {
        fgets(inputString, 100, stdin);
        inputLen = strlen(inputString)-1;
        if(0 >= inputLen)
        {
            return 0;
        }
        for(int i = 2,count = inputLen-1-2; i < inputLen; i++, count--) {
            if(inputString[i] >= 'A' && inputString[i] <= 'F') {
                output += pow(16,count)*(inputString[i]-'A'+10);
            }
            else if(inputString[i] >= 'a' && inputString[i] <= 'f') {
                output += pow(16,count)*(inputString[i]-'a'+10);
            }
            else if(inputString[i] >= '0' && inputString[i] <= '9') {
                output += pow(16,count)*(inputString[i]-0x30);
            }
        }
        printf("%ld\n",output);
        output = 0;
        memset(inputString, 0x00, 100);
    }
    return 0;
}