#include<stdio.h>
#include<stdlib.h>
#include "time.h"
#include "ordenacao.h"
#define verbose 1

int main(){

    
      

    Item v[] = {9, 8, 1, 7, 3, 5, 2, 4, 6};
    int n = sizeof(v) / sizeof(v[0]);

    int opcao = menu();
    selectionsort(v, n);
    printf("vetor final\n");
    print_vetor(v, n);

    /*switch (opcao) {
        case 1:
            printf("Ordenação Selection Sort\n");
            executar_experimento(v, n, selectionsort);
            break;
        case 2:
            printf("Ordenação Insertion Sort\n");
            executar_experimento(v, n, Inserctionsort);
            break;
        case 3:
            printf("Ordenação Bubble Sort\n");
            executar_experimento(v, n, BubbleSort);
            break;
        case 4:
            printf("Ordenação Quick Sort\n");
            executar_experimento(v, n, quickSortrecursivo);
            break;
        case 5:
            printf("Ordenação Quick Sort com Inserção\n");
            executar_experimento(v, n, quickSortComInsercao);
            break;
        case 6:
            printf("Ordenação Quick Sort recursivo\n");
            executar_experimento(v, n, quickSortrecursivo);
            break;
        case 7:
            printf("Ordenação Quick Sort com Partição e Mediana de 3\n");
            executar_experimento(v, n, quickSortMediana3);
            break;
        case 8:
            printf("Ordenação Quick Sort com Partição e Mediana de 5\n");
            executar_experimento(v, n, quickSortMediana5);
            break;
        case 9:
            printf("Ordenação Quick Sort iterativo\n");
            executar_experimento(v, n, QuickSort_iterativo);
            break;*/

    printf("escolheu %d\n", opcao);
    return 0;
}






    

  