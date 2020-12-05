#include <stdlib.h>
#include <stdio.h>
 
int main()
{
    char str[500];
    while(scanf("%s", str) != EOF)
    {
        int len=strlen(str);
        int hash_table[128] = {0};
        for(int i=0; i<len; i++)
        {
            hash_table[str[i]]++;
        }
        int flag=0;
        for(int i=0; i<len; i++)
        {
            if(hash_table[str[i]] == 1)
            {
                printf("%c\n", str[i]);
                flag = 1;
                break;
            }
        }
        if(!flag) printf("-1\n");
    }
    return 0;
}