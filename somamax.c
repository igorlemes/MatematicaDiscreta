#include <stdio.h>
#include <math.h>


int max(int a, int b){
    if(a>=b){
        return a;
    } else {
        return b;
    }
}
int main(){
    
    
    int n;
    scanf("%d", &n);
    
    int *A = malloc(sizeof(int)*n);
    
    for (int i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }
    

    int localMax = 0;
    int globalMax = -INFINITY;
    int index[2];


    for (int i = 0; i < n; i++){
        localMax = max(A[i], A[i]+ localMax);
        if (localMax > globalMax){
            globalMax = localMax
        }
        
    }
    

    return 0;
    
}