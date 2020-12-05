#include <iostream>
#include <vector>
 
int main()
{
    int x = 0, y = 0, z = 0;
    while (std::cin >> x >> y >> z)
    {
        //获取输入
        std::vector<std::vector<int> > a(x, std::vector<int>(y, 0));
        for (int i = 0; i < x; ++i)
        {
            for (int j = 0; j < y; ++j)
            {
                std::cin >> a[i][j];
            }
        }
        std::vector<std::vector<int> > b(y, std::vector<int>(z, 0));
        for (int i = 0; i < y; ++i)
        {
            for (int j = 0; j < z; ++j)
            {
                std::cin >> b[i][j];
            }
        }
 
        //计算输出
        for (int i = 0; i < x; ++i)
        {
            for (int j = 0; j < z; ++j)
            {
                int cij = 0;
                for (int k = 0; k < y; ++k)
                {
                    cij += a[i][k] * b[k][j];
                }
                std::cout << cij << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}