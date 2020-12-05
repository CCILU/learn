#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number[4] = {0};
int result = 0;

void sort(int point, int n, int array[])
{
    int temp = 0;	
    temp = array[point];
    array[point] = array[n];
    array[n] = temp;
}

void find(int secondIndex, int calValue, int array[])
{
    int flag = 0;
    if((secondIndex == 4)&&(calValue==24))
    {
        result=1;
    }
    if(secondIndex>=4)
        return;
    for(flag=0; flag<4; flag++) {
        switch(flag) {
            case 0:
                find(secondIndex+1, calValue+array[secondIndex], array);
                break;
            case 1:
                if(calValue-array[secondIndex]>=0)
                {
                    find(secondIndex+1, calValue-array[secondIndex], array);
                }
                else
                {
                    find(secondIndex+1, array[secondIndex]-calValue, array);
                }
                break;
            case 2:
                find(secondIndex+1, calValue*array[secondIndex], array);
                break;
            case 3:
                if(calValue%array[secondIndex] == 0)
                {
                    find(secondIndex+1, calValue/array[secondIndex], array);
                }
                else if(array[secondIndex]%calValue == 0)
                {
                    find(secondIndex+1, array[secondIndex]/calValue, array);
                }
    
                break;
        }
    }

}

int main() {
    while(scanf("%d%d%d%d",&number[0],&number[1],&number[2],&number[3])>0) {
        int point=0, n=0;
        for(point=0; point<4; point++) {
            for(n=0; n<4; n++) {
                sort(point, n, number);
                find(1, number[0], number);
            }
        }
    
        if(result) {
            printf("true\n");
            result = 0;
        }
        else {
            printf("false\n");
        }
    }
} 