#include<stdio.h>
#include<stdlib.h>
int a[1000001];
int data_cmp(void const *vp, void const *vpa) 
{
    return *(int *)vpa-*(int *)vp;
}
int main(){
    int n=0,q=0;
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    while(q--){
        int quiry=0;
        scanf("%d",&quiry);
        int *ans=bsearch(&quiry,a,n,sizeof(int),data_cmp);
        if(ans) printf("%d\n",*ans);
        else printf("-1\n");
    }
    return 0;
}