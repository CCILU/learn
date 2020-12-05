#include <stdio.h>
int main(void)
{
    double a,b,i;
    scanf("%lf",&a);
    if(a >= 0) {
        for(i = 0;i <= a;i+=0.05)
        {
            if((i * i *i) > a)
                break;     
        }
        printf("%.1lf\r\n",i);
        return 0;
    }
    else {
        for(i = 0;i <= a;i-=0.05)
        {
            if((i * i *i) < -a)
                break;     
        }
        printf("%.1lf\r\n",-i);
        return 0;
    }
    
}