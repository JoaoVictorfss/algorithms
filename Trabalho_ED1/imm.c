#include "image.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
int verifica;
    if(strcmp(argv[1], "-open") == 0){
      int verifica = extension(argv[2]);
        if(verifica == TXT){
            verifica = openTxt(argv[2]);
            if(verifica == ERROR_OPENING_FILE)printf("Erro ao abrir o aquivo\n");
        }
        else if(verifica == IMM){
           verifica = openIMM( argv[2]);
           if(verifica == ERROR_OPENING_FILE)printf("Erro ao abrir o aquivo\n");
        }
        else{
            printf("Erro, formato diferente. Tente na próxima com arquivos do tipo texto ou binário!\n");
        }
    }
    else if(strcmp(argv[1], "-convert") == 0){
        int verificaTxt = extension(argv[2]);
        int verificaImm = extension(argv[3]);
        if(verificaTxt == TXT && verificaImm == IMM){
           verifica = convertTxtToImm(argv[2], argv[3]);
           if(verifica != SUCCESS) printf("Erro ao converter o arquivo\n");
        }
        else printf("formatos diferentes, tente novamente com arquivos do tipo texto e binário\n");
    }
    else if(strcmp(argv[1], "-segment") == 0){
        if(extension(argv[3]) == IMM && extension(argv[4]) == IMM){
            int thr = atoi(argv[2]);
            verifica = threshold(thr, argv[3], argv[4]);
            if(verifica != SUCCESS) printf("Error ao abrir o arquivo\n");
        }
        else printf("Erro, comando inexistente");
    } 
    else if(strcmp(argv[1], "-cc") == 0){ 
        if(extension(argv[2]) == IMM){ 
            Image *image = openFileIMM(argv[2]);
            if(image == NULL){
                printf("Error ao abrir o arquivo\n");
                exit(1);
            } 
           int verifica;
           verifica = relatedPoints(image);
           if(verifica != SUCCESS) printf("Erro, não foi possível pegar os pontos conexos\n");
        }
        else{
            printf("formato de arquivo insuportado\n");
        }
    } 
    else if(strcmp(argv[1], "-lab") == 0){
        Image *image = openFileIMM(argv[2]);
        printf("\n----Labirinto----\n");
        showPicture(image);
        verifica = maze(image);
        if(verifica != SUCCESS) printf("Erro ao trabalhar com o labirinto\n");
    }  
    else{
        printf("Erro, comando inexistente\n");
    }   return 0;
}