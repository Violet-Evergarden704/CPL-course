#include<stdio.h>
int main(){
    int n=0;
    scanf("%d",&n);
    int a[2001] = {0};
    for (int i=1;i<=n;i++){
        if(a[i]==0)
        a[i]=1;
        else if(a[i]==1)
        a[i]=0;
    }
    for (int b=1;b<=n;b++){
        if(a[b]==1)
        printf("%d ",b);
    }
    return 0;
}