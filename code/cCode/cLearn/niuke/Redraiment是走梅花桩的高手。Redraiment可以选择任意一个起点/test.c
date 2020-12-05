#include <stdlib.h>
#include <stdio.h>
 
int main()
{
    int n;
    while(scanf("%d", &n) != EOF)
    {
        int arr[300] = {0}, dp[300] = {0};
        for(int i=0; i<n; i++)
        {
            scanf("%d", &arr[i]);
        }
        dp[0] = 1;
        int maxans = 1;
        for(int i=1; i<n; i++)
        {
            int maxval = 0;
            for(int j=0; j<i; j++)
            {
                if(arr[i] > arr[j])
                    maxval = (maxval > dp[j]) ? maxval : dp[j];
            }
            dp[i] = maxval + 1;
            maxans = (maxans > dp[i]) ? maxans : dp[i];
        }
        printf("%d\n", maxans);
    }
    return 0;
}