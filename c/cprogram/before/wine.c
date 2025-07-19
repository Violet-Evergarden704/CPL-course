#include<stdio.h>
int a[10001];
int b[10001];
int main(){
    int n=0,l=0;
    scanf("%d%d",&n,&l);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&b[i]);
    }
    int ml[10002]={0};
    int value=0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (a[j] > a[j + 1]) {
                 int tmp = a[j];
                 int tmpb=b[j];
                 a[j] = a[j + 1];
                 b[j]=b[j+1];
                 a[j + 1] = tmp;
                 b[j+1]=tmpb;
    }
  }
}
    for(int i=n-1;i>=0;i--){
        ml[i]=b[i]+ml[i+1];
        if(ml[i]<=l){
        value+=b[i]*a[i];
        }
        else if(ml>l&&i!=n-1){
            b[i]=-(ml[i+1]-l);
            value+=b[i]*a[i];
            break;
        }
        else if(ml>l&&i==n-1){
            value+=l*a[i];
            break;
        }
    }
    printf("%d",value);
    return 0;
}