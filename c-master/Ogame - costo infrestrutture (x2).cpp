#include <stdio.h>
#include <stdlib.h>

main(){
int cri, met, deu, liv;
printf("Inserisci il costo attuale del prossimo livello\nMetallo: ");
scanf("%d",&met);
printf("\nCristallo: ");
scanf("%d",&cri);
printf("\nDeuterio: ");
scanf("%d",&deu);
printf("\n\ninserisci il numero di livelli: ");
scanf("%d",&liv);
for(liv-=1;liv>0;liv--){
                  met*=3;cri*=3;deu*=3;
                  }
printf("L'infrastruttura costa\nMetallo: %d\nCristallo: %d\nDeuterio: %d\n\n",met,cri,deu);
system("pause");
}
