#include<stdio.h>
int main(){
    int r=0,c=0;
    scanf("%d%d",&r,&c);
    char s[102][102];
    int num=0;
    int cornerleft[102][102]={0};
    int cornerright[102][102]={0};
    for(int i = 0;i<r;i++){
        scanf("%s",s[i]);
    }
    
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
                for(int k=1;j-k>=0;k++){
                    if(s[i][j]=='/'&&s[i+k][j-k]=='/')cornerleft[i][j]++;
                    else break;
                }
                
                for(int k=1;j+k<c;k++){
                    if(s[i][j]=='\\'&&s[i+k][j+k]=='\\')cornerright[i][j]++;
                    else break;
                }
                
                int min=cornerleft[i][j];
                if(cornerleft[i][j]>=cornerright[i][j])
                min=cornerright[i][j];
                
                for(int k=0;k<=min;k++){
                    if(s[i][j]=='/'
                        &&s[i][j+1]=='\\'
                        &&j-k>=0
                        &&j-k<c
                        &&j+k+1>=0
                        &&j+k+1<c
                        &&i+k+1<r
                        &&i+k+1>=0
                        &&s[i+k+1][j-k]=='\\'
                        &&s[i+k+1][j+k+1]=='/'
                        &&cornerright[i+k+1][j-k]>=k
                        &&cornerleft[i+k+1][j+1+k]>=k)
                        num++;
                }
            }
        }
    printf("%d",num);
    return 0;
}    printf(" %d",cornerright[4][0]);