#include <stdio.h>

int getZ(int input) {
    if(0 == input%2) {
        printf("2 ");
        input /= 2;
    }
    else if(0 == input%3) {
        printf("3 ");
        input /= 3;
    }
    else if(0 == input%5) {
        printf("5 ");
        input /= 5;
    }
    else if(0 == input%7) {
        printf("7 ");
        input /= 7;
    }
    else {
        int i = 11;
        for(i; i <= input; i+=2) {
            if(0 == input%i)
                break;
        }
        printf("%d ",i);
        input /= i;
    }
    return input;
}

int main() {
    int input = 0;
    scanf("%d",&input);
    if(input < 2) {
        return 0;
    }
    while(input != 1) {
        input = getZ(input);
    }
    return 0;
}