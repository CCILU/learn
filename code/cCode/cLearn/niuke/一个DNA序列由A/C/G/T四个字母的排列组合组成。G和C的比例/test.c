#include<stdio.h>
 
int main(void){
    char cin[5000];
    while(scanf("%s", &cin) != EOF){
        int n;
        scanf("%d", &n);
        int num = 0, m = 0, pp = 0;
        for(int i=0; cin[i]!='\0'; i++){
            if(cin[i]=='G' || cin[i]=='C')
                num += 1;
            if(i>=n)
                if(cin[i-n]=='G' || cin[i-n]=='C')
                    num -= 1;
            if(num>m){
                pp = i - n + 1 > 0 ? i - n + 1 : 0;
                m = num;
            }
        }
        cin[pp+n] = '\0';
        printf("%s\n", &cin[pp]);
    }
}