#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>

void selectionsort(Item* v, int n){
    int i, j, Min;
    Item aux;

    for (i = 0; i < n - 1; i++) {
      Min = i;
      for (j = i + 1 ; j < n; j++) {
         if ( v[j].chave < v[Min].chave){
             Min = j;
}
}
           aux = v[Min];
           v[Min] = v[i];
           v[i] = aux;
}
}

void Inserctionsort(Item* v, int n ){
int i,j;
Item aux;
for (i = 1; i < n; i++){
aux = v[i];
j = i - 1;
while ( ( j >= 0 ) && ( aux.chave < v[j].chave ) ) {
v[j + 1] = v[j];
j--;
}
v[j + 1] = aux;
}
}

void Bubblesort(Item* v, int n ) {
int i, j;
Item aux;
for(int i = 0 ; i < n-1 ; i++ ) {
for(int j = 1 ; j < n-i ; j++ ) {
if ( v[j].chave < v[j-1].chave ) {
aux = v[j];
v[j] = v[j-1];
v[j-1] = aux;
} // if
}
}
}

void quickSort_recursivo(Item* v, int baixo, int alto) {
    if (baixo < alto) {
        int pivot = v[(baixo + alto) / 2].chave; // Escolhe o pivô como o elemento do meio
        int i = baixo;
        int j = alto;

        // Particionamento
        while (i <= j) {
            while (v[i].chave < pivot) i++;
            while (v[j].chave > pivot) j--;

            if (i <= j) {
                // Troca os elementos v[i] e v[j]
                Item temp = v[i];
                v[i] = v[j];
                v[j] = temp;
                i++;
                j--;
            }
        }

        // Ordena recursivamente as sublistas
        if (baixo < j) quickSort_recursivo(v, baixo, j);
        if (i < alto) quickSort_recursivo(v, i, alto);
    }
}

void Particao(int Esq, int Dir, int *i, int *j, Item *A){
Item pivo, aux;
*i = Esq; *j = Dir;
pivo = A[(*i + *j)/2]; /* obtem o pivo x */
do
{
while (pivo.chave > A[*i].chave) (*i)++;
while (pivo.chave < A[*j].chave) (*j)--;
if (*i <= *j)
{
aux = A[*i]; A[*i] = A[*j]; A[*j] = aux;
(*i)++; (*j)--;
}
} while (*i <= *j);
}

void Ordena(int Esq, int Dir, Item *A)
{
int i,j;
Particao(Esq, Dir, &i, &j, A);
if (Esq < j) Ordena(Esq, j, A);
if (i < Dir) Ordena(i, Dir, A);
}
void QuickSort_iterativo(Item *A, int n){
Ordena(0, n-1, A);
}





