#ifndef ORDENACAO_H
#define ORDENACAO_H


// E s t r u t u r a de Dados para o TP


typedef struct Item {
int chave ;
}Item ;

typedef int Elemento ;



void selectionsort(Item *v, int n);
void Bubblesort(Item* v, int n );
void Inserctionsort(Item* v, int n );
void quickSortrecursivo(Item* A, int n);
void Ordena(int Esq, int Dir, Item *A);
void QuickSort_iterativo(Item *A, int n);
void Particao(int Esq, int Dir, int *i, int *j, Item *A);
void print_vetor(Item* v, int n);
#endif