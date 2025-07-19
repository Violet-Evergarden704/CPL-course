#include<stdio.h>
int main(){
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    if (a+b<c || b+c<a || a+c<b){
        printf("not ");
    }
    else if (a*a+b*b==c*c){
        printf("right ");
    }
    else if (a==b && b==c){
        printf("equilateral ");
    }
    else if (a*a+b*b-c*c<0){
        printf("obtuse ");
    }
    else
    printf("acute ");
    if (a==b && b!=c){
        printf("isosceles ");
    }
    if (a==c && b!=c){
        printf("isosceles ");
    }
    if (c==b && a!=c){
        printf("isosceles ");
    }
    printf("triangle");
    return 0;
}