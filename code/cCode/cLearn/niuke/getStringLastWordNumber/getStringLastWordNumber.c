#include <stdio.h>
#include <string.h>
//#define NULL ((void*)0)

int getStringLastWordNumber(char *inputString) {
    int           countData = 0;
    long i = strlen((char *)inputString)-1-1;
    printf("inputString = %s",inputString);
    if(inputString == NULL) {
        return 0;
    }
    while(inputString[i] != ' ' && i >= 0) {
        countData++;
        --i;
    }
    return countData;
}

int main() {
    char inputString[5001] = {0};
    //gets(inputString);
    fgets(inputString, 5000, stdin);
    printf("%d \n",inputString[strlen(inputString)-1]);
    printf("%d \n",getStringLastWordNumber(inputString));
    return 0;
}