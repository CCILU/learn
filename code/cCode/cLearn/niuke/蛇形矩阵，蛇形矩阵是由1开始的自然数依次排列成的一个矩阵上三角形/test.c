#include <stdio.h>

int main() {
    int number = 0;
    int num = 0;
    int lastnum = 0;
   //Sn = n(a1+an)/2                       
   while(scanf("%d",&number) != EOF) {
        if(0 == number) {
            return 0;
        }
        for(int i = 1; i <= number; i++) {
            for(int j = 1; j < number-i+1; j++) {
                num = ((j+i-1)*(j+i-1)+(j+i-1))/2- (i-1);
                printf("%d ",num);
            }
            lastnum = (number*number+number)/2 - (i-1);
            printf("%d\n", lastnum);
        }
    }
    return 0;
}