/*Grafi rappresentati mediante liste di adiacenza
Scrivere un programma in C che implementi la struttura dati grafo mediante le liste di adiacenza. Si richiede che
•	l'input sia costituito dal numero dei vertici e per ciascun vertice siano assegnati i vertici adiacenti:
•	si possa visitare il grafo in profondità ed in ampiezza.
*/

#include <stdio.h>
#include <stdlib.h>
#define M 50

typedef struct nodo{
        int key;
        struct nodo* next;
        }vertice;
vertice *tmp=NULL,*coda_top=NULL,*coda_end=NULL;     

void push(int n){
        tmp=(vertice*)malloc(sizeof(vertice));
        tmp->key=n;
        tmp->next=NULL;
        if(coda_top)
                     coda_end->next=tmp;
        else
             coda_top=tmp;
        coda_end=tmp;
}

int pop(){
    int n;
    n=coda_top->key;
    tmp=coda_top;
    coda_top=coda_top->next;
    free(tmp);
    printf("%d -> ",n);
    return n;
}

/*void ram(int v,vertice*grafo[]){
     int visitato[M],i;
     for(i=0;i<M;i++)
                             visitato[i]=0;
     printf("%5d",v);
     visitato[v]=1;
     push(v);
     while(coda_top){
                     v=pop();
                     for(tmp=grafo[v];tmp;tmp=tmp->next)
                                                         if(!visitato[tmp->key]){
                                                                                        printf("%5d",tmp->key);
                                                                                        push(tmp->key);
                                                                                        visitato[tmp->key]=1;
                                                         }
                     
     }
}*/

     
int visitato[M];

void azzera_visitato(){
     int i;
     for(i=0;i<M;i++)
                             visitato[i]=0;
}

void visita_profondita(int n,vertice * grafo[]){
     vertice* temp;
     visitato[n]=1;
     printf("%5d",n);
     for(temp=grafo[n];temp;temp=temp->next)
                                            if(!visitato[temp->key])
                                                                    visita_profondita(temp->key,grafo);
     
}

void visita_livello(vertice * grafo[],int n_vertici){
     int start;
     int visitato[M];
     int i;
     
     for(i=0;i<n_vertici;i++)
                             visitato[i]=0;
                       
     system("cls");
     printf("Da qualche vertice si vuole iniziare la visita per livello : ");
     scanf("%d",&start);
     push(start);
     visitato[start]=1;
     printf("\n\n");
     while(coda_top){
                                 tmp=grafo[pop()];
                                 while(tmp){
                                            if(!visitato[tmp->key]){
                                                                    visitato[tmp->key]=1;
                                                                    push(tmp->key);
                                            }
                                            tmp=tmp->next;
                                 }
     }
     printf("NULL");                       
}

void stampa_grafo(int n_vertici, vertice *grafo[]){
     int i;
     system("cls");
     for(i=0;i<n_vertici;i++){
                            tmp=grafo[i];
                            printf("%d : ",i);
                            while(tmp){
                                       printf("%d - > ",tmp->key);
                                       tmp=tmp->next;
                            }                                     
     printf("NULL\n");
     }
}

vertice *crea_lista(int ver_adi){
     vertice *testa;
     printf("\ninserisci i vertici: ");
     testa=NULL;
     for(;ver_adi;ver_adi--){
                             tmp=(vertice*)malloc(sizeof(vertice));
                             tmp->next=testa;
                             scanf("%d",&tmp->key);
                             testa=tmp;
     }                    
}

int crea_grafo(vertice *grafo[]){
     int n_vertici,ver_adi,i;
     system("cls");
     printf("inserisci il numero di vertici: ");
     scanf("%d",&n_vertici);
     for(i=0;i<n_vertici;i++){
                              printf("\nInserisci il numero di vertici adiacenti a %d: ",i);
                              scanf("%d",&ver_adi);
                              grafo[i]=crea_lista(ver_adi);
     }
     return n_vertici;
}

int main(){
    int n_vertici;
    int scelta;
    vertice *grafo[M];
    n_vertici=crea_grafo(grafo);
    stampa_grafo(n_vertici,grafo);
    fflush(stdin);getchar();
    visita_livello(grafo,n_vertici);
    //printf("\n\ninserisci n: ");
    //scanf("%d",&scelta);
    //ram(scelta,grafo);   
    printf("\n\ninserisci il nodo radice: ");
    scanf("%d",&scelta);
    azzera_visitato();
    visita_profondita(scelta,grafo);
    fflush(stdin);getchar();
}
