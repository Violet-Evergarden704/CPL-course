/*华氏温度转化为摄氏温度*/
#include <stdio.h>
int main(){
    double f,c;
    printf("Fahrenheit temperature:");
    scanf("%lf",&f);
    c=(f-32.0f)*5.0/9.0;
    printf("Celsius temperature:%.1lf",c);
    return 0;
}