#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;
#define pii pair<int, int>
#define pll pair<ll, ll>
#define mp make_pair
#define faster_cin_cout ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(0)
 
template <typename T>
inline void read(T &x) {char ch=getchar(); int f=1; x=0; while(!isdigit(ch)){if(ch=='-')f *= -1; ch=getchar();} while(isdigit(ch)) {x = (x<<1) + (x<<3) + (ch^48); ch=getchar();} x*=f;}
ll qpow(ll x, ll y) { ll a=1, b=x; while(y){if(y&0x1) a*=b; b*=b; y>>=1;} return a;}
 
int main(void)
{
#ifndef ONLINE_JUDGE
    ifstream cin("in.txt");
#endif
    //faster_cin_cout;
 
    int n;
    string rule;
    while(cin >> n >> rule) {
 
        int cur = 1;
 
        if(n <= 4) {
            for(int i = 0; i < rule.size(); i++) {
                if(rule[i] == 'U') {
                    if(cur == 1) cur = n;
                    else cur--;
                } else if(rule[i] == 'D') {
                    if(cur == n) cur = 1;
                    else cur++;
                }
            }
            for(int i = 1; i <= n; i++) {
                if(i < n) cout << i << " ";
                else cout << i << endl;
            }
            cout << cur << endl;
            continue;
        }
 
        vector<int> win(5, 0);
        for(int i = 1; i <= 4; i++) win[i] = i;
 
        for(int i = 0; i < rule.size(); i++) {
            if(rule[i] == 'U') {
                if(cur == 1) {
                    // 特殊向上翻页
                    if(win[cur] == 1) {
                        for(int i = 1; i <= 4; i++) win[i] = n - 4 + i;
                        // 目前在第 4 页
                        cur = 4;
                    } else {
                        // 正常向上翻页
                        for(int i = 1; i <= 4; i++) win[i]--;
                        // 当前选中页不动
                    }
                } else {
                    // 当前选中页上移
                    cur--;
                }
            } else if(rule[i] == 'D') {
                if(cur == 4) {
                    // 特殊向下翻页
                    if(win[cur] == n) {
                        for(int i = 1; i <= 4; i++) win[i] = i;
                        // 目前在第 1 页
                        cur = 1;
                    } else {
                        // 正常向下翻页
                        for(int i = 1; i <= 4; i++) win[i]++;
                        // 当前选中页不动
                    }
                } else {
                    // 当前选中页下移动
                    cur++;
                }
            }
        }
        for(int i = 1; i <= 4; i++) {
            if(i < 4) cout << win[i] << " ";
            else cout << win[i] << endl;
        }
        cout << win[cur] << endl;
    }
 
    return 0;
}