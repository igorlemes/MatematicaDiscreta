#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(){
    /*
    (O Problema)
    O problema é encontrar a soma máxima de um subarray contíguo.
    A primeira entrada é n, que representa o tamanho do array. 
    Logo após isso, temos os n valores do array guardados dinamicamente na memória.

    (Solução)
    O algoritmo para encontrar a maior soma, consiste em buscar elemento por elemento, no array A, qual a maior soma dentre todos os subarrays que terminam no i-ésimo elemento.
    Ao identificar, atribuimos os indices de início e fim do subarray.
    
    (Análise Assintótica)
    Desta maneira, conseguimos que a solução seja em O(n), pois cada elemento é verificado somente uma vez, caso ele faça parte do subarray com maior soma, o índice é atualizado, assim como o valor de soma maxima.
    O mesmo ocorre com o crescimento assistótico de memória, que tem O(n), pois os elementos são guardados somente uma vez.
    
    */
    
    int n;
    scanf("%d", &n);
    
    int *A = (int*)malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }
    

    int localMax = 0;
    int globalMax = -__INT_MAX__;
    int index[2];

    index[0] = 0;
    index[1] = 0;


    for (int i = 0; i < n; i++){

        if(A[i] >= A[i] + localMax){
            localMax = A[i];
            index[0] = i;
            index[1] = i;
        } else {
            localMax = A[i] + localMax;
            index[1] = i;
        }
        if (localMax > globalMax){  
            globalMax = localMax;
        }
        
    }

    if(globalMax < 0){
        globalMax = 0;
    }

    printf("Soma: %d\n", globalMax);  
    printf("Índices: %d a %d\n", index[0], index[1]);

    free(A);
    return 0;
}