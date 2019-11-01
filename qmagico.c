#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int **alocarQuadrado(int n){
    int** quadradoMagico = (int**)malloc(n*sizeof(int*));

    for (int i = 0; i < n; i++){
        quadradoMagico[i] = (int*)malloc(n*sizeof(int));
    }
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            quadradoMagico[i][j] = 0;
        }
    }

    return quadradoMagico;
}

void desalocarQuadrado(int** quadradoMagico, int n){
    for (int i = 0; i < n; i++){
        free(quadradoMagico[i]);
    }
    free(quadradoMagico);
}

void printQuadradoMagico(int **quadradoMagico, int n){
    printf("n = %d, Soma = %d\n",  n, n*(n*n+1)/2); 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            printf("%3d ", quadradoMagico[i][j]); 
        }
        printf("\n"); 
    }
}

int **tamanhoQuatro(int n){

    
    /*
    No quadrado mágico de 4x4 (ou qualquer multiplo de 4), nós temos que primeiramente preencher todo o quadrado mágico com os valores de de cada posição, de 1 até n², no caso 16.
    Após isso nós substituimos os valores seguindo uma regra, de que cada posição terá o valor (n*n+1)-quadradoMagico[i][j] 
    Para facilitar, dividimos o quadrado mágico em cinco quadrados menores. Quatro deles tem lado n/4, superior direito e esquerdo, inferior direito e esquerdo, enquanto um deles tem lado n/2 e calcula os valores no centro do quadrado mágico, basicamente permutando os valores.
    
    Após substituirmos todos os valores das posições, o quadrado mágico de lado 4n está pronto.   
    */
    
    int **quadradoMagico = alocarQuadrado(n);
    

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            quadradoMagico[i][j] = (n*i) + j + 1; 
        }
    } 
    
    /*Tamanho (n/4)*(n/4) */ 
    for (int i = 0; i < n/4; i++){
        for (int j = 0; j < n/4; j++){
            quadradoMagico[i][j] = (n*n + 1) - quadradoMagico[i][j]; 
        }
    }
    
    /*Tamanho (n/4)*(n/4) */ 
    for (int i = 0; i < n/4; i++){
        for (int j = 3 * (n/4); j < n; j++){
            quadradoMagico[i][j] = (n*n + 1) - quadradoMagico[i][j]; 
        }
    }
        
    /*Tamanho (n/4)*(n/4) */ 
    for (int i = 3 * n/4; i < n; i++){
        for (int j = 0; j < n/4; j++){
            quadradoMagico[i][j] = (n*n+1) - quadradoMagico[i][j]; 
        }
    }
    
    /*Tamanho (n/4)*(n/4) */ 
    for (int i = 3 * n/4; i < n; i++){
        for (int j = 3 * n/4; j < n; j++){
            quadradoMagico[i][j] = (n*n + 1) - quadradoMagico[i][j]; 
        }
    }   
    
    /*Tamanho (n/2)*(n/2) */ 
    for (int i = n/4; i < 3 * n/4; i++){
        for (int j = n/4; j < 3 * n/4; j++){
            quadradoMagico[i][j] = (n*n + 1) - quadradoMagico[i][j]; 
        }
    }
    
    return quadradoMagico;
}
int **tamanhoImpar(int n){

    int tamanho = n * n;
    int **quadradoMagico = alocarQuadrado(n);
    /*O algoritmo para preenchimento de qualquer quadrado mágico de lado impar, segue as seguintes regras:
    Primeiramente a posição inicial será na linha int(n/2) e na coluna n-1.
    Os valores são então colocados em ordem de 1 até n². Após cada valor adicionado, basta colocar o próximo valor na linha anterior e na próxima coluna (i-- e j++).
    É preciso, entretanto, tratar o quadrado mágico como um toro, onde estão todos conectados os lados.
    */        
    
    int i = n/2; 
    int j = n-1; 
    
    for (int index = 1; index <= tamanho; ) { 
        if (i==-1 && j==n){ 
            j = n-2; 
            i = 0; 
        } 
        else { 
            if (j == n){
                j = 0; 
            } 
            if (i < 0){
                i=n-1; 
            } 
        } 
        if (quadradoMagico[i][j]){ 
            j -= 2; 
            i++; 
            continue; 
        } else {
            quadradoMagico[i][j] = index++;
        }
        
        j++; i--; 
    }

    return quadradoMagico;
}

int **tamanhoSeis(int n){
    int tamanho = n * n;
    int metadeDeN = n / 2;
    int tamanhoSubGrid = tamanho / 4;

    int** subGrid = tamanhoImpar(metadeDeN);
    int gridFactors[] = {0, 2, 3, 1};
    int** quadradoMagico = alocarQuadrado(n);

    for (int linha = 0; linha < n; linha++) {
        for (int coluna = 0; coluna < n; coluna++) {
            int grid = (linha / metadeDeN) * 2 + (coluna / metadeDeN);
            quadradoMagico[linha][coluna] = subGrid[linha % metadeDeN][coluna % metadeDeN];
            quadradoMagico[linha][coluna] += gridFactors[grid] * tamanhoSubGrid;
        }
    }

    int nColsLeft = metadeDeN / 2;
    int nColsRight = nColsLeft - 1;

    for (int linha = 0; linha < metadeDeN; linha++)
        for (int coluna = 0; coluna < n; coluna++) {
            if (coluna < nColsLeft || coluna >= n - nColsRight
                    || (coluna == nColsLeft && linha == nColsLeft)) {

                if (coluna == 0 && linha == nColsLeft)
                    continue;

                int tmp = quadradoMagico[linha][coluna];
                quadradoMagico[linha][coluna] = quadradoMagico[linha + metadeDeN][coluna];
                quadradoMagico[linha + metadeDeN][coluna] = tmp;
            }
        }
    desalocarQuadrado(subGrid, metadeDeN);
    return quadradoMagico;
}

int main(){

    for (int n = 3; n <= 6; n++){
        if(n % 2 == 1){
            int **quadradoMagico = tamanhoImpar(n);
            printQuadradoMagico(quadradoMagico, n);
            desalocarQuadrado(quadradoMagico, n);

        } else if (n == 4){
            int **quadradoMagico = tamanhoQuatro(n);
            printQuadradoMagico(quadradoMagico, n);
            desalocarQuadrado(quadradoMagico, n);
        } else if (n == 6){
            int **quadradoMagico = tamanhoSeis(n);
            printQuadradoMagico(quadradoMagico, n);
            desalocarQuadrado(quadradoMagico, n);
        }

    }

    return 0;
}