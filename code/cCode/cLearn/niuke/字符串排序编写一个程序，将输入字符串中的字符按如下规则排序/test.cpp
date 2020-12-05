#include <iostream>
using namespace std;
bool isChar(char ch){
    return (ch>='a'&&ch<='z') || (ch>='A' && ch <='Z');
}
int toInt(char ch){
 
    return ch>='A'&&ch <='Z'?ch-'A':ch-'a';
}
int main() {
    string str;
    while (getline(cin, str)){
        int lastSwap;
        int next, temp;
        for(int j=str.size()-1;j>0;j=lastSwap){
            lastSwap = 0;
            for(int i=0; i<j;i++){
                if(isChar(str[i])){
                    next = i+1;
                    while (next<=j && !isChar(str[next])){
                        next++;
                    }
 
                    if(isChar(str[next]) && toInt(str[i])>toInt(str[next])){
                       temp = str[next];
                       str[next] = str[i];
                       str[i] = temp;
                       lastSwap = i;
                    }
                }
            }
        }
 
        cout << str << endl;
    }
    return 0;
}