#include <stdio.h>
#include <string.h>
int main(void)
{
    int i,j;
    char str1[1000];
    char str2[1000];
    int count1 = 0, count2 = 0;
 
    #pragma warning(suppress : 4996)//用VS写的，需要压制警告
    gets(str1);
    //scanf("%s", &str1);
    int length = strlen(str1);
    for (i = 0; i < length; i++)
    {
        if (str1[length - 1 - i] != ' ')
        {
            count1++;
        }
        else
        {
            for (j = 0; j < count1; j++)
            {
                str2[count2 + j] = str1[length - i + j];
            }
            str2[count2 + j] = ' ';
            count2 += (count1+ 1);
            count1 = 0;
        }
    }
    for (j = 0; j < count1; j++)
    {
        str2[count2 + j] = str1[length - i + j];
    }
    str2[count2 + j] = ' ';
    count2 += (count1 + 1);
    count1 = 0;
    str2[i] = 0;
    printf("%s", str2);
    return 0;
}