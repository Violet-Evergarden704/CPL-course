#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int front[3][3];
int back[3][3];
int left[3][3];
int right[3][3];
int up[3][3];
int down[3][3];

void f(void){
    
}

int main(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&front[i][j]);
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&back[i][j]);
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&left[i][j]);
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&right[i][j]);
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&up[i][j]);
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&down[i][j]);
        }
    }

    //input over
}