#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variável de controle para o modo verbose
int verbose = 0; // 1 para ativar, 0 para desativar

void print_vetor(Item* v, int n) {
    if (verbose) {
        for (int i = 0; i < n; i++) {
            printf("%d ", v[i].chave);
        }
        printf("\n");
    }
}

void selectionSort(Item* v, int n) {
    int i, j, Min;
    Item aux;

    for (i = 0; i < n - 1; i++) {
        Min = i;
        for (j = i + 1; j < n; j++) {
            if (v[j].chave < v[Min].chave) {
                Min = j;
            }
        }
        aux = v[Min];
        v[Min] = v[i];
        v[i] = aux;

        if (verbose) {
            printf("SelectionSort: passo %d\n", i + 1);
            print_vetor(v, n);
        }
    }
}

void insertionSort(Item* v, int n) {
    int i, j;
    Item aux;

    for (i = 1; i < n; i++) {
        aux = v[i];
        j = i - 1;
        while (j >= 0 && aux.chave < v[j].chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;

        if (verbose) {
            printf("InsertionSort: passo %d\n", i);
            print_vetor(v, n);
        }
    }
}

void bubbleSort(Item* v, int n) {
    int i, j;
    Item aux;

    for (i = 0; i < n - 1; i++) {
        for (j = 1; j < n - i; j++) {
            if (v[j].chave < v[j - 1].chave) {
                aux = v[j];
                v[j] = v[j - 1];
                v[j - 1] = aux;
            }
        }

        if (verbose) {
            printf("BubbleSort: passo %d\n", i + 1);
            print_vetor(v, n);
        }
    }
}

void particao(int Esq, int Dir, int* i, int* j, Item* A) {
    Item pivo, aux;
    *i = Esq;
    *j = Dir;
    pivo = A[(*i + *j) / 2]; // Obtém o pivô

    do {
        while (pivo.chave > A[*i].chave) (*i)++;
        while (pivo.chave < A[*j].chave) (*j)--;
        if (*i <= *j) {
            aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);

    if (verbose) {
        printf("Particao: Esq=%d, Dir=%d, i=%d, j=%d, Pivô=%d\n", Esq, Dir, *i, *j, pivo.chave);
        print_vetor(A, Dir - Esq + 1);
    }
}

void ordena(int Esq, int Dir, Item* A) {
    int i, j;
    particao(Esq, Dir, &i, &j, A);
    if (Esq < j) ordena(Esq, j, A);
    if (i < Dir) ordena(i, Dir, A);
}

void quickSortrecursivo(Item* A, int n) {
    ordena(0, n - 1, A);
}

void quickSortIterativo(Item* A, int n) {
    // Cria uma pilha para armazenar os índices das sublistas
    int* stack = (int*)malloc(n * sizeof(int));

    // Inicializa a pilha com os limites da lista inteira
    int topo = -1;
    stack[++topo] = 0;
    stack[++topo] = n - 1;

    // Continua até que a pilha esteja vazia
    while (topo >= 0) {
        // Desempilha Dir e Esq
        int Dir = stack[topo--];
        int Esq = stack[topo--];

        // Realiza a partição
        int i, j;
        particao(Esq, Dir, &i, &j, A);

        // Se existirem elementos à esquerda do pivô, empilha os índices correspondentes
        if (Esq < j) {
            stack[++topo] = Esq;
            stack[++topo] = j;
        }

        // Se existirem elementos à direita do pivô, empilha os índices correspondentes
        if (i < Dir) {
            stack[++topo] = i;
            stack[++topo] = Dir;
        }

        if (verbose) {
            printf("QuickSort Iterativo: Empilhando [%d, %d] e [%d, %d]\n", Esq, j, i, Dir);
            print_vetor(A, n);
        }
    }

    // Libera a memória da pilha
    free(stack);
}