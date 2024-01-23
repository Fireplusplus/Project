/*
1_2_3
4_O_6   tabella spostamenti
7_8_9

Lo spostamento Y+1 è inteso verso il basso

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 30
#define m 30
#define MAX_STACK_SIZE 100

int labirinto[n][m];
int x=1,y=1;

typedef struct{
       int x,y;
}spostamento;

spostamento mossa[8]={{-1,-1}, {0,-1}, {1,-1}, {-1,0}, {+1,0}, {-1,+1}, {0,+1}, {+1,+1} };

typedef struct{
        int x,y,dir;
}elemento;

elemento nodo[MAX_STACK_SIZE];

void push(){
     tmp=(struct nodo*)malloc(sizeof(struct nodo));
     if(testa==NULL)
                    tmp->next=NULL;
     else
         tmp->next=testa;
     testa=tmp;
     testa->x=x;
     testa->y=y;
     printf("E' stato trovato un nodo!\n");
     tmp=testa;
     while(tmp!=NULL){
                      printf("--> %d&%d ",tmp->x,tmp->y);
                      tmp=tmp->next;
                      }
}

void pop(){
     if(testa==NULL){
                     printf("\n\nNon trovo soluzioni");
                     fflush(stdin);getchar();
                     }
     else{
          x=testa->x;
          y=testa->y;
          tmp=testa;
          testa=testa->next;
          free(tmp);
          }
}

void mostra(){
     system("CLS");
     int i,j;
     for(i=0;i<n;i++){
                     for(j=0;j<m;j++)
                                      printf("%c",labirinto[i][j]);
                     printf("\n");
     }
     printf("\n\n\n");
}

void valuta(){
     
}
     

void genera(){
     int i,j;    
     do{
        printf("\n\n\nGenero....\n");
        for(i=1;i<n-1;i++)
                     for(j=1;j<m-1;j++)
                                       if(rand()%2)
                                                   labirinto[i][j]=219;
                                       else
                                                   labirinto[i][j]=0;
     }while(labirinto[1][1]!=0 || labirinto[n-2][m-2]!=0);
     for(i=0;i<n;i++)
                      labirinto[0][i]=labirinto[n-1][i]=labirinto[i][0]=labirinto[i][m-1]=219;
     mostra();
     fflush(stdin);getchar();
}

void parti(){
     labirinto[x][y]=176;
     int eunnodo;
     do{
        eunnodo=0;
        if(labirinto[x+1][y+1]==0)
                                  eunnodo++;
        if(labirinto[x][y+1]==0)
                                  eunnodo++;
        if(labirinto[x+1][y]==0)
                                  eunnodo++;
        if(labirinto[x-1][y+1]==0)
                                  eunnodo++;
        if(labirinto[x+1][y-1]==0)
                                  eunnodo++;
        if(labirinto[x-1][y]==0)
                                  eunnodo++;
        if(labirinto[x][y-1]==0)
                                  eunnodo++;
        if(labirinto[x-1][y-1]==0)
                                  eunnodo++;
        
        if(eunnodo>1)
                     push();
                     
        if(labirinto[x+1][y+1]==0){
                                             x+=1;
                                             y+=1;
                                             }
        else if(labirinto[x][y+1]==0)
                                                y+=1;
        else if(labirinto[x+1][y]==0)
                                                x+=1;
        else if(labirinto[x-1][y+1]==0){
                                                  x-=1;
                                                  y+=1;
                                                  }
        else if(labirinto[x+1][y-1]==0){
                                                   x+=1;
                                                   y-=1;
                                                   }
        else if(labirinto[x-1][y]==0)
                                                x-=1;
        else if(labirinto[x][y-1]==0)
                                                y-=1;
        else if(labirinto[x-1][y-1]==0){
                                                  x-=1;
                                                  y-=1;
                                                  }
        else pop();
        labirinto[x][y]=176;
        mostra();
     }while(x!=n-2 || y!=m-2);  
     printf("\n\n\nFATTO!!\n");
     fflush(stdin);getchar();   
       
}

int main(){
    srand(time(NULL));
             genera();
             parti();
}
