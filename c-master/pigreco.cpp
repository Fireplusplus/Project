#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

main(){
   
double lati=9999999,PI= 3.1415;
for(;;lati++){system("cls");
              printf("%5.0f : pigreco = %f\n\n",lati,(lati)*sin(PI/lati));
              }

}
