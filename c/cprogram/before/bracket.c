#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#define size 100001
char contents[1000000];
int top=0;
int wa=0;
void push(char i){
    top++;
    contents [top]=i;
}
void pop(void){
    contents[top]=0;
    if(top>0)
    top--;
    else if(top==0)
    wa=1;
}
char s[1000000];

int main(){
    int t=0;
    int flag=0;
    scanf("%d",&t);
    for(int i=0;i<t;i++){
        top = 0, wa = 0, flag = 0; // 多次使用で变量必须每一次都初始化为你想要で情况，不然就会偏离预期
        scanf("%s",s); 
        int len = strlen(s);
        for(int j=0;j<len;j++){
            if(s[j]=='('
                ||s[j]=='['
                ||s[j]=='{'){
                    push(s[j]);
        }
        else if(s[j]==')'){
            if(contents[top]=='('){
                flag=0;
                pop();
                if(wa){
                flag=1;
                break;
                }
            }
            else {
                flag=1;
                break;}
        }
        else if(s[j]==']'){
            if(contents[top]=='['){
                flag=0;
                pop();
                if(wa){
                flag=1;
                break;
                }
            }
            else {
                flag=1;
                break;}
        }
        else if(s[j]=='}'){
            if(contents[top]=='{'){
                flag=0;
                pop();
                if(wa){
                flag=1;
                break;
                }
            }
            else {
                flag=1;
                break;}
        }
        }
    if(flag || top != 0)printf("False\n"); // 有两种情况会出问题，一方面し匹配失误左右对不上，另一方面可能し左边一堆左括号，右边有一些可以匹配で但是不够数量 例如 ((((((()))，这种情况に原来で程序识别不出来，所以一定要正常匹配+匹配完全，即flag == 0 && top == 0才合题
    else printf("True\n");
    }
    return 0;
}