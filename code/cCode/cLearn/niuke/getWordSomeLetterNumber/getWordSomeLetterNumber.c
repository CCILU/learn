#include <stdio.h>
#include <string.h>
#define NULL ((void *)0)

int getWordSomeLetterNumber(char * inputString, char inputLetter) {
    long stringLen = strlen(inputString)-1;
    int count = 0;
    if(inputString == NULL) {
        return 0;
    }
    for(int i = 0; i < stringLen; i++) {
        if(inputString[i] == inputLetter || inputString[i] == inputLetter+32 || inputString[i] == inputLetter-32) {
            ++count;
        }
    }
    return count;
}
int main() {
    char inputString[5000] = {0};
    char inputLetter = 0;
    fgets(inputString, 5000, stdin);
    scanf("%c",&inputLetter);
    printf("%d\n", getWordSomeLetterNumber(inputString, inputLetter));
    return 0;
}