#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
int pos;
 
int compute(char* data)
{
    int len = strlen(data);
    int stack[1000];
    int top = -1;
    int num = 0;
    char flag = '+';
 
    while (pos < len) {
        if (data[pos] == '{' || data[pos] == '[' || data[pos] == '(') {
            pos++;
            num=compute(data);
        }
 
        while (pos < len && isdigit(data[pos])) {
            num = num*10 + data[pos] -'0';
            pos++;
        }
 
        switch (flag) {
        case '+':
            stack[++top] = num;
            break;
        case '-':
            stack[++top] = -num;
            break;
        case '*':
            stack[top] *= num;
            break;
        case '/':
            stack[top] /= num;
            break;
        }
 
        num = 0;
        flag = data[pos];
        if (data[pos] == '}' || data[pos] == ']'|| data[pos] == ')') {
            pos++;
            break;
        }
        pos++;
    }
 
    int res = 0;
 
    for (int i = 0; i <= top; i++) {
        res += stack[i];
    }
    return res;
}
 
int main()
{
    char data[1000];
 
    while (scanf("%s", data) != EOF) {
        pos = 0;
        int res = compute(data);
        printf("%d\n", res);
    }
    return 0;
}