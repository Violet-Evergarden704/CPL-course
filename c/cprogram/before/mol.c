#include<stdio.h>
#include<math.h>
int main(){
    double P,L,T,V,R,n;
    R=8.314;
    scanf("%lf%lf%lf",&P,&L,&T);
    V=pow(L,3);
    n=P*V/(R*T);
    printf("%.4e",n);
    return 0;
}