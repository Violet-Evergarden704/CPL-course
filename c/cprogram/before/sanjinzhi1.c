#include<stdio.h>
#include<string.h>
#include<math.h>
int main(){
    int n;
    int t=0;//t是结果
    scanf("%d",&n);
    for (int i=0;i<n;i++){//n行，n个数
        char s[15];
        int len=0;
        int m=0;
        scanf("%s",s);
        len=strlen(s);
        for(int b=0;b<len;b++){
            if(s[b]=='Z') m=-1;
            if(s[b]=='1') m=1;
            if(s[b]==0) m=0;
            t=m*pow(3,b);
        }
        printf("%d",t);
        
        
    }
    return 0;
}