#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void troca(int *x, int *y){ 
   int temp;
   temp=*x;
   *x=*y;
   *y=temp;
}

int particionamento(int vetor[], int left, int rigth){
    int mediana = (left + (rigth - left)/2);
    troca(&vetor[mediana], &vetor[rigth]);
    int pivo = vetor[rigth];
    int i = left-1;

    for( int j = left; j < rigth; j++){

        if(vetor[j] < pivo){
            i++;
            troca(&vetor[j], &vetor[i]);        
        }
        troca(&vetor[i+1], &vetor[rigth]);    
    }
   
    return(i + 1);
}

void quickSort(int vetor[], int left, int rigth, clock_t *tempo){
    clock_t inicio = clock();
    if(left < rigth){
        int indice_pivo = particionamento(vetor, left, rigth);
        quickSort(vetor, left, indice_pivo - 1, tempo );
        quickSort(vetor, indice_pivo + 1, rigth, tempo);
    }
    *tempo = clock() - inicio;
}

void gerarVetorCrescente(int vetor[], int tamanhoVetor) {

    for (int i = 0; i < tamanhoVetor; i++) {
        vetor[i] = i + 1;
    }
}

void gerarVetorDecrescente(int vetor[], int tamanhoVetor) {

    for (int i = 0; i < tamanhoVetor; i++) {
        vetor[i] = tamanhoVetor - i;
    }
}

void gerarVetoraleatorio(int vetor[], int tamanhoVetor) {
    
    srand (time(NULL));
    for (int i = 0; i < tamanhoVetor; i++) {
        vetor[i] = rand() % tamanhoVetor;
    }
}

int main() {

    int elementos;
    
    for(elementos = 100; elementos <= 10000000; elementos *= 10){
        int *vetor = (int*)malloc(elementos * sizeof(int));
        
        //a)
        gerarVetorCrescente(vetor, elementos);

        clock_t tempo;
        printf("teste com %d elementos(Crescente): \n", elementos);

        quickSort(vetor, 0, elementos - 1, &tempo );

        printf("Tempo do QuickSort: %.2lf milisegundos\n", ((double)tempo/CLOCKS_PER_SEC) * 1000);
    
        free(vetor);
    }

    printf("\n");

    for(elementos = 100; elementos <= 10000000; elementos *= 10){
        int *vetor = (int*)malloc(elementos * sizeof(int));
        
        //b)
        gerarVetorDecrescente(vetor, elementos);

        clock_t tempo;
        printf("teste com %d elementos(Decrescente): \n", elementos);

        quickSort(vetor, 0, elementos - 1, &tempo );

        printf("Tempo do QuickSort: %.2lf milisegundos\n", ((double)tempo/CLOCKS_PER_SEC) * 1000);
    
        free(vetor);
    }

    printf("\n");

     for(elementos = 100; elementos <= 10000000; elementos *= 10){
        int *vetor = (int*)malloc(elementos * sizeof(int));
        
        //c)
        gerarVetoraleatorio(vetor, elementos);

        clock_t tempo;
        printf("teste com %d elementos(aleatório): \n", elementos);

        quickSort(vetor, 0, elementos - 1, &tempo );

        printf("Tempo do QuickSort: %.2lf milisegundos\n", ((double)tempo/CLOCKS_PER_SEC) * 1000);
    
        free(vetor);
    }

    return 0;
}
