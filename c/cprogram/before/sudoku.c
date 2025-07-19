#include<stdio.h>
int main(){
    int A[9][9];
    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            A[i][j]=0;
            scanf("%d",&A[i][j]);
        }
    }
    int flag=1;
    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            
            if(i%3==2 && j%3==2){
                    for(int m=0;m<3;m++){
                        for(int n=0;n<3;n++){
                        
                            if(A[i][j]
                            ==A[i-m][j-n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
                if(i%3==2 && j%3==1){
                    for(int m=0;m<3;m++){
                        for(int n=-1;n<2;n++){
                        
                            if(A[i][j]
                            ==A[i-m][j-n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
                if(i%3==2 && j%3==0){
                    for(int m=0;m<3;m++){
                        for(int n=0;n<3;n++){
                        
                            if(A[i][j]
                            ==A[i-m][j+n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
                if(i%3==1 && j%3==2){
                    for(int m=-1;m<2;m++){
                        for(int n=0;n<3;n++){
                        
                            if(A[i][j]
                            ==A[i-m][j-n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
                if(i%3==1 && j%3==1){
                    for(int m=-1;m<2;m++){
                        for(int n=-1;n<2;n++){
                        
                            if(A[i][j]
                            ==A[i-m][j-n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
                if(i%3==1 && j%3==0){
                    for(int m=-1;m<2;m++){
                        for(int n=0;n<3;n++){
                        
                            if(A[i][j]
                            ==A[i-m][j+n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
                if(i%3==0 && j%3==2){
                    for(int m=0;m<3;m++){
                        for(int n=0;n<3;n++){
                        
                            if(A[i][j]
                            ==A[i+m][j-n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
                if(i%3==0 && j%3==1){
                    for(int m=0;m<3;m++){
                        for(int n=-1;n<2;n++){
                        
                            if(A[i][j]
                            ==A[i+m][j-n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
                if(i%3==0 && j%3==0){
                    for(int m=0;m<3;m++){
                        for(int n=0;n<3;n++){
                        
                            if(A[i][j]
                            ==A[i+m][j+n]){
                                if(m==0&&n==0) flag=1;
                                else flag=0;
                            }
                            
                        }
                        
                    }
                }
            for(int m=0;m<9 && m>j && m>i;m++){
                int a[9]={0};
                int b[9]={0};
                
                a[m]=A[i][j]-A[i][m];
                b[m]=A[i][j]-A[m][j];
                
                if(a[m]==0) flag=0;
                else if(b[m]==0) flag=0;
            }
        }
    }
    if (flag==1) printf("YES");
    else if (flag==0) printf("NO");
    return 0;
}