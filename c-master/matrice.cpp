#include <stdio.h>

main(){
int i,j,a[5][5];
for(i=0;i<5;i++){
                 for(j=0;j<5;j++){
                 if(j-i==0)a[i][j]=1;
                 else a[i][j]=0;
                 }
}
for(i=0;i<5;i++){
                 for(j=0;j<5;j++){
                 printf("%d",a[i][j]);
                 }
printf("\n");
}
fflush(stdin);getchar();
}
