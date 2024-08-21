#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define verbose 1

int comparacoes = 0;
int trocas = 0;

int menu() {
    int opcao;
    printf("1. Ordenacao Selection Sort\n");
    printf("2. Ordenacao Insertion Sort\n");
    printf("3. Ordenacao Bubble Sort\n");
    printf("4. Ordenacao Quick Sort\n");
    printf("5. Ordenacao Quick Sort com Inserção\n");
    printf("6. Ordenacao Quick Sort recursivo\n");
    printf("7. Ordenacao Quick Sort com Partição e Mediana de 3\n");
    printf("8. Ordenacao Quick Sort com Partição e Mediana de 5\n");
    printf("9. Ordenacao Quick Sort iterativo\n");
    printf("escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

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
            comparacoes++;
            if (v[j].chave < v[Min].chave) {
                Min = j;
                trocas++;
            }
        }
        aux = v[Min];
        v[Min] = v[i];
        v[i] = aux;

        if (verbose) {
            printf("SelectionSort: passo %d\n", i + 1);
            printf("trocou %d com %d\n", v[i].chave, v[Min].chave);
            print_vetor(v, n);
        }
    }
    printf("comparacoes: %d\n", comparacoes);
    printf("trocas: %d\n", trocas);
}

void Inserctionsort(Item* v, int n) {
    int i, j;
    Item aux;

    for (i = 1; i < n; i++) {
        aux = v[i];
        j = i - 1;
        comparacoes++;
        while (j >= 0 && aux.chave < v[j].chave) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
            trocas++;
        }

        v[j + 1] = aux;
        if (verbose) {
            printf("InsertionSort: passo %d\n", i);
            printf("trocou %d com %d\n", v[i].chave, v[j + 1].chave);
            print_vetor(v, n);
        }
    }
    printf("comparacoes: %d\n", comparacoes);
    printf("trocas: %d\n", trocas);
}

void BubbleSort(Item* v, int n) {
    int i, j;


    Item aux;

    for (i = 0; i < n - 1; i++) {
        for (j = 1; j < n - i; j++) {
            comparacoes++;
            if (v[j].chave < v[j - 1].chave) {
                aux = v[j];
                v[j] = v[j - 1];
                v[j - 1] = aux;
                trocas++;
            }
        }
        
        if (verbose) {
            printf("BubbleSort: passo %d\n", i);
            printf("trocou %d com %d\n", v[i].chave, v[j].chave);
            print_vetor(v, n);
        }
    }
    printf("comparacoes: %d\n", comparacoes);
    printf("trocas: %d\n", trocas);
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
    comparacoes++;
    if (verbose) {
        printf("Particao: Esq=%d, Dir=%d, i=%d, j=%d, Pivô=%d\n", Esq, Dir, *i, *j, pivo.chave);
        printf("trocou %d com %d\n", A[*i].chave, A[*j].chave);
        print_vetor(A, Dir - Esq + 1);
    }
    printf("comparacoes: %d\n", comparacoes);
}

void Ordena(int Esq, int Dir, Item* A) {
    int i, j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j) Ordena(Esq, j, A);
    if (i < Dir) Ordena(i, Dir, A);
}

void quickSortrecursivo(Item* A, int n) {
    Ordena(0, n - 1, A);
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
        Particao(Esq, Dir, &i, &j, A);

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
        comparacoes++;
        if (verbose) {
            printf("QuickSort Iterativo: Empilhando [%d, %d] e [%d, %d]\n", Esq, j, i, Dir);
            printf("trocou %d com %d\n", A[i].chave, A[j].chave);
            print_vetor(A, n);
        }
    }
    printf("comparacoes: %d\n", comparacoes);

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
    comparacoes++;
    if (verbose) {
        printf("ParticaoMediana3: Esq=%d, Dir=%d, i=%d, j=%d, Pivo=%d\n", Esq, Dir, *i, *j, pivo.chave);
        print_vetor(A, Dir - Esq + 1);
    }
    printf("comparacoes: %d\n", comparacoes);
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
    Ordena(0, n - 1, A);
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
    comparacoes++;
    if (verbose) {
        printf("ParticaoMediana5: Esq=%d, Dir=%d, i=%d, j=%d, Pivo=%d\n", Esq, Dir, *i, *j, pivo);
        print_vetor(A, Dir - Esq + 1);
    }
    printf("comparacoes: %d\n", comparacoes);
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