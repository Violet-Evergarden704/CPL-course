#include<stdio.h>
#include<math.h>
int main(){
    int n=0;
    scanf("%d",&n);
    char string[n];
    scanf("%s",string);
    for (int i=0;i<n/2;i++){
        if(string[i]=='?'){
            string[i]=string[n-1-i];
        }
        else if(string[n-1-i]=='?'){
            string[n-i-1]=string[i];
        }
        }
    printf("%s",string);
    return 0;
}