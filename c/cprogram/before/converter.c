#include<stdio.h>
int main(){
    int m,a,b,c;
    scanf("%d",&m);
    a=m/100;
    b=(m-a*100)/10;
    c=(m-a*100-b*10);
    if(m==0)
    printf("zero");
    if(m%100==0 && m!=0){
    switch(a){
        case 1:printf("one hundred");break;
        case 2:printf("two hundred");break;
        case 3:printf("three hundred");break;
        case 4:printf("four hundred");break;
        case 5:printf("five hundred");break;
        case 6:printf("six hundred");break;
        case 7:printf("seven hundred");break;
        case 8:printf("eight hundred");break;
        case 9:printf("nine hundred");break;}
    }
    else if(m%100!=0){
    switch(a){
        case 0:break;
        case 1:printf("one hundred and ");break;
        case 2:printf("two hundred and ");break;
        case 3:printf("three hundred and ");break;
        case 4:printf("four hundred and ");break;
        case 5:printf("five hundred and ");break;
        case 6:printf("six hundred and ");break;
        case 7:printf("seven hundred and ");break;
        case 8:printf("eight hundred and ");break;
        case 9:printf("nine hundred and ");break;}
    if(m%10==0){
            switch(b){
    case 0:break;
    case 1:printf("ten");break;
    case 2:printf("twenty");break;
    case 3:printf("thirty");break;
    case 4:printf("forty");break;
    case 5:printf("fifty");break;
    case 6:printf("sixty");break;
    case 7:printf("seventy");break;
    case 8:printf("eighty");break;
    case 9:printf("ninty");break;}
    
    }
    else if (m%10!=0){
    switch(b){
    case 0:break;
    case 1:switch(m%100){
        case 11:printf("eleven");break;
        case 12:printf("twelve");break;
        case 13:printf("thirteen");break;
        case 14:printf("fourteen");break;
        case 15:printf("fifteen");break;
        case 16:printf("sixteen");break;
        case 17:printf("seventeen");break;
        case 18:printf("eighteen");break;
        case 19:printf("nineteen");break;}
        break;
    case 2:printf("twenty-");break;
    case 3:printf("thirty-");break;
    case 4:printf("forty-");break;
    case 5:printf("fifty-");break;
    case 6:printf("sixty-");break;
    case 7:printf("seventy-");break;
    case 8:printf("eighty-");break;
    case 9:printf("ninty-");break;}
    if(b!=1){
    switch(c){
    case 1:printf("one");break;
    case 2:printf("two");break;
    case 3:printf("three");break;
    case 4:printf("four");break;
    case 5:printf("five");break;
    case 6:printf("six");break;
    case 7:printf("seven");break;
    case 8:printf("eight");break;
    case 9:printf("nine");break;}
    }
    }
    }
    return 0;
}