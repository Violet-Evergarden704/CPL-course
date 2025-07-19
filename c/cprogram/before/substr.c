#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    char *s;
    s=(char *)malloc(100005 * sizeof(char));
    char *ipt;
    ipt=(char *)malloc(100005 * sizeof(char));
    scanf("%s",s);
    scanf("%s",ipt);
    int len=strlen(s);
    int len2=strlen(ipt);
    int flag=1;
   // a=(int *)malloc(100005*sizeof(int));
    for(int i=0;i<len;i++){
        for(int j=0;j<len2;j++){
            if(*(s+i+j)==*(ipt+i+j)){
                flag+=0;
            }
        }
        if(!flag){
            printf("%d ",i);
        }
    }
}