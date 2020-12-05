#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    int n;
    while(cin >> n){
        while(n--){
            string str;
            cin >> str;
            int i,temp[26]={0},k=26,res=0;
            for(i=0;i<str.length();i++){
                if(str[i]>='a' && str[i]<='z')
                    temp[str[i]-'a']++;
                else
                    temp[str[i]-'A']++;
            }
            sort(temp,temp+26);
            for(i=25;i>=0;i--){
                res+=temp[i]*k--;
            }
            cout << res << endl;
        }
    }
    return 0;
}