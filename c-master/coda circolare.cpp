#include <stdio.h>
#define MAX_SIZE 5

typedef struct{
        int key;
        } elemento;

elemento coda[MAX_SIZE];


void addc(int davanti, int * dietro, elemento item){
     if((*dietro+1)%MAX_SIZE==davanti)
                                      printf("\n\nCoda piena!");
     else{
         *dietro=(*dietro+1)%MAX_SIZE;
         coda[*dietro]=item;
         }
     }

elemento deletec(int *davanti,int dietro){
         if(*davanti==dietro)
                             printf("\n\nCoda vuota!");
         else
              *davanti=(*davanti+1)%MAX_SIZE;
         return coda[*davanti];
         }

int main(){
    int dietro=0,davanti=0;
    elemento item;
    int scelta;
    while(1){
             printf("\n\nfai la tua scelta:\n1.\taggiungi\n2.\tcancella\n");
             scanf("%d",&scelta);
             if (scelta==1){
                            printf("\ninserisci il numero: ");
                            scanf("%d",&item.key);
                            addc(davanti,&dietro,item);
                            }
             else if(scelta==2)
                               printf("\nho eliminato %d",deletec(&davanti,dietro));
             else
                 break;
                 }
    fflush(stdin);getchar();
}
