#include <stdio.h>
#include <string.h>

int main() {
    int inputCount = 0;
    char inputStr[1000][100] = {0};
    char rebbishData[100] = {0};
        scanf("%d",&inputCount);
        if(0 >= inputCount)
            return 0;
        gets(rebbishData);
        for(int i = 0; i < inputCount; i++) {
            fgets(inputStr+i, 100, stdin);
            for(int j = 0; j < i; j++) {
                if(strcmp(inputStr[i], inputStr[j]) < 0) {
                    char temp[100] = {0};
                    strcpy(temp, inputStr[i]);
                    strcpy(inputStr[i],inputStr[j]);
                    strcpy(inputStr[j],temp);
                }
            }
        }
        for(int i = 0; i < inputCount; i++){
            printf("%s",inputStr+i);
        }
    return 0;
}
/*
9
cap
to
cat
card
two
too
up
boat
boot
*/
