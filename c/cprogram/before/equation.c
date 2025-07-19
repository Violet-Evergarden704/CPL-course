#include<stdio.h>
#include<math.h>
int main(){
    int p,q;
    double m,x1;
    scanf("%d%d",&p,&q);
    m=sqrt(pow(q/2.0,2)+pow(p/3.0,3));
    if (-q/2.0-m>0 && -q/2.0+m>0)
    {
        x1=pow(-q/2.0+m,1.0/3)+pow(-q/2.0-m,1.0/3);
        printf("%.3lf\n",x1);
    }
    if (-q/2.0-m<0 && -q/2.0+m>0){
        x1=pow(-q/2.0+m,1.0/3)-pow(q/2.0+m,1.0/3);
        printf("%.3lf\n",x1);
    }
    if (-q/2.0-m<0 && -q/2.0+m<0){
        x1=-pow(q/2.0-m,1.0/3)-pow(q/2.0+m,1.0/3);
        printf("%.3lf\n",x1);
    }
    if(-q/2.0-m>0 && -q/2.0+m<0){
        x1=-pow(q/2.0-m,1.0/3)+pow(-q/2.0-m,1.0/3);
        printf("%.3lf\n",x1);
    }
    return 0;
}