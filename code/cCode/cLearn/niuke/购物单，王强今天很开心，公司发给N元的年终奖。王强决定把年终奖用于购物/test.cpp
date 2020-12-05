#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
class goods
{
public:
    int _v = 0;//价格
    int _p = 0;//用处不大,主要用_w
    int _q = 0;//父亲
    int _w = 0;//_v * _p
    vector<goods> _sub;//儿子容器
    vector<goods> _cho;//每一个主件可以选择的情况，附件为空
    goods() = default;
    goods(int v, int p, int q) : _v(v), _p(p), _q(q), _w(v* p) {}//构造函数
    goods operator+(goods& sub)//重载加法运算符
    {
        goods g;
        //计算
        g._v = this->_v + sub._v;
        g._w = this->_w + sub._w;
        //复制
        g._p = this->_p;
        g._q = this->_q;
        g._sub = this->_sub;
        g._cho = this->_cho;
        return g;
    }
};
//记录选择的过程，后续输出已经被注释掉了
void tracegoods(vector<int>& f, vector<vector<int>>& dp, vector<goods>& man)
{
    int i = dp.size() - 1, j = dp[0].size() - 1;
    for (; i > 0; --i)
    {
        if (dp[i][j] != dp[i - 1][j])
        {
            f[i] = dp[i][j] - dp[i - 1][j];
            j -= man[i]._v;
        }
        else
        {
            f[i] = 0;
        }
    }
 
    f[0] = (dp[0][j] == 0) ? 0 : dp[0][j];
}
//主函数
int main()
{
    int n = 0, m = 0;
    while (cin >> n && cin >> m)
    {
        int v;
        int p;
        int q;
        int count = 0;
        map<int, goods> all;//所有商品
        vector<goods> man;//主件
        //1读入所有商品
        while (++count <= m)
        {
            cin >> v;
            cin >> p;
            cin >> q;
            all[count] = goods(v, p, q);
        }
        //2将附件添加到主件的容器内
        for (auto g : all)
        {
            int fath = g.second._q;
            if (fath != 0)
            {
                all[fath]._sub.push_back(g.second);
            }
        }
        //3构建主件和附件的组合,加入到man
        for (auto g : all)
        {
            auto& zhu = g.second;
            if (zhu._q == 0)
            {
                auto& cho = zhu._cho;
                if (zhu._sub.size() == 2)
                {
                    cho.push_back(zhu);
                    cho.push_back(zhu + zhu._sub[0]);
                    cho.push_back(zhu + zhu._sub[1]);
                    cho.push_back((zhu + zhu._sub[0]) + zhu._sub[1]);
                }
                else if (zhu._sub.size() == 1)
                {
                    cho.push_back(zhu);
                    cho.push_back(zhu + zhu._sub[0]);
                }
                else//没有附件
                {
                    cho.push_back(zhu);
                }
                man.push_back(zhu);
            }
        }
        //动态规划，01背包，未优化
        vector<vector<int>> dp(man.size(), vector<int>(n + 1, 0));
        //4初值
        int k = 0, j = man[0]._cho[k]._v;
        while (k < man[0]._cho.size() - 1)
        {
            while (j >= man[0]._cho[k]._v && j < man[0]._cho[k + 1]._v && j <= n)
            {
                dp[0][j] = man[0]._cho[k]._w;
                j++;
            }
            k++;
        }
        while (j <= n)
        {
            dp[0][j] = man[0]._cho[k]._w;
            j++;
        }
        //5多重背包规划
        for (int i = 1; i < man.size(); ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                for (int k = 0; k < man[i]._cho.size(); k++)//每一种主件的多个选择
                {
                    if (j >= man[i]._cho[k]._v)
                    {
                        dp[i][j] = max(dp[i][j], dp[i - 1][j - man[i]._cho[k]._v] + man[i]._cho[k]._w);
                    }
 
                }
            }
        }
        //输出
        cout << dp[man.size() - 1][n] << endl;
    }
    return 0;
}