#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char s;
    scanf("%s",s);
    char *ptr_s=&s;
    int len=strlen(s);
    for(ptr_s=s;ptr_s<s+len;ptr_s++){
        if(*ptr_s==' '&&islower(*(ptr_s+1))){
            *ptr_s-=32;
        }
        else if(*ptr_s!=' '&&isupper(*(ptr_s+1))){
            *ptr_s+=32;
        }
    }
    
    for(ptr_s=s;ptr_s<s+len;ptr_s++){
        printf("%c",*s);
    }
}