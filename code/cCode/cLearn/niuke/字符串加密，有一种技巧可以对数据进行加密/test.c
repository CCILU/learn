#include <stdio.h>

void func_encrypt(char * key,char * data,char * encrypt)
{
    int i,k,index;
    int flag[26]={0};
    char kstr[27]="";
    if(key == NULL || data == NULL || encrypt == NULL){
        return;
    }
    for(i=0,k=0; key[i]!='\0'; i++){
        if(key[i]>='A' && key[i]<='Z'){ // 求对应字母表中的下标
            index = key[i] - 'A';
        }else if(key[i]>='a' && key[i]<='z'){
            index = key[i] - 'a';
        }
        flag[index]++; // 标记遇到了几次
        if(flag[index] == 1){ // 第一次遇到时才需要加入密钥表
            if(key[i]>='A' && key[i]<='Z'){
                kstr[k] = key[i];
            }else if(key[i]>='a' && key[i]<='z'){
                kstr[k] = key[i] - 'a' + 'A'; // 统一存为大写，便于后面处理
            }
  //          printf("%d %c ",k,kstr[k]);
            k++;
        }
    }
    for(i=0; i<26; i++){
        if(flag[i] == 0){ // 没有遇到过的字母，存入密钥表
            kstr[k] = 'A' + i;
   //         printf("%d %c ",k,kstr[k]);
            k++;
        }
    }
    kstr[k] = '\0';
 //   printf("\n");
    for(i=0; data[i]!='\0'; i++){
        if(data[i] == ' '){ // 注意空格的处理
            encrypt[i] = ' ';
            continue;
        }
        if(data[i]>='A' && data[i]<='Z'){
            index = data[i] - 'A';
            encrypt[i] = kstr[index];
  //          printf("%c ",encrypt[i]);
        }else if(data[i]>='a' && data[i]<='z'){
            index = data[i] - 'a';
            // 注意不能改变密钥表！！若data中有重复字母，就会导致无法对应而出错
            encrypt[i] = kstr[index] - 'A' + 'a';  // 保持小写状态
  //          printf("%c ",encrypt[i]);
        }
    }
    encrypt[i] = '\0';
    return;
}
int main()
{
    char key[100]="";
    char data[1000]="";
    while(gets(key) && gets(data)){ // 注意可能输入字符串中有空格，用gets而不是scanf
        char encrypt[1000]="";
        func_encrypt(key,data,encrypt);
        printf("%s\n",encrypt);
    }
    return 0;
}