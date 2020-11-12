
#include"image.h"
#include"pilha.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Image{
    int linhas;
    int colunas;
    unsigned char *dados;
};

/*
*Apaga a matriz
*/
int freeImage(Image *pIMAGE){
     if(pIMAGE == NULL || pIMAGE->dados == NULL){
        return INVALID_NULL_POINTER;                  
     }
     else{
        free(pIMAGE->dados);
        free(pIMAGE);
        return 0;
    }
}

/*
*Cria uma matriz para a imagem
*/
Image *imageCreate(int linhas, int colunas){
    Image * pIMAGE = (Image*)malloc(1*sizeof(Image));
    if(pIMAGE == NULL){
        return NULL;
    }
    pIMAGE->linhas = linhas;
    pIMAGE->colunas = colunas;
    pIMAGE->dados = calloc(linhas*colunas, sizeof(unsigned char));
    if(pIMAGE->dados == NULL){
        free(pIMAGE);
        return NULL;
    }
   return pIMAGE;
}

/*
* Mostra a imagem na tela 
*/
void showPicture(Image *pImage){
    int colunas = 0;
    for(int i=0; i<(pImage->linhas * pImage->colunas); i++){
           colunas ++;
           if((int)pImage->dados[i]/10 < 1){
               printf("%hhu   ", pImage->dados[i]);
           }
           else if((int)pImage->dados[i]/100 < 1){
               printf("%hhu  ", pImage->dados[i]);
           }
           else{
               printf("%hhu ", pImage->dados[i]);  
           }   
           if(colunas == pImage->colunas){
               printf("\n");
               colunas = 0;
           }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    }
    return;
}

Image *openFileTxt(char *nomeArq){
    FILE *fp = NULL;
    fp = fopen(nomeArq, "r");
    if(fp == NULL){
         return NULL;
    }
    int nrows, ncols;
    char formato[3];
    unsigned char aux;
    fscanf(fp, "%s\n", formato);
    fscanf(fp, "%d %d\n", &ncols, &nrows);
    fscanf(fp, "%hhu\n", &aux);
    Image *image = imageCreate(nrows, ncols); 
    for(int i = 0; i < (ncols * nrows); i++){
         fscanf(fp, "%hhu", &image->dados[i]);
    }
    fclose(fp);
    return image;
}

/*
*Abre uma image do formato de texto
*/
int openTxt(char *nomeArq){
    Image *image = openFileTxt(nomeArq);
    if(image == NULL) return ERROR_OPENING_FILE;;
    showPicture(image);
    freeImage(image);
    return SUCCESS;
}

