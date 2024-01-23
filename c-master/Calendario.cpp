#include <stdio.h>

main()
{
      int scelta=7, counter, giorni;
      
      do{printf("Che giorno e' il primo del mese?");
      printf("\n0) Lun\n1) Mar\n2) Mer\n3) Gio\n4) Ven\n5) Sab\n6) Dom");
      printf("\nInserire la scelta: ");
      scanf("%d",&scelta);
      printf("\n\n");}while(scelta>6);
      counter=scelta;
      
      printf("\n\n Lun Mar Mer Gio Ven Sab Dom\n");
     
                      while(scelta>0){
                                 scelta--;
                                 printf("    ");
                                 }

      for(giorni = 1; giorni < 32; giorni++){
                 printf("%4d",giorni);
                 if((giorni+counter)%7==0)printf("\n");
                 }
    
fflush(stdin);
getchar();
return 0;      
}
      
