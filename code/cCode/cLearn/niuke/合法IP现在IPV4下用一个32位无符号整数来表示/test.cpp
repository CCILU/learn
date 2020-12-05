#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    string s;
    while(cin >> s){
        int n=s.size();vector<int> v;bool isValid=true;
        int num_i=count(s.begin(),s.end(),'.');
        if(num_i!=3)
            cout << "NO" <<endl;
        for(int i=0;i<4;i++){
            int index=s.find('.');
            v.push_back(stoi(s.substr(0,index)));
            s=s.substr(index+1);
        }
        for(int i=0;i<v.size();i++){
            if(v[i]<0 || v[i]>255)
                isValid=false;
        }
        if(isValid)
            cout << "YES" <<endl;
        else
            cout << "NO" <<endl;
    }
}