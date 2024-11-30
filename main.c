#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

long long quicksort_trocas = 0;
long long insertionsort_trocas = 0;

void troca(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    quicksort_trocas++;
}

void gerarVetorCrescente(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = i + 1;
    }
}

void gerarVetorDecrescente(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = tamanho - i;
    }
}

void gerarVetorAleatorio(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % tamanho;
    }
}

int particionamento(int vetor[], int left, int right) {
    int mediana = left + (right - left) / 2;
    troca(&vetor[mediana], &vetor[right]);
    int pivo = vetor[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (vetor[j] < pivo) {
            i++;
            troca(&vetor[i], &vetor[j]);
        }
    }
    troca(&vetor[i + 1], &vetor[right]);
    return i + 1;
}

void quickSort(int vetor[], int left, int right) {
    if (left < right) {
        int indice_pivo = particionamento(vetor, left, right);
        quickSort(vetor, left, indice_pivo - 1);
        quickSort(vetor, indice_pivo + 1, right);
    }
}

void insertionSort(int vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
            insertionsort_trocas++;
        }
        vetor[j + 1] = chave;
    }
}

void salvarResultados(char *arquivo, char *algoritmo, char *tipo, int tamanho, double tempo, long long trocas) {
    FILE *fp = fopen(arquivo, "a");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s,%s,%d,%.2lf,%lld\n", algoritmo, tipo, tamanho, tempo, trocas);
    fclose(fp);
}

int main() {
    srand(time(NULL));
    int tamanhos[] = {100, 1000, 10000, 100000, 1000000, 10000000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    for (int t = 0; t < num_tamanhos; t++) {
        int tamanho = tamanhos[t];
        int *vetor = (int *)malloc(tamanho * sizeof(int));
        int *copia = (int *)malloc(tamanho * sizeof(int));

        void (*geradores[])(int *, int) = {gerarVetorCrescente, gerarVetorDecrescente, gerarVetorAleatorio};
        char *tipos[] = {"Crescente", "Decrescente", "Aleatório"};

        for (int tipo = 0; tipo < 3; tipo++) {
            geradores[tipo](vetor, tamanho);

            quicksort_trocas = 0;
            for (int i = 0; i < tamanho; i++) copia[i] = vetor[i];
            clock_t inicio = clock();
            quickSort(copia, 0, tamanho - 1);
            clock_t fim = clock();
            salvarResultados("resultados.csv", "QuickSort", tipos[tipo], tamanho,
                             ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000, quicksort_trocas);

            if (tamanho <= 100000) {
                insertionsort_trocas = 0;
                for (int i = 0; i < tamanho; i++) copia[i] = vetor[i];
                inicio = clock();
                insertionSort(copia, tamanho);
                fim = clock();
                salvarResultados("resultados.csv", "InsertionSort", tipos[tipo], tamanho,
                                 ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000, insertionsort_trocas);
            } else {
                salvarResultados("resultados.csv", "InsertionSort", tipos[tipo], tamanho, -1, -1);
            }
        }

        free(vetor);
        free(copia);
    }

    return 0;
}
