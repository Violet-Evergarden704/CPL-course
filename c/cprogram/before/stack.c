#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
char contents[10001];
int top=0;
bool is_empty(void){
    return top==0;
}
void mypush(char s){
    contents[top]=s;
    top++;
}
void mypop(void){
    if(is_empty())printf("Empty\n");
    else{
        top--;
    }
}
void mytop(void){
    if(is_empty())printf("Empty\n");
    else {
        //char str_top=contents[top];
        printf("%c\n",contents[top-1]);
}}
void myprint(void){
    if(is_empty()){
        printf("Empty\n");
        return;
    }
    else{
        for (int i = top - 1; i >= 0; i--)
    printf("| %c |\n", contents[i]);
    printf("|===|\n");
}//dont change elements in stack
    }


int main(void){
    int n=0;
    scanf("%d",&n);
    while(n--){
        char s[10];
        scanf("%s",s);
        if (s[2] == 's'){ 
            char m[2];
            scanf("%s",m);
      mypush(m[0]);}//only pushes one character
    else if (s[0] == 'p' && s[1] == 'o')  // pop
      mypop();
    else if (s[0] == 't')  // top
      mytop();
    else if (s[1] == 'r')  // print
      myprint();
    }
    return 0;
}