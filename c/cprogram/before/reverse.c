#include<stdio.h>
int a[101];
int main(){
    int flag=0,sum=0;
    int m=0;
    int b=0;
    scanf("%d",&m);
    for(int i=0;i<m-1;i++) scanf("%d",&a[i]);
    for(int i=0;i<m-1;i++){
        if(a[i]<=a[i+1]){
            flag=0;
            sum+=flag;
        }
        else if(a[i]>a[i+1]){
            flag=1;
            sum+=flag;
        }
    }
    for(int i=1;i<m-1;i++){
        if(sum==0&&a[i-1]+a[i+1]>2*a[i]) b=1;
    }
    if(sum==0&&b==0)printf("0");
    else if(sum==0&&b==1)printf("1");
    else printf("-1");
    return 0;
}