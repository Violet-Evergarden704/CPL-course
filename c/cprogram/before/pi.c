#include<stdio.h>
#include<math.h>
int main(){
    double pi1,pi2,a,b,c,d,e,f,g;
    a=pow(5280,3);
    b=236674+30303*sqrt(61);
    c=sqrt(427);
    d=log(a*pow(b,3)+744);
    pi1=d/c;
    e=atan(1.0/8);
    f=atan(1.0/57);
    g=atan(1.0/239);
    pi2=24*e+8*f+4*g;
    printf("%.15lf\n%.15lf",pi1,pi2);
    return 0;
}