#include <iostream>
using namespace std;
 
bool isPrime(int n)
{
    int i=0;
    for(i=2;i*i<=n;i++)
    {
        if(n%i==0) return false;
    }
    return true;
}
 
int main()
{
    int n;
    while(cin>>n)
    {
        int left=n/2;
        int right=n/2;
        while(left>=2)
        {
            if(isPrime(left)&&isPrime(right))
            {
                cout<<left<<endl;
                cout<<right<<endl;
                break;
            }
            else
            {
                left--;
                right++;
            }
        }
    }
    return 0;
}