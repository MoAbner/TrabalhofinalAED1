#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(int *x, int *y){ 
   int temp;
   temp=*x;
   *x=*y;
   *y=temp;
}
int particionamento(int abner[], int left, int rigth){
    int mediana = (rigth - left) / 2;
    int pivo1 = abner[mediana];    
    int i = left;

    for( int j = mediana + 1; j <= rigth; j++){

        if(abner[j] <= pivo1){
            i++;
            swap(&j, &i);        
        }
    }
   
    return(i);
}
// RELAÇÃO DE RECORRÊNCIA.