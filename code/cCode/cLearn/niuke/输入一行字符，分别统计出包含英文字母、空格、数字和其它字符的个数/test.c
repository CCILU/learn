#include <stdio.h>
#include <string.h>

int main() {
    while(1) {
        char inputStr[1001] = {0};
        int instrLen = 0;
        int out1 = 0;
        int out2 = 0;
        int out3 = 0;
        int out4 = 0;
        fgets(inputStr,1001,stdin);
        instrLen = strlen(inputStr)-1;
        if(instrLen <= 0)
            return 0;
        for(int i = 0; i < instrLen; i++) {
            if((inputStr[i] >= 'a' && inputStr[i] <= 'z') || (inputStr[i] >= 'A' && inputStr[i] <= 'Z')) {
                out1++;
            }
            else if(inputStr[i] == ' ') {
                out2++;
            }
            else if(inputStr[i] >= '0' && inputStr[i] <= '9') {
                out3++;
            }
            else {
                out4++;
            }
        }
        printf("%d\n",out1);
        printf("%d\n",out2);
        printf("%d\n",out3);
        printf("%d\n",out4);
    }
    return 0;
}