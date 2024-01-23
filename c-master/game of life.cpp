#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 10

int quadrato[n][n],a,b,i,j,h,k,conta=0,kill_today,mobilita;

struct elemento{
       int x,y,giorni;
       struct elemento *next;
       }*testa=NULL,*coda=NULL,*tmp=NULL;

void push(int x,int y){
     tmp=(struct elemento*)malloc(sizeof(struct elemento));
     if(testa==NULL){
                    testa=tmp;
                    coda=tmp;
                    }
     else{
         coda->next=tmp;
         coda=tmp;
         }
     tmp->x=x;
     tmp->y=y;
     tmp->giorni=0;
     coda->next=NULL;
     }

void mostra_elementi(){
     printf("\n\nsesso,giorni e posizioni degli elementi\n");
     tmp=testa;
     while(tmp!=NULL){
                      printf("--> %c %dgg (%d,%d)",quadrato[tmp->x][tmp->y],tmp->giorni,tmp->x,tmp->y);
                      tmp=tmp->next;
                      }
}

void azzera(int probabilita){
     for (i=0;i<n;i++)
         for(j=0;j<n;j++)
                         if(rand()%101<probabilita){
                                                    push(i,j);
                                                    conta++;
                                                   if(rand()%2){
                                                               quadrato[i][j]=11;
                                                               }
                                                   else{
                                                       quadrato[i][j]=12;
                                                       }
                                                   }
                         else
                             quadrato[i][j]=0;
}

void mostra(){
     system("CLS");
     for (i=0;i<n;i++){
         for(j=0;j<n;j++)
                         printf("%c",quadrato[i][j]);
         printf("\n");
                      }
}

void kill(){
     conta--;
     tmp=testa;
     quadrato[tmp->x][tmp->y]=0;
     testa=testa->next;
     free(tmp);     
}

void genera(){
     
}

int controlla_possibilita(int x,int y){
           k=0;
           for(a=x-1;a<x+2;a++)
                               for(b=y-1;b<y+2;b++)
                                                   if(a>=0 && b<=9)
                                                           if(quadrato[a][b]==0)
                                                                               k++;
           return k;                      
}

void sposta(){
     printf("\n\n\n");
     for(i=conta*mobilita/100;i;i--){
                                     tmp=testa;
                                     for(j=rand()%conta;j;j--)
                                                               tmp=tmp->next;
                                     h=quadrato[tmp->x][tmp->y];
                                     printf("(%d,%d)-->",tmp->x,tmp->y);
                                     do{if(controlla_possibilita(tmp->x,tmp->y)){
                                                                                 quadrato[tmp->x][tmp->y]=0;
                                                                                 tmp->x+=(rand()%3)-1;
                                                                                 if(tmp->x<0)
                                                                                             tmp->x+=10;
                                                                                 if(tmp->x>9)
                                                                                             tmp->x-=10;                                                                                 
                                                                                 tmp->y+=(rand()%3)-1;
                                                                                 if(tmp->y<0)
                                                                                             tmp->y+=10;
                                                                                 if(tmp->y>9)
                                                                                             tmp->y-=10;                                                                                 
                                                                                 }
                                        }while(quadrato[tmp->x][tmp->y]!=0);
                                     printf("(%d,%d)  ",tmp->x,tmp->y);
                                     quadrato[tmp->x][tmp->y]=h;
                                     }
                                                               
     
}

void giorno(){
     sposta();
     if(conta){
               printf("\n\nUn giorno e\' passato e ci sono %d elementi\n",conta);
                   tmp=testa;
                       while(tmp!=NULL){
                                           if(tmp->giorni<10)
                                                             tmp->giorni++;
                                           else
                                               kill_today++;
                                           tmp=tmp->next;
                                           }
                       if(kill_today)
                                     printf("...e moriranno %d elementi! :(",kill_today);
                       while(kill_today){
                                         kill();
                                         kill_today--;
                       }
               }
     else{
         printf("\n\nSono tutti morti! :(:(:(:(:(:(:(:(:(:(:(:(");
         fflush(stdin);getchar();
         }
}

int main(){
    srand(time(NULL));
    printf("Quante probabilita\' in percentuale che ci sia un essere in ogni spazio?\n");
    scanf("%d",&i);
    printf("\nQuanto vuoi che siano mobili le cellule in percentuale?\n");
    scanf("%d",&mobilita);
    azzera(i);
    while(1){
             mostra();
             mostra_elementi();
             giorno();
             fflush(stdin);getchar();
             }
}
