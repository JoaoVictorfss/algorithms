#include"tad.h"
#include<stdio.h>
#include<stdlib.h>

int main(){
    int resultado;
    MATRIZES *pmat;
    MATRIZES *pmat2;
    MATRIZES *paux;
    MATRIZES *pmult;
    double *somalinhas;
    double *somacolunas;
    int escalar=2;
   
    pmat=criaMatriz(5,5);
    if(pmat==NULL){
        printf("Erro");
        exit(1);
    }
    pmat2=criaMatriz(5,5);
    if(pmat2==NULL){
        printf("Erro");
        exit(1);
    }
    paux=criaMatriz(5,5);
    if(paux==NULL){
        printf("Erro");
        exit(1);
    }
    resultado=escreveElemento(pmat, 0, 0, 1);
    if(resultado==-1){
        printf("Erro");
        exit(1);
    }
    /*escreveElemento(pmat, 0, 1, 2);
    escreveElemento(pmat, 1, 0, 3);
    escreveElemento(pmat, 1, 1, 4);
    resultado=escreveElemento(pmat2, 0, 0, 5);
    if(resultado==-1){
        printf("Erro");
        exit(1);
    }
    escreveElemento(pmat2, 0, 1, 6);
    escreveElemento(pmat2, 1, 0, 7);
    escreveElemento(pmat2, 1, 1, 8);*/
    preencheMatriz(pmat);
    preencheMatriz(pmat2);
    preencheMatriz(paux);
    printf("\nprimeira matriz: \n");
    printaMatriz(pmat);
    printf("\nsegunda matriz: \n");
    printaMatriz(pmat2);

    resultado=somaMatriz(pmat, pmat2, paux);
    if(resultado==-1){
        printf("Erro");
        exit(1);
    }
    printf("\nsoma das matrizes 1 e 2: \n");
    printaMatriz(paux);
    printf("\nmatriz aux: \n");
    printaMatriz(paux);
    printf("\ntraço da matriz aux: %0.0lf \n", tracoMATRIZ(paux));
    
    resultado=multPorEscalar(paux, escalar);
    if(resultado==-1){
       printf("Erro");
       exit(1);
    }
    printf("\nmatriz aux multiplicada por %d: \n", escalar);
    printaMatriz(paux);
   
    printf("\nSoma de linhas da primeira matriz: \n");
    somalinhas=somaLinhas(pmat, &resultado);
    if(somaLinhas==NULL){
       printf("Erro");
       exit(1);
    }
    for( int i=0; i<resultado; i++){
        printf("A soma da linha %d da primeira matriz é: %.0lf\n", i+1, somalinhas[i]);
    }

    printf("\nSoma de colunas da primeira matriz: \n");
    somacolunas=somaColunas(pmat, &resultado);
    if(somacolunas==NULL){
       printf("Erro");
       exit(1);
    }
    for( int i=0; i<resultado; i++){
        printf("A soma da coluna %d da primeira matriz é: %.0lf\n", i+1, somacolunas[i]);
    }

    pmult=multMatriz(pmat, pmat2);
    if(pmult==NULL){
       printf("Erro");
       exit(1);
    }
    printf("Matriz 1 multiplicada pela matriz 2: \n");
    printaMatriz(pmult);
  
    free(somacolunas);
    free(somalinhas);
    resultado=destroiMatriz(pmult);
    resultado=destroiMatriz(pmat2);
    resultado=destroiMatriz(pmat);
    destroiMatriz(paux);  
}

