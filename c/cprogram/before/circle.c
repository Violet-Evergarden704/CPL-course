#include<stdio.h>
int main()
{
    double radius;
    scanf("%lf",&radius);
    double L=2*3.14159*radius;
    double S=3.14159*radius*radius;
    double A=4*3.14159*radius*radius;
    double V=4.0/3.0*3.14159*radius*radius*radius;//也可以把π换掉

    printf("%-15.4lf:L\n%-15.4lf:S\n",L,S);
    printf("%-15.4lf:A\n%-15.4lf:V\n",A,V);//格式化
    return 0;
}