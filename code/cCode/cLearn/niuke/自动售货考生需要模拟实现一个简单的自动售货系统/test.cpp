#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
#include<sstream>
using namespace std;
int number=0,num,balance;
char hyphen,colon;
unordered_map<string,int>  goods={{"A1",0},{"A2",0},{"A3",0},{"A4",0},{"A5",0},{"A6",0}};
map<int,int>               money={{1,0},{2,0},{5,0},{10,0}};
unordered_map<string,int>  mp={{"A1",2},{"A2",3},{"A3",4},{"A4",5},{"A5",8},{"A6",6}};
bool rule(const pair<string,int> p1,const pair<string,int> p2){
    if(p1.second>p2.second)      return true;
    else if(p1.second<p2.second) return false;
    else{
        return p1.first<p2.first;
    }
}
vector<string> split(string str,char c){
    vector<string> vec;
    int idx;
    str+="#";
    while(str.size()!=1){
        idx=str.find(c);
        vec.emplace_back(str.substr(0,idx));
        str=str.substr(idx+1);
    }
    return vec;
}
void initialization(string str){
    stringstream ss(str);
    //Goods Initialization
    number=0;
    ss>>hyphen;
    ss>>num>>hyphen;  goods["A1"]=num;  number+=num;
    ss>>num>>hyphen;  goods["A2"]=num;  number+=num;
    ss>>num>>hyphen;  goods["A3"]=num;  number+=num;
    ss>>num>>hyphen;  goods["A4"]=num;  number+=num;
    ss>>num>>hyphen;  goods["A5"]=num;  number+=num;
    ss>>num;          goods["A6"]=num;  number+=num;
    //Money Initialization
    ss>>num>>hyphen;  money[1]=num;
    ss>>num>>hyphen;  money[2]=num;
    ss>>num>>hyphen;  money[5]=num;
    ss>>num;          money[10]=num;
    cout<<"S001:Initialization is successful"<<endl;
}
void pay(string str){
    num=stoi(str.substr(2));
    if(money.find(num)==money.end())           cout<<"E002:Denomination error"<<endl;
    else if(num>2&&money[1]*1+money[2]*2<num)  cout<<"E003:Change is not enough, pay fail"<<endl;
    else if(num>10)                            cout<<"E004:Pay the balance is beyond the scope biggest"<<endl;
    else if(number==0)                         cout<<"E005:All the goods sold out"<<endl;
    else{
        balance+=num;
        money[num]++;
        cout<<"S002:Pay success,balance="<<balance<<endl;
    }
}
void buy(string str){
    string good_name=str.substr(2);
    if(goods.find(good_name)==goods.end())    cout<<"E006:Goods does not exist"<<endl;
    else if(goods[good_name]==0)              cout<<"E007:The goods sold out"<<endl;
    else if(mp[good_name]>balance)            cout<<"E008:Lack of balance"<<endl;
    else{
        balance-=mp[good_name];
        goods[good_name]--;
        number--;
        cout<<"S003:Buy success,balance="<<balance<<endl;
    }
}
void refund(){
    if(balance==0) cout<<"E009:Work failure";
    //The rule of refound.
    else{
        int y1=0,y2=0,y5=0,y10=0;
        int origin=balance;
        if(balance>=10&&money[10]>0) {
            if(balance<=10*money[10]){
                y10=balance/10;
                money[10]-=y10;
                balance-=(10*y10);
            }else{
                y10=money[10];
                money[10]=0;
                balance-=(10*y10);
            }
        }
        if(balance>=5&&money[5]>0){
            if(balance<=5*money[5]){
                y5=balance/5;
                money[5]-=y5;
                balance-=(5*y5);
            }else{
                y5=money[5];
                money[5]=0;
                balance-=(5*y5);
            }
        }
        if(balance>=2&&money[2]>0){
            if(balance<=2*money[2]){
                y2=balance/2;
                money[2]-=y2;
                balance-=(2*y2);
            }else{
                y2=money[2];
                money[2]=0;
                balance-=(2*y2);
            }
        }
        if(balance>=1&&money[1]>0){
            if(balance<=money[1]){
                y1=balance;
                money[1]-=y1;
                balance-=y1;
            }else{
                y1=money[1];
                money[1]=0;
                balance-=y1;
            }
        }
        //If lack of change, try the best to refund more
        if(balance!=0&&y5>0&&((money[2]+y2)*2>=origin-10*y10)){
            balance+=(5*y5+2*y2+y1);
            money[5]+=y5; y5=0;
            money[2]+=y2; y2=0;
            money[1]+=y1; y1=0;
            y2=balance/2;
            money[2]-=y2;
            balance-=(2*y2);
        }
        cout<<"1 yuan coin number="<<y1<<endl;
        cout<<"2 yuan coin number="<<y2<<endl;
        cout<<"5 yuan coin number="<<y5<<endl;
        cout<<"10 yuan coin number="<<y10<<endl;
    }
}
void querry(string str){
            if(str=="0"){
                vector<pair<string,int>> dic;
                pair<string,int> p1("A1",goods["A1"]);
                dic.emplace_back(p1);
                pair<string,int> p2("A2",goods["A2"]);
                dic.emplace_back(p2);
                pair<string,int> p3("A3",goods["A3"]);
                dic.emplace_back(p3);
                pair<string,int> p4("A4",goods["A4"]);
                dic.emplace_back(p4);
                pair<string,int> p5("A5",goods["A5"]);
                dic.emplace_back(p5);
                pair<string,int> p6("A6",goods["A6"]);
                dic.emplace_back(p6);
                sort(dic.begin(),dic.end(),rule);
               for(int i=0;i<6;i++)
                   cout<<dic[i].first<<" "<<mp[dic[i].first]<<" "<<dic[i].second<<endl;
            }
            else if(str=="1"){
                for(auto m=money.begin();m!=money.end();m++)
                    cout<<m->first<<" yuan coin number="<<m->second<<endl;
            }
            else cout<<"E010:Parameter error";
}
int main(){
    string str;
    while(getline(cin,str)){
        number=0;
        balance=0;
        vector<string> vec_str=split(str,';');
        for(auto v:vec_str){
            if(v[0]=='r')       initialization(v);
            else if(v[0]=='p')  pay(v);
            else if(v[0]=='b')  buy(v);
            else if(v[0]=='c')  refund();
            else if(v[0]=='q')  querry(v.substr(2));
        }
    }
    return 0;
}