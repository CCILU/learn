#include <stdio.h>

int main() {
    int inData = 0;
    double outData1 = 0.0;
    double outData2 = 0.0;
    scanf("%d",&inData);
    outData1 = (double)inData;
    outData2 = (double)inData;
    printf("outData1 :%.6lf\n",outData1);
    for(int i = 0; i < 4; i++){
        outData2 /= (double)2;
        printf("outData2 :%.6lf\n",outData2);
        outData1 += outData2*2;
        printf("outData1 :%.6lf\n",outData1);
    }
    outData2 /= (double)2;
    //outData1 += outData2;
    printf("%.6lf\n",outData1);
    printf("%.6lf",outData2);
    return 0;
}