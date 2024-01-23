#include <stdio.h>
#include <stdlib.h>
#define M 50

typedef struct nodo {
    int key;
    struct nodo* next;
}vertice;

vertice *tmp,*coda_top=NULL,*coda_end=NULL;

void visita_lista() {
    printf("\n\n>>");
    for(tmp=coda_top; tmp; tmp=tmp->next)
        printf("%d -> ", tmp->key);
        printf("NULL");
}

void push(int n) {
     tmp=(vertice*)malloc(sizeof(vertice));
     tmp->key=n;
     
     if (coda_top) {
	 printf("\nprimo elemento : %d", n);
         coda_end->next=tmp;
         coda_end=tmp;
     }
     else {
          printf("\nelemento : %d", n);
          coda_top=coda_end=tmp;
     }
          
     coda_end->next=NULL;
                  
}

int pop() {
    if (coda_top) {        
        tmp=coda_top;
        coda_top=coda_top->next;
        printf("\nho poppato %d", tmp->key);
        free(tmp);
    }
    else {
        printf("\nnon ci sono elementi!");
    }
}
                                
int main() {
    int scelta;
    int n;
    do {
        printf("\n\nscegli:\n1)pop\n2)push\n3)esci\n");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                pop();
                break;
            case 2:
                printf("\ninserisci il numero da pushare: ");
                scanf("%d", &n);
                push(n);
                break;
            case 3:
                return 0;
            default: 
                break;
        }
        visita_lista();
    }while(scelta!=3);
    
    fflush(stdin);
    getchar();
}
