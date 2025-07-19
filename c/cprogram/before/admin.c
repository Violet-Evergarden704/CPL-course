#include <stdio.h>
#include <math.h>
int main()
{
    char name[]="wangwei";
    char gender='F';
    int birth_month=5;
    int birth_day=20;
    int birth_year=1902;
    char weekday[]="tuesday";
    double score_c=100,score_m=90,score_med=80;
    double mean =(score_c+score_m+score_med)/3;
    double sum_square=pow(score_c-mean,2)+pow(score_m-mean,2)+pow(score_med-mean,2);
    double sd=sqrt(sum_square);//算方差
    int rank=5;
    printf("%s \t% c\n"
    "%.2d-%.2d-%d \t %.3s \n"
    "%.0lf \t %d%%",
    name,gender,
    birth_month,birth_day,birth_year,weekday,
    mean,rank);
    return 0;
}