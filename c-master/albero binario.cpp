#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
       int dato;
       struct nodo *sx,*dx;
       }*albero;


albero genera(albero tmp,int n){
     int sin,des;
     tmp->dato=n;
     printf("\nInserire il dato per il figlio sinistro di %d: ",n);
     scanf("%d",&sin);
     if(sin){
             tmp->sx=(albero)malloc(sizeof(struct nodo));
             genera(tmp->sx,sin);
     }
     else
         tmp->sx=NULL;
     printf("\nInserire il dato per il figlio destro di %d: ",n);
     scanf("%d",&des);
     if(des){
             tmp->dx=(albero)malloc(sizeof(struct nodo));
             genera(tmp->dx,des);
     }
             else
                 tmp->dx=NULL;
     return tmp;
}

void inorder(albero tmp){
     if(tmp){
             inorder(tmp->sx);
             printf("%d ",tmp->dato);
             inorder(tmp->dx);             
     }
}
void preorder(albero tmp){
     if(tmp){
             printf("%d ",tmp->dato);
             preorder(tmp->sx);
             preorder(tmp->dx);             
     }
}
void postorder(albero tmp){
     if(tmp){
             postorder(tmp->sx);
             postorder(tmp->dx);             
             printf("%d ",tmp->dato);
     }
}

void visita(albero radice){
     char scelta;
     do{
             printf("\n\nChe tipo di visita si vuole effettuare?\n\n"
             "1)inorder\n"
             "2)preorder\n"
             "3)postorder\n"
             "0)esci\n");
             scanf("%d",&scelta);
             printf("\n");
             switch(scelta){
                            case 1:
                                 inorder(radice);
                                 break;
                            case 2:
                                 preorder(radice);
                                 break;
                            case 3:
                                 postorder(radice);
                                 break;
                            case 0:
                                 break;
                            default:
                                    printf("Scelta sbagliata!");
             }
     }while(scelta);
}

int main(){
    albero radice=NULL;
    int n;
    printf("Creazione di un albero binario\n\n"
    "Per non creare un nodo digitare 0\n"
    "Immettere il primo dato: ");
    scanf("%d",&n);
    radice=(albero)malloc(sizeof(struct nodo));
    genera(radice,n);
    visita(radice);
    }
