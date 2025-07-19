#include<stdio.h>
#include<math.h>
int chain[100000];
int ans[10001];
int cmt=1;
void split(int i){
    chain[i]--;
    chain[i+1]=chain[i];
}
int main(){
    int n=0,q=0;
    scanf("%d%d",&n,&q);
    chain[0]=n;
    char s=getchar();
    if(s=='A'){
        int id=0,m=0;
        scanf("%d%d",&id,&m);
        int lgm=log2(m)+1;
        for(int i=0;i<n;i++){
            if(lgm!=n){
                split(chain[i]);
                n--;
                cmt++;
            }
            else {if(!ans[i])
                ans[i]=id;
                else
                ans[i-1]=id;
            }
        }
    }
    else {
        printf("%d\n",cmt);
        for(int i=cmt-1;i>=0;i--){
            printf("%d ",ans[i]);
        }
    }
}