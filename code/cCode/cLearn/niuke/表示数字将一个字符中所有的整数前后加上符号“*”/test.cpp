#include <iostream>
 
using namespace std;
 
int main(){
    string a;
    while(cin>>a){
        string cache="";
        for(int i=0;i<a.size();i++){
            if(a[i]>='0'&&a[i]<='9'){
                cache+=a[i];
            }else{
                if(cache==""){
                    cout<<a[i];
                }else{
                    cout<<"*"<<cache<<"*"<<a[i];
                    cache="";
                }
            }
        }
        if(cache!=""){
            cout<<"*"<<cache<<"*";
        }
        cout<<"\n";
    }
}