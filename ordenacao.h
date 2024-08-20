#ifndef ORDENACAO_H
#define ORDENACAO_H


// E s t r u t u r a de Dados para o TP


typedef struct Item {
int chave ;
}Item ;

typedef int Elemento ;



void selectionsort(Item *v, int n); //Funcionando correto
void BubbleSort(Item* v, int n );  //Funcionando correto
void Inserctionsort(Item* v, int n );//Funcionando correto
void quickSortrecursivo(Item* A, int n); //Funcionando correto
void Ordena(int Esq, int Dir, Item *A);
void QuickSort_iterativo(Item *A, int n);// Funcionando correto
void Particao(int Esq, int Dir, int *i, int *j, Item *A);
void print_vetor(Item* v, int n);
void quickSortComInsercao(Item* A, int n); // Funcionando correto
int medianaDeCinco(Item* v, int a, int b, int c, int d, int e);
void quickSortMediana5(Item* A, int n); //Funcionando correto
void ordenaMediana5(int Esq, int Dir, Item* A);
void particaoMediana5(int Esq, int Dir, int* i, int* j, Item* A);
void executar_experimento(Item* v, int n, void (*sort_func)(Item*, int));
void gerar_vetor_aleatorio(Item* v, int n);
void quickSortMediana3(Item* A, int n); // Não esta funcionando corretamente
void ordenaMediana3(int Esq, int Dir, Item* A);
void particaoMediana3(int Esq, int Dir, int* i, int* j, Item* A) ;


#endif