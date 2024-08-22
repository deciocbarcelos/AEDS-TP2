#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "time.h"
#include "ordenacao.h"
#define verbose 1

Item* lerArquivo(const char *nomeArquivo, int *quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Lê o conteúdo da linha do arquivo
    char linha[1024];
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Erro ao ler a linha do arquivo.\n");
        fclose(arquivo);
        return NULL;
    }
    fclose(arquivo);

    // Conta a quantidade de números na linha
    int count = 1;
    for (char *p = linha; *p != '\0'; p++) {
        if (*p == ',') {
            count++;
        }
    }
    
    // Aloca o vetor de Items
    Item *vetor = (Item *)malloc(count * sizeof(Item));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return NULL;
    }

    // Divide a linha e converte os números para o vetor de Items
    char *token = strtok(linha, ",");
    int i = 0;
    while (token != NULL) {
        vetor[i].chave = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }

    *quantidade = count;
    return vetor;
}



int main(){

    int quantidade;
    char nomeArquivo[50];  

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    Item *v = lerArquivo(nomeArquivo, &quantidade);

    int opcao = menu();

    switch (opcao) {
        case 1:
            printf("Ordenação Selection Sort\n");
            selectionsort(v, quantidade);
            printf("vetor final\n");
            print_vetor(v, quantidade);
            break;
        case 2:
            printf("Ordenação Insertion Sort\n");
            Inserctionsort(v, quantidade);
            printf("vetor final\n");
            print_vetor(v, quantidade);
            break;
        case 3:
            printf("Ordenação bubble sort\n");
            BubbleSort(v, quantidade);
            printf("vetor final\n");
            print_vetor(v, quantidade);
            break;
        case 4:
            printf("Ordenação quick sort\n");
            QuickSort_iterativo(v, quantidade);
            printf("vetor final\n");
            print_vetor(v, quantidade);
            break;
        case 5:
            printf("Ordenação quick sort com inserção\n");
            quickSortComInsercao(v, quantidade);
            printf("vetor final\n");
            print_vetor(v, quantidade);
            break;
        case 6:
            printf("Ordenação quick sort recursivo\n");
            quickSortrecursivo(v, quantidade);
            printf("vetor final\n");
            print_vetor(v, quantidade);
            break;
        case 7:
            printf("Ordenação quick sort com partição e mediana de 3\n");
            quickSortMediana3(v, quantidade);
            printf("vetor final\n");
            print_vetor(v, quantidade);
            break;
        case 8:
            printf("Ordenação quick sort com partição e mediana de 5\n");
            quickSortMediana5(v, quantidade);
            printf("vetor final\n");
            print_vetor(v, quantidade);
            break;
        default:
            printf("Escolha uma opção válida\n");
            break;
    }   
            
    return 0;
}






    

  