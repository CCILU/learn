#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    int num;
    while (cin >> str >> num)
    {
        int temp = num-1;
        while (temp >= 0 && str[temp] < 0)
            temp--;
        if ((num - temp) % 2 == 0)
            num--;
        cout << str.substr(0, num) << endl;
    }
    return 0;
}