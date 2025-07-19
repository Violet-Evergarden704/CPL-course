#include<stdio.h>
int main(){
    int n,a,b,c,max,min,add=0;
    scanf("%d",&n);
    while (n!=495){
    a=n/100;b=(n-a*100)/10;c=n-a*100-b*10;
    
    
    if (a<b && b<c){
    max=c*100+b*10+a;
    min=a*100+b*10+c;
    if(n-(max-min)>0){
    add+=n-(max-min);}
    n=max-min;
    }
    
    if (a<c && b>c){
    max=b*100+c*10+a;
    min=a*100+c*10+b;
    if(n-(max-min)>0){
    add+=n-(max-min);}
    n=max-min;
    }
    
    if (b<a && a<c){
    max=c*100+a*10+b;
    min=b*100+a*10+c;
    if(n-(max-min)>0){
    add+=n-(max-min);}
    n=max-min;
    }
    
    if (b<c && c<a){
    max=a*100+c*10+b;
    min=b*100+c*10+a;
    if(n-(max-min)>0){
    add+=n-(max-min);}
    n=max-min;
    }
    
    if (c<a && a<b){
    max=b*100+a*10+c;
    min=c*100+a*10+b;
    if(n-(max-min)>0){
    add+=n-(max-min);}
    n=max-min;
    }
    
    if (c<b && b<a){
    max=a*100+b*10+c;
    min=c*100+b*10+a;
    if(n-(max-min)>0){
    add+=n-(max-min);}
    n=max-min;
    }
    }
    
    
    printf("%d",add);
    return 0;
}