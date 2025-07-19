#include<stdio.h>
int main(){
    char name[20];
    int pre;
    double frac,factor,scieexp,conv;
    char unit,newunit;
    scanf("%s%d%lf%lf %c",&name,&pre,&frac,&factor,&unit);//单个字符只能用%c,不能用%s,%c要加空格
    scieexp=pre+frac;
    conv=(pre+frac)*factor;
    unit=unit-32;
    printf("%.2s: %d (%.5lf) | %.5E %.5lf %c",name,pre,frac,scieexp,conv,unit);
    return 0;
}