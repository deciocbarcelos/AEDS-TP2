#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "time.h"
#include "ordenacao.h"

// Função para ler um arquivo e preencher um vetor de Items com os números da linha
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

int main(int argc, char *argv[]) {
    int verbose = 0;
    int quick = 0;
    char tipoOrdenacao[50] = "";
    char nomeArquivo[100] = "";

    // Verifica os argumentos passados
    if (argc < 3) {
        printf("Uso: %s -q <metodo ordenacao> <nome entrada>.txt\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-verbose") == 0) {
            verbose = 1;
        }
        if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "-quick") == 0) {
            quick = 1;
            if (i + 1 < argc) {
                strcpy(tipoOrdenacao, argv[i + 1]);
                strcpy(nomeArquivo, argv[i + 2]);
            }
        }
    }

    int quantidade;
    Item *v = lerArquivo(nomeArquivo, &quantidade);

    if (v == NULL) {
        return 1; // Se houve um erro ao ler o arquivo, termina o programa
    }

    // Executar apenas se verbose estiver ativo
    if(verbose == 1) {
        int opcao = menu();

        switch (opcao) {
            case 1:
                printf("Ordenação Selection Sort\n");
                selectionsort(v, quantidade);
                break;
            case 2:
                printf("Ordenação Insertion Sort\n");
                Inserctionsort(v, quantidade);
                break;
            case 3:
                printf("Ordenação bubble sort\n");
                BubbleSort(v, quantidade);
                break;
            case 4:
                printf("Ordenação quick sort\n");
                QuickSort_iterativo(v, quantidade);
                break;
            case 5:
                printf("Ordenação quick sort com inserção\n");
                quickSortComInsercao(v, quantidade);
                break;
            case 6:
                printf("Ordenação quick sort recursivo\n");
                quickSortrecursivo(v, quantidade);
                break;
            case 7:
                printf("Ordenação quick sort com partição e mediana de 3\n");
                quickSortMediana3(v, quantidade);
                break;
            case 8:
                printf("Ordenação quick sort com partição e mediana de 5\n");
                quickSortMediana5(v, quantidade);
                break;
            default:
                printf("Escolha uma opção válida\n");
                break;
        } 
        printf("Vetor final\n");
        print_vetor(v, quantidade);
    }

    // Executar o quick sort direto se quick estiver ativo
    if(quick == 1 && verbose == 0) {
        if (strcmp(tipoOrdenacao, "quicksort_iterativo") == 0) {
            QuickSort_iterativo(v, quantidade);
        } else if (strcmp(tipoOrdenacao, "quicksort_com_insercao") == 0) {
            quickSortComInsercao(v, quantidade);
        } else if (strcmp(tipoOrdenacao, "quicksort_recursivo") == 0) {
            quickSortrecursivo(v, quantidade);
        } else if (strcmp(tipoOrdenacao, "quicksort_mediana3") == 0) {
            quickSortMediana3(v, quantidade);
        } else if (strcmp(tipoOrdenacao, "quicksort_mediana5") == 0) {
            quickSortMediana5(v, quantidade);
        } else {
            printf("Tipo de ordenação desconhecido: %s\n", tipoOrdenacao);
            free(v);
            return 1;
        }
        printf("Vetor final\n");
        print_vetor(v, quantidade);
    }

    free(v); // Libera a memória alocada

    return 0;
}
