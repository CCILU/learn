#include <stdio.h>
#include <string.h>

int main() {
    int tab[1000][1000] = {0};
    char inStr1[1000] = {0};
    char inStr2[1000] = {0};
    while(1) {
        memset(inStr1, 0x00, 1000);
        memset(inStr2, 0x00, 1000);
        fgets(inStr1,1000,stdin);
        fgets(inStr2,1000,stdin);
        int count1 = 0;
        int count2 = 0;
        int maxLen = 0;
        int wordsFlag = 0;
        count1 = strlen(inStr1)-1;
        count2 = strlen(inStr2)-1;
        if(count1 <= 0 || count2 <= 0) {
            return 0;
        }
        if(count1 > count2) {
            char temp[1000] = {0};
            strcpy(temp, inStr1);
            strcpy(inStr1, inStr2);
            strcpy(inStr2, temp);
            int tempInt = count1;
            count1 = count2;
            count2 = tempInt;
        }
        for(int i = 0; i < count1; i++) {
            for(int j = 0; j < count2; j++) {
                if(inStr1[i] == inStr2[j]) {
                    tab[i+1][j+1] = tab[i][j] + 1;
                    if(maxLen < tab[i+1][j+1]) {
                        maxLen = tab[i+1][j+1];
                        wordsFlag = i;
                    }
                }
                else {
                    tab[i+1][j+1] = 0;
                }
            }
        }
        char out[1000] = {0};
        memset(out, 0x00, 1000);
        strncpy(out, &inStr1[wordsFlag-maxLen+1], maxLen);
        printf("%s\n",out);
    }
    return 0;
}