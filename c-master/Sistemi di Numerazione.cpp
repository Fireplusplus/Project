/* Sistemi di numerazione */

#include <stdio.h>
#include <math.h>

#define N 50

main()
{
    int v[N];
    int base,cifre,i,j,tmp;
    printf("Inserisci Base e Numero Cifre: ");
    scanf("%d%d",&base,&cifre);
    for(i=0;i<pow(base,cifre)-1;i++)
    {
        tmp=i;
        for(j=cifre-1;j>=0;j--)
        {
            v[j]=tmp%base;
            tmp=tmp/base;
        }     
        for(j=0;j<cifre;j++) printf("%d",v[j]);
        printf("\n");
    }    
    fflush(stdin);
    getchar();
}    
