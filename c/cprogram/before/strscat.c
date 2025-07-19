#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* mystrcat(char* a,char* b){
    *a = malloc(sizeof(char));
    *b = malloc(sizeof(char));
    int lena=strlen(*a);
    int lenb=strlen(*b);
    char* c=malloc((lena+lenb)*sizeof(char));
    for(int i=0;i<lena;i++){
        *(c+i)=*(a+i);
    }
    for(int i=0;i<lenb;i++){
        *(c+i+lena)=*(b+i);
    }
    return *c;
}
char* mystrdelete(char* a,char* b){
    *a = malloc(sizeof(char));
    *b = malloc(sizeof(char));
    int lena=strlen(*a);
    int lenb=strlen(*b);
    char* c=malloc((lena+lenb)*sizeof(char));
    char* d=malloc((lena+lenb)*sizeof(char));
    *d=strstr(a,b);
    for(int i=lenb;i<lena;i++){
        *(c+i)==*(d+i);
    }
    return *c;
}
int main(){
    int n;
    char* s1=malloc(sizeof(char));
    char* s2=malloc(sizeof(char));
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        while ((scanf("%s", s1) != EOF));
        while ((scanf("%s", s2) != EOF));
    }
    int len1=strlen(*s1);
    int len2=strlen(*s2);
    for(int i=len2-1;i>=0;i--){
        if(*(s1+len1-1)==*(s2+i)){
            
        }
    }

    return 0;
}