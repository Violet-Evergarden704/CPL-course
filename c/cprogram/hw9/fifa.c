#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int attack[1001][11];
int defend[1001][11];
int strategy[1001][11];
float aver_att[1001];
float aver_def[1001];
float aver_stra[1001];

void Print(float a[],char **team);
int main(){
    char *team[1001];
    char *players[11];
    int n;
    scanf("%d",&n);//n是队伍数量
    for(int i=0;i<n;i++){
        team[i]=malloc(21*sizeof(char *));
    }
    for(int i=0;i<11;i++){
        players[i]=malloc(21*sizeof(char *));
    }
    
    for(int i=0;i<n;i++){
        scanf("%s",team[i]);
        getchar();
        for(int j=0;j<11;j++){
            scanf("%s",players[j]);
            getchar();
            scanf("%d%d%d",&attack[i][j],&defend[i][j],&strategy[i][j]);
            getchar();
        }
    }

    
    
    for(int i=0;i<n;i++){
        for(int j=0;j<11;j++){
            aver_att[i]+=attack[i][j];
            aver_def[i]+=defend[i][j];
            aver_stra[i]+=strategy[i][j];
        }
        aver_att[i]=aver_att[i]/11.0;
        aver_def[i]=aver_def[i]/11.0;
        aver_stra[i]=aver_stra[i]/11.0;
    }
    //按照进攻排序的输出：
      Print(aver_att,team);
      Print(aver_def,team);
      Print(aver_stra,team);
    return 0;
}
void Print(float a[],char **team){
    int vis2[1001]={0};
    for(int i=0;i<1001;i++){
        float max=a[0];
        int maxid=0;
        for(int j=0;j<1001;j++){
        if(a[j]>max){
            max=a[j];
            maxid=j;
        }
        else continue;
        }
        if(!vis2[maxid]){
            printf("%s ",team[maxid]);
            vis2[maxid]=1;
            a[maxid]=0;
        }
        else {
            continue;
        }
    }
    printf("\n");
    
}