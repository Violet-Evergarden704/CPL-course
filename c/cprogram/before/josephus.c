#include<stdio.h>
int main(){
    int n=0,k=0;
    scanf("%d%d",&n,&k);
    int a[500]={1};
    for (int i=1,m=0;m==n-2;i+=k,m++){
        if(i<=n)
            a[i]=0;
        if(i>n){
            i=i-n;
            a[i]=0;
        }
    }
    
    
    
    
    
    for (int b=0;b<=n-1;b++){
        if (a[b]==1)
        printf("%d",b);
    }
    return 0;
}