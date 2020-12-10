#include "tad.h"
#include<stdio.h>
#include <stdlib.h>

struct MATRIZES{
    int linhas;
    int colunas;
    double *dados;
};

int destroiMatriz(MATRIZES *pMatriz){
     if(pMatriz==NULL || pMatriz->dados==NULL){
        return -1;                  
     }
     else{
        free(pMatriz->dados);
        free(pMatriz);
        return 0;
    }
}

MATRIZES *criaMatriz(int linhas, int colunas){
    MATRIZES * pMatriz = (MATRIZES*)malloc(1*sizeof(MATRIZES));
    if(pMatriz == NULL){
        return NULL;
    }
    pMatriz->linhas=linhas;
    pMatriz->colunas=colunas;
    pMatriz->dados=(double*)malloc(linhas*colunas*sizeof(double));
    if(pMatriz->dados == NULL){
        free(pMatriz);
        return NULL;
    }
   return pMatriz;
}

int escreveElemento(MATRIZES *pMATRIZ, int linhas, int colunas, double valor){
    if(pMATRIZ == NULL || linhas >= pMATRIZ->linhas || colunas >=pMATRIZ->colunas){
        return -1;
    }
    else{
        pMATRIZ->dados[colunas*(pMATRIZ->linhas)+linhas]=valor;
        return 0;
    }
}

int acessaElemento(MATRIZES *pMATRIZ, int linhas, int colunas, double *valor){
    if(pMATRIZ == NULL || linhas >= pMATRIZ->linhas || colunas >=pMATRIZ->colunas){
        return -1;
    }
    else{
        *valor=pMATRIZ->dados[colunas*(pMATRIZ->linhas)+linhas];
        return 0;
    }
}

int preencheMatriz(MATRIZES *pMATRIZ){
    if(pMATRIZ == NULL){
        return -1;
    }
    else{
        for(int i=0; i<pMATRIZ->linhas; i++){
             for(int j=0; j<pMATRIZ->colunas; j++){
                 pMATRIZ->dados[(j*(pMATRIZ->linhas))+i] = (double) rand();
             }
        }
        return 0;
    }

}
void printaMatriz(MATRIZES *pMATRIZ){
    for(int i=0; i<pMATRIZ->linhas; i++){
             for(int j=0; j<pMATRIZ->colunas; j++){
                printf("%.0lf ", pMATRIZ->dados[(j*(pMATRIZ->linhas))+i]);
             }
             printf("\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
        }
    return;
}

int somaMatriz(MATRIZES *pMATRIZone, MATRIZES *pMATRIZtwo, MATRIZES *pMATRIZsoma){
   if(pMATRIZone->linhas != pMATRIZtwo->linhas || pMATRIZone->colunas != pMATRIZtwo->colunas || pMATRIZone==NULL || pMATRIZtwo==NULL || pMATRIZsoma==NULL){
       return -1;
   }

   else{
        for(int i=0; i<pMATRIZone->linhas; i++){
             for(int j=0; j<pMATRIZone->colunas; j++){
                 pMATRIZsoma->dados[(j*(pMATRIZone->linhas))+i] = (pMATRIZone->dados[(j*pMATRIZone->linhas)+i] + pMATRIZtwo->dados[(j*pMATRIZone->linhas)+i]);
             }
        }
        return 0;        
   }
}

MATRIZES* multMatriz(MATRIZES *pMATRIZ, MATRIZES *pMATRIZ2){
    if(pMATRIZ->colunas != pMATRIZ2->linhas ||  pMATRIZ==NULL || pMATRIZ2==NULL){
        return NULL;
    }
    else{
        double aux=0.0;
        MATRIZES *pMATRIZmult;
        pMATRIZmult=calloc(1, sizeof(MATRIZES));
        pMATRIZmult->linhas=pMATRIZ->linhas;
        pMATRIZmult->colunas=pMATRIZ2->colunas;
        pMATRIZmult->dados=(double*)calloc(pMATRIZ->linhas, pMATRIZ2->colunas * sizeof(double));
        
        for(int k=0;k<pMATRIZ->linhas; k++){
                aux=0.0;
                for(int i=0; i<pMATRIZ2->colunas; i++){
                        aux=0.0;
                        for(int j=0; j<pMATRIZ->colunas; j++){
                            aux+=pMATRIZ->dados[(j*(pMATRIZ->linhas)+k)]*pMATRIZ2->dados[(i*(pMATRIZ2->linhas)+j)]; 
                        }  
                        pMATRIZmult->dados[i*(pMATRIZmult->linhas)+k]=aux;       
                }
        }
        return pMATRIZmult;        
    }
}


double tracoMATRIZ(MATRIZES *pmat){
    double aux=0.0;
    for(int i=0; i<pmat->linhas; i++){
        for(int j=0; j<pmat->colunas; j++){
            if(i==j){
                aux+=pmat->dados[j*((pmat->linhas))+i];
            }
        }
    }
    return aux;
}

int multPorEscalar(MATRIZES *pmat, int escalar){
    if(pmat==NULL){
        return -1;
    }
    else{
        for(int i=0; i<pmat->linhas; i++){
             for(int j=0; j<pmat->colunas; j++){
                 pmat->dados[(j*(pmat->linhas))+i]*=escalar;
             }
        }
        return 0;
    }
}

double* somaLinhas(MATRIZES *pmat,int *resultado){
    double *somalinhas;
    if(pmat==NULL){
        return NULL;
    }
    else{ 
          *resultado=pmat->linhas;
          somalinhas=(double*)calloc((pmat->linhas), sizeof(double));
          for(int i=0; i<pmat->linhas; i++){
             for(int j=0; j<pmat->colunas; j++){
                somalinhas[i] += pmat->dados[(j*(pmat->linhas))+i];
             }
         }
    }
    return somalinhas;
}

double* somaColunas(MATRIZES *pmat,int *resultado){
    double *somacolunas;
    if(pmat==NULL){
        return NULL;
    }
    else{ 
          *resultado=pmat->colunas;
          somacolunas=(double*)calloc((pmat->colunas), sizeof(double));  
          for(int j=0; j<pmat->colunas; j++){
                 for(int i=0; i<pmat->linhas; i++){
                     somacolunas[j] += pmat->dados[(j*(pmat->linhas))+i];        
                 }
              
          }
    }
    return somacolunas;
}










