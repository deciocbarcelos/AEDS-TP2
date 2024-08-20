#include<stdio.h>
#include<stdlib.h>
#include "time.h"
#include "ordenacao.h"
#define verbose 1

int main(){

    Item v[] = {9, 8, 1, 7, 3, 5, 2, 4, 6};
    int n = sizeof(v) / sizeof(v[0]);

    quickSortMediana3(v, n);
    print_vetor(v, n);

    return 0;
}






    
