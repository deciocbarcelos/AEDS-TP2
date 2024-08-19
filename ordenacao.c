#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void selectionsort(Item* v, int n) {
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

void Inserctionsort(Item* v, int n) {
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

void BubbleSort(Item* v, int n) {
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

void Particao(int Esq, int Dir, int* i, int* j, Item* A) {
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

void Ordena(int Esq, int Dir, Item* A) {
    int i, j;
    particao(Esq, Dir, &i, &j, A);
    if (Esq < j) ordena(Esq, j, A);
    if (i < Dir) ordena(i, Dir, A);
}

void quickSortrecursivo(Item* A, int n) {
    ordena(0, n - 1, A);
}

void QuickSort_iterativo(Item* A, int n) {
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
int medianaDeTres(Item* v, int a, int b, int c) {
    if ((v[a].chave > v[b].chave) != (v[a].chave > v[c].chave))
        return a;
    else if ((v[b].chave > v[a].chave) != (v[b].chave > v[c].chave))
        return b;
    else
        return c;
}

void particaoMediana3(int Esq, int Dir, int* i, int* j, Item* A) {
    // Seleciona três índices aleatórios
    int k1 = Esq + rand() % (Dir - Esq + 1);
    int k2 = Esq + rand() % (Dir - Esq + 1);
    int k3 = Esq + rand() % (Dir - Esq + 1);

    // Determina o índice do pivô usando a mediana de três
    int pivo_indice = medianaDeTres(A, k1, k2, k3);
    Item pivo = A[pivo_indice];
    
    // Particionamento
    *i = Esq;
    *j = Dir;
    
    do {
        while (A[*i].chave < pivo.chave) (*i)++;
        while (A[*j].chave > pivo.chave) (*j)--;
        if (*i <= *j) {
            Item aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void ordenaMediana3(int Esq, int Dir, Item* A) {
    int i, j;
    particaoMediana3(Esq, Dir, &i, &j, A);
    if (Esq < j) ordenaMediana3(Esq, j, A);
    if (i < Dir) ordenaMediana3(i, Dir, A);
}

void quickSortMediana3(Item* A, int n) {
    srand(time(NULL));  // Inicializa a semente do gerador de números aleatórios
    ordenaMediana3(0, n - 1, A);
}
void quickSortComInsercao(Item* A, int n) {
    ordena(0, n - 1, A);
}

// Função para encontrar a mediana de 5 elementos
int medianaDeCinco(Item* v, int a, int b, int c, int d, int e) {
    Item arr[] = {v[a], v[b], v[c], v[d], v[e]};
    
    // Ordena os cinco elementos para encontrar a mediana
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (arr[j].chave < arr[i].chave) {
                Item temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // A mediana é o elemento do meio
    return arr[2].chave;
}
void particaoMediana5(int Esq, int Dir, int* i, int* j, Item* A) {
    // Seleciona cinco índices aleatórios
    int k1 = Esq + rand() % (Dir - Esq + 1);
    int k2 = Esq + rand() % (Dir - Esq + 1);
    int k3 = Esq + rand() % (Dir - Esq + 1);
    int k4 = Esq + rand() % (Dir - Esq + 1);
    int k5 = Esq + rand() % (Dir - Esq + 1);

    // Determina a mediana de cinco
    int pivo = medianaDeCinco(A, k1, k2, k3, k4, k5);
    
    // Particionamento
    *i = Esq;
    *j = Dir;

    do {
        while (A[*i].chave < pivo) (*i)++;
        while (A[*j].chave > pivo) (*j)--;
        if (*i <= *j) {
            Item aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);

    if (verbose) {
        printf("ParticaoMediana5: Esq=%d, Dir=%d, i=%d, j=%d, Pivô=%d\n", Esq, Dir, *i, *j, pivo);
        print_vetor(A, Dir - Esq + 1);
    }
}

void ordenaMediana5(int Esq, int Dir, Item* A) {
    int i, j;
    particaoMediana5(Esq, Dir, &i, &j, A);
    if (Esq < j) ordenaMediana5(Esq, j, A);
    if (i < Dir) ordenaMediana5(i, Dir, A);
}

void quickSortMediana5(Item* A, int n) {
    srand(time(NULL));  // Inicializa a semente do gerador de números aleatórios
    ordenaMediana5(0, n - 1, A);
}
void executar_experimento(Item* v, int n, void (*sort_func)(Item*, int)) {
    long long int comparacoes = 0;
    long long int copias = 0;

    clock_t inicio = clock();
    sort_func(v, n);
    clock_t fim = clock();

    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo de Execucao: %.3f segundos\n", tempo_execucao);
    printf("Comparacoes: %lld\n", comparacoes);
    printf("Copias: %lld\n", copias);
}
void gerar_vetor_aleatorio(Item* v, int n) {
    for (int i = 0; i < n; i++) {
        v[i].chave = rand() % 1000000;
    }
}