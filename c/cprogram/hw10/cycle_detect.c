#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
char *strings[10000001];
int dest[10000001];
int number[10000001];
bool check_range(int target,int n){
    if(target<=n&&target>=1)return true;
    else return false;
}

int main(){
    int n=0;
    int range=1,head=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        number[i]=i;
        strings[i]=(char *)malloc(200*sizeof(char *));
        scanf("%s%d",strings[i],&dest[i]);
    }
    //input over
    for(int i=1;i<=n;i++){
        if(!check_range(dest[i],n)) {
            printf("-1");
            range=0;
            break;
        }
    }
    if(range){
            if(dest[dest[1]]==1){
                head=0;
                printf("%s",strings[1]);
            }
    }//特别判定如果起点是第一位的情况，但是我写的不完善，如果是1->2->3->1这种情况就会出错
    
    if(range&&head){
    int *p1=number+1,*p2=number+1;
    int flag=0;
    for(int i=1;i<=n*n;i++){
        p1=number+dest[*p1];
        p2=number+dest[*p2];
        p2=number+dest[*p2];
        if(p1==p2){
            flag=1;
            break;
        }
    }
    if(flag){
        p1=number+1;
        for(int i=0;i<n*n;i++){
            p1=number+dest[*p1];
            p2=number+dest[*p2];
            if(p1==p2){
            printf("%s",strings[*p1]);
            break;
            }
        }
    }
    else printf("-1\n");
    }
    return 0;
}