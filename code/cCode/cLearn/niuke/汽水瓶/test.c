#include <stdio.h>

int main() {
    int count = 0;
    int inNumber = 0;
    while(1) {
        scanf("%d",&inNumber);
        if(0 == inNumber) {
            return 0;
        }
        while(inNumber/3) {
            count += inNumber/3;
            inNumber = inNumber/3 + inNumber%3;
        }
        if(inNumber == 2) {
            count++;
        }
        printf("%d\n",count);
        count = 0;
    }
    return 0;
}