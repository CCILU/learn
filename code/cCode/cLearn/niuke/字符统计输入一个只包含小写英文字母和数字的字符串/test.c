#include<stdio.h>
#include<string.h>
typedef struct {//创造结构体将字符数据联系起来
    int num;//字符ASCII码
    int count;//字符数量
}s;
int main(void)
{
    char str[1000] = { 0 };
    while (gets(str)) {
        s c[1000] = { 0 };
        int len = strlen(str);
        for (int i = 0; i < 128; i++) {//将结构体下标和num值匹配
            c[i].num = i;
        }
        for (int i = 0; i < len; i++) {//计算每个字符出现的次数count
            c[str[i]].count++;
        }
        for (int i = 0; i < 128; i++) {//将结构体根据count降序排序
            for (int j = 0; j < 128 - i; j++) {
                if (c[j].count < c[j + 1].count) {
                    s a = c[j];//此处注意是将结构体排序而不是count！
                    c[j] = c[j + 1];
                    c[j + 1] = a;
                }
            }
        }
        for (int i = 0; i < 128; i++) {//将排序好的结构体中的字符ASCII码以字符输出
            if (c[i].count == 0) {//判断出现的字符是否输出完毕
                printf("\n");
                break;
            }
            printf("%c", c[i].num);
        }
    }
    return 0;
}