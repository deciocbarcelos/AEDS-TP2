#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define verbose 0

unsigned long long comparacoes = 0;
unsigned long long trocas = 0;

int menu() {
    int opcao;
    printf("1. Ordenacao Selection Sort\n");
    printf("2. Ordenacao Insertion Sort\n");
    printf("3. Ordenacao Bubble Sort\n");
    printf("4. Ordenacao Quick Sort\n");
    printf("5. Ordenacao Quick Sort com Insercao\n");
    printf("6. Ordenacao Quick Sort recursivo\n");
    printf("7. Ordenacao Quick Sort com Particao e Mediana de 3\n");
    printf("8. Ordenacao Quick Sort com Particao e Mediana de 5\n");
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
    clock_t inicio = clock();

    for (i = 0; i < n - 1; i++) {
        Min = i;
        for (j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].chave < v[Min].chave) {
                Min = j;
            }
        }

        // Só incrementa a contagem de trocas se Min for diferente de i, ou seja, uma troca real ocorreu
        if (Min != i) {
            aux = v[Min];
            v[Min] = v[i];
            v[i] = aux;
            trocas++;
        }

        if (verbose) {
            printf("SelectionSort: passo %d\n", i + 1);
            printf("trocou %d com %d\n", v[i].chave, v[Min].chave);
            print_vetor(v, n);
        }
    }
    printf("comparacoes: %llu\n", comparacoes);
    printf("trocas: %llu\n", trocas);
       
    


   clock_t fim = clock();
   double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
   printf("Tempo total de execucao %.2f ", tempo_segundos );
}

void Inserctionsort(Item* v, int n) {
    int i, j;
    Item aux;
    clock_t inicio = clock();

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
    printf("comparacoes: %llu\n", comparacoes);
    printf("trocas: %llu\n", trocas);
     
    


   clock_t fim = clock();
   double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
   printf("Tempo total de execucao %.2f ", tempo_segundos );
}


void BubbleSort(Item* v, int n) {
    zerar_contagens();
    int i, j;
    int trocou;
    clock_t inicio = clock();
    Item aux;

    for (i = 0; i < n - 1; i++) {
        trocou = 0;  // Flag para indicar se houve troca
        for (j = 1; j < n - i; j++) {
            comparacoes++;
            if (v[j].chave < v[j - 1].chave) {
                aux = v[j];
                v[j] = v[j - 1];
                v[j - 1] = aux;
                trocas++;
                trocou = 1;
            }
        }

        if (verbose) {
            printf("BubbleSort: passo %d\n", i);
            print_vetor(v, n);
        }

        if (!trocou) break;  // Se nenhuma troca ocorreu, o vetor já está ordenado
    }
    printf("comparacoes: %llu\n", comparacoes);
    printf("trocas: %llu\n", trocas);

    clock_t fim = clock();
    double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo total de execucao %.2f ", tempo_segundos );
}




void Particao(int Esq, int Dir, int* i, int* j, Item* A) {
    clock_t inicio = clock();
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
            trocas ++;

        }
        comparacoes++;
    } while (*i <= *j);
    
    if (verbose) {
        printf("Particao: Esq=%d, Dir=%d, i=%d, j=%d, Pivô=%d\n", Esq, Dir, *i, *j, pivo.chave);
        printf("trocou %d com %d\n", A[*i].chave, A[*j].chave);
        print_vetor(A, Dir - Esq + 1);
        
    }
    printf("comparacoes: %llu\n", comparacoes);
    printf("trocas: %llu\n", trocas);
     


   clock_t fim = clock();
   double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
   printf("Tempo total de execucao %.2f ", tempo_segundos );
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
    clock_t inicio = clock();

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
            trocas++;
        }

        // Se existirem elementos à direita do pivô, empilha os índices correspondentes
        if (i < Dir) {
            stack[++topo] = i;
            stack[++topo] = Dir;
            trocas++;
        }
        comparacoes++;
        if (verbose) {
            printf("QuickSort Iterativo: Empilhando [%d, %d] e [%d, %d]\n", Esq, j, i, Dir);
            printf("trocou %d com %d\n", A[i].chave, A[j].chave);
            print_vetor(A, n);
        }
    }
    
    printf("comparacoes: %llu\n", comparacoes);
    printf("trocas: %llu\n", trocas);
       


   clock_t fim = clock();
   double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
   printf("Tempo total de execucao %.2f ", tempo_segundos );
}

    // Libera a memória da pilha
    

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
        while (A[*i].chave < pivo.chave) {
            (*i)++;
            comparacoes++;
        }
        while (A[*j].chave > pivo.chave) {
            (*j)--;
            comparacoes++;
        }
        if (*i <= *j) {
            Item aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*i)++;
            (*j)--;
            trocas++;
        }
    } while (*i <= *j);
    
    if (verbose) {
        printf("ParticaoMediana3: Esq=%d, Dir=%d, i=%d, j=%d, Pivo=%d\n", Esq, Dir, *i, *j, pivo.chave);
        // Assumindo que print_vetor imprime o vetor a partir de A[Esq] até A[Dir]
        print_vetor(A + Esq, Dir - Esq + 1);
    }
}

void ordenaMediana3(int Esq, int Dir, Item* A) {
    int i, j;
    particaoMediana3(Esq, Dir, &i, &j, A);
    if (Esq < j) ordenaMediana3(Esq, j, A);
    if (i < Dir) ordenaMediana3(i, Dir, A);
}

void quickSortMediana3(Item* A, int n) {
    srand(time(NULL));  // Inicializa a semente do gerador de números aleatórios
    
    clock_t inicio = clock();
    
    ordenaMediana3(0, n - 1, A);
    
    clock_t fim = clock();
    
    double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo total de execucao: %.2f segundos\n", tempo_segundos);
    printf("comparacoes: %llu\n", comparacoes);
    printf("trocas: %llu\n", trocas);
}
void quickSortComInsercao(Item* A, int n) {
    Ordena(0, n - 1, A);
}


// Função para calcular a mediana de cinco elementos
int medianaDeCinco(Item* A, int k1, int k2, int k3, int k4, int k5) {
    int valores[5] = {A[k1].chave, A[k2].chave, A[k3].chave, A[k4].chave, A[k5].chave};
    // Ordena os cinco valores
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (valores[i] > valores[j]) {
                int temp = valores[i];
                valores[i] = valores[j];
                valores[j] = temp;
            }
        }
    }
    return valores[2];  // A mediana será o terceiro valor após a ordenação
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
        while (A[*i].chave < pivo) {
            (*i)++;
            comparacoes++;
        }
        while (A[*j].chave > pivo) {
            (*j)--;
            comparacoes++;
        }
        if (*i <= *j) {
            Item aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*i)++;
            (*j)--;
            trocas++;
        }
    } while (*i <= *j);

    if (verbose) {
        printf("ParticaoMediana5: Esq=%d, Dir=%d, i=%d, j=%d, Pivo=%d\n", Esq, Dir, *i, *j, pivo);
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

    clock_t inicio = clock();  // Início da medição do tempo

    ordenaMediana5(0, n - 1, A);

    clock_t fim = clock();  // Fim da medição do tempo
    double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo total de execucao: %.2f segundos\n", tempo_segundos);
    printf("comparacoes: %llu\n", comparacoes);
    printf("trocas: %llu\n", trocas);;
}

void gerar_vetor_aleatorio(Item* v, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        v[i].chave = rand() % 1000000;
    }
}

void zerar_contagens() {
    comparacoes = 0;
    trocas = 0;
}