Image *openFileIMM(char *nomeArq){
    FILE *fp = fopen(nomeArq, "rb");
    if(fp == NULL) return NULL;
    int nrows, ncols;
    fread(&ncols, sizeof(int), 1, fp);
    fread(&nrows, sizeof(int), 1, fp);
    Image *image = imageCreate(nrows, ncols);
    for(int i = 0; i < (ncols * nrows); i++){
         fread( &image->dados[i], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    return image;
}

/*
*Abre uma imagem em binário
*/
int openIMM(char *nomeArq){
    Image *image = openFileIMM(nomeArq);
    if(image == NULL) return ERROR_OPENING_FILE;
    showPicture(image);
    freeImage(image);
    return SUCCESS;
}

/*
*Converte uma imagem do formato de texto para o formato binário
*/ 
int convertTxtToImm(char *nomeArq, char *nomeArq2){
    Image *image = openFileTxt(nomeArq);
    if(image == NULL) return ERROR_OPENING_FILE;
    FILE *fp = fopen(nomeArq2, "wb");
    if(fp == NULL){
        return INVALID_FILE;
    }
    fwrite(&image->colunas, sizeof(int), 1, fp);
    fwrite(&image->linhas, sizeof(int), 1, fp);
    fwrite(image->dados, sizeof(unsigned char), (image->colunas * image->linhas), fp);
    freeImage(image);
    fclose(fp);
    return SUCCESS;
}

/*
*Verifica a extensão dos arquivos 
*/
int extension(char *str){
    if(strlen(str) > 4){
        int i = strlen(str) - 4;
        if(str[i+1] == 't' && str[i+2] == 'x' && str[i+3] == 't') return TXT;
        else if(str[i+1] == 'p' && str[i+2] == 'g' && str[i+3] == 'm') return TXT;
        else if(str[i+1] == 'i' && str[i+2] == 'm' && str[i+3] == 'm') return IMM;
        else return DIFFERENT_FORMAT;         
    }
}

/*
*A função threshold faz a limiarização de uma imagem
*/
int threshold(int thr, char *nomeArq, char *nomeArq2){
    Image *image = openFileIMM(nomeArq);
    if(image == NULL) return ERROR_OPENING_FILE;
    FILE *fp = fopen(nomeArq2, "wb");
    for(int i = 0; i < (image->colunas * image->linhas); i++){
        if(image->dados[i] <= thr){
            image->dados[i] = 0;        
        }
        else{
            image->dados[i] = 1;
        }
    }
    fwrite(&image->colunas, sizeof(int), 1, fp);
    fwrite(&image->linhas, sizeof(int), 1, fp);
    fwrite(image->dados, sizeof(unsigned char), (image->colunas * image->linhas), fp);
    fclose(fp);
    freeImage(image);
    return SUCCESS;
}

/*
*A Função relatedPoints pega todos os pontos conexos de uma imagem e organiza todos 
*com valores crescentes pra cada ponto conectado
*/
int relatedPoints(Image* image){
    Pilha* stack = stack_create(image->linhas * image->colunas);
    if(stack == NULL)return INVALID_NULL_POINTER;
    Image* imageSaida = imageCreate(image->linhas, image->colunas);
    if(imageSaida == NULL) return INVALID_NULL_POINTER;
    if(image == NULL) return ERROR_OPENING_FILE;
    int index = 1, p, pAtual[4];
    for(int i = 0; i < (image->linhas * image->colunas); i++){
        p = i;
        if(image->dados[p] == 1 && imageSaida->dados[p] == 0){
            imageSaida->dados[p] = index;
            push(stack, p);
            while((stack_size(stack))!=0){
                get_element(stack, &p);
                pop(stack);
                pAtual[0] = p - image->colunas;
                pAtual[1] = p + image->colunas;
                pAtual[2] = p - 1;
                pAtual[3] = p + 1;
                for(int j = 0; j < 4; j++){
                    if(image->dados[pAtual[j]] == 1 && imageSaida->dados[pAtual[j]] == 0){
                        imageSaida->dados[pAtual[j]] = index;
                        push(stack, pAtual[j]);
                    }
                }
            }
            index++;
        } 
    }
    showPicture(imageSaida);
    freeImage(imageSaida);
    freeImage(image);
    stack_free(stack);
    return SUCCESS;
}

int search_begin(Image *image){//procura o elemento na primeira coluna da matriz 
    if(image == NULL) return INVALID_NULL_POINTER;
    int ponto = 0;
    for(int i = 0; i < image->linhas; i++){
        ponto = i*(image->colunas);
        if (image->dados[ponto] == 1){
            return ponto;
        }
    }
    return ELEM_NOT_FOUND;
}


/*
*Função maze trabalha com uma imagem de um labirinto, em que o objetivo é mostrar o caminho que
*contém a saída do mesmo, usando a pilha e valor 2 para mapear os caminhos corretos.
*Para trabalhar com esse labirinto a image deve ser limirializada. Dessa forma, primeiramente o usuário 
*tem que fazer a limiarização da imagem através da função threshold pelo comando "segment". 
*
*/

int maze(Image *image){
    Pilha *stack = stack_create(image->linhas * image->colunas);
    if(stack == NULL)return INVALID_NULL_POINTER;
    Image *imageSaida = imageCreate(image->linhas, image->colunas);
    if(imageSaida == NULL) return INVALID_NULL_POINTER;
    int pontoAtual = 0;
    int verifica;
    int ponto_direita, ponto_esquerda, ponto_cima, ponto_baixo;
    pontoAtual = search_begin(image);
    push(stack, pontoAtual);
    while((pontoAtual + 1) % (image->colunas) != 0){//enquanto a posição atual for diferente da última coluna
        image->dados[pontoAtual] = 3; 
        if(stack_size(stack) == 0){//pilha vazia significa que não encontrei o 1 e desempilhei tudo, logo, tenho que pegar o proximo valor do inicio do labirinto
            pontoAtual = search_begin(image);
            if(pontoAtual != ELEM_NOT_FOUND){
                push(stack, pontoAtual);
                image->dados[pontoAtual] = 3;
            }
            else{
                printf("Labirinto sem saída\n");
                stack_free(stack);
                freeImage(imageSaida);
                freeImage(image);
                return SUCCESS;
            }
        }
        ponto_direita = pontoAtual + 1;
        ponto_esquerda = pontoAtual - 1;
        ponto_cima = pontoAtual - image->colunas;
        ponto_baixo = pontoAtual + image->colunas;
        if (image->dados[ponto_direita] == 1){
            pontoAtual = ponto_direita;
            push(stack, pontoAtual);
        }
        else{
            if (image->dados[ponto_esquerda] == 1){
                pontoAtual = ponto_esquerda;
                push(stack, pontoAtual);
            } 
            else if (image->dados[ponto_cima] == 1){
                pontoAtual = ponto_cima;
                push(stack, pontoAtual);
           }
           else if (image->dados[ponto_baixo] == 1){
                pontoAtual = ponto_baixo;
                push(stack, pontoAtual);
           }
           else{
                pop(stack);//desempilha se não tiver vizinhos
           }
        }
    }
    for(int i = 0; i < (image->linhas * image->colunas); i++){
        if(image->dados[i] == 3){
            imageSaida->dados[i] = 1;
        }
        else{
            imageSaida->dados[i] = image->dados[i];
        }
    }
    int size = stack_size(stack);
    int pontoColuna[size];
    int pontoLinha[size];
    int j = size-1;
    int pos = 0;
    for(int i = 0; i < size; i++){
        get_element(stack, &pos);
        pontoColuna[j] = (pos%image->colunas) + 1;//pega a coluna;
        pontoLinha[j] = (pos/image->linhas) + 1;//pega a linha;
        pop(stack);
        imageSaida->dados[pos] = 2;
        j--;
    }
    printf("\n----Resposta do labirinto----\n\n");
    showPicture(imageSaida);
    printf("\ncoordenadas de saída:\n\n");
    for(int i = 0; i<size; i++){
        printf("coluna: %d, linha: %d\n", pontoColuna[i], pontoLinha[i]);
    }
    stack_free(stack);
    freeImage(imageSaida);
    freeImage(image);
    return SUCCESS;       
}

 
