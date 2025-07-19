#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM 101

char *table[NUM];


char **strsplit(char *s,char *a);
int mystrcmp(char *a, char *b);
int count(char *a,char *b);
int cmp(const void *a, const void *b);

int main(){
    char *s=malloc(NUM*NUM*sizeof(char));
    scanf("%s",s);
    char *spt=malloc(sizeof(char));
    scanf("%c",spt);
    int m=count(s,spt);
    char *ans[NUM];
    ans=strsplit(s,spt);
    qsort(ans,m,sizeof(char *),cmp);
    for(int i=0;i<m;i++){
        
        printf("%s\n",ans[i]);
    }
    return 0;
}

char **strsplit(char *a,char *b){
    int cnt=0;
    char *s=a;
    for(int i=1;i<NUM;i++){
        cnt=0;
        while(*s++!=*b){
            cnt++;
        }
        char *m=malloc(cnt*sizeof(char));
        table[i]=m;
        if(*s=='\0')break;
    }
    return table;
}
int mystrcmp(char *a, char *b){
    for(;*a==*b;a++,b++){
        if(*a=='\0')return 0;
    }
    return *((const unsigned char *)a)-*((const unsigned char *)b);
}
int count(char *a,char *b){
    int cnt=1;
    char *s=a;
    if(*s==*b)cnt++;
    s++;
    if(*s=='\0')return cnt;
    return cnt;
}
int cmp(const void *a, const void *b){
    return *(int *)a-*(int *)b;
}