
#include <math.h>
#include <stdio.h>
#include "tad_lista.h"
#include <stdlib.h>

struct lista{
    int qtd;//quem diferencia a lista de um vetor. Com  ela 
    //controlamos em tempo de execução quantos elementos nossa lista possui 
    int tam_inicial;//vai guardar o tamanho inicial 
    int aux;//vai guardar a atualização do tamanho inicial
    struct aluno *dados;
};

Lista* cria_lista(int qtd_inicial){
    Lista *li=calloc(1, sizeof(Lista));//caso dê falha, retorna NULL;
    if(li!=NULL) 
       li->qtd=0;//iniciando o TAD com a lista com 0 elementos
    li->tam_inicial=qtd_inicial;
    li->aux=li->tam_inicial;
    li->dados=calloc(qtd_inicial,sizeof(struct aluno));
    return li;
}

void libera_lista(Lista*li){
    free(li->dados);
    free(li);
}

int consulta_lista_pos(Lista*li, int pos, struct aluno *al){
    //retorna um inteiro para verificação, e passa os dados do aluno para um ponteiro do tipo aluno;
    if(li==NULL || pos <= 0 || pos>li->qtd)
         return -1;
    *al=li->dados[pos-1]; //copiando para *al o conteúdo daquela posição passada
     return 0;
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){//consulta os dados da lista pela matricula passada e copia para struct aluno os dados da matricula consultada
    if(li==NULL)
        return -1;
    int i = 0;
    while(i<li->qtd && li->dados[i].matricula != mat)
         i++;
    if( i == li->qtd)//elemento não encontrado
      return -1;

    *al=li->dados[i];
    return 0;
}

int insere_lista_final(Lista* li, struct aluno al){
    int aux=li->tam_inicial;
    if(li==NULL) 
          return -1;
    if(li->qtd==li->aux){
          li->aux+=aux;
          li->dados=realloc(li->dados, li->aux * sizeof(struct aluno));
          if(li->dados==NULL) return -1;
    }
    
    li->dados[li->qtd]=al;
    li->qtd++; 
    return 0;
}

int insere_lista_inicio(Lista*li, struct aluno al){
    int aux=li->tam_inicial;
    if(li==NULL) 
          return -1;
    if(li->qtd==li->aux){
          li->aux+=aux;
          li->dados=realloc(li->dados, li->aux * sizeof(struct aluno));
          if(li->dados==NULL) return -1;
    } 
    int i;
    for(i=li->qtd; i>=0; i--)
          li->dados[i+1]=li->dados[i];
    li->dados[0]=al;
    li->qtd++;
    return 0;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    int aux=li->tam_inicial;
    if(li==NULL) 
          return -1;
    if(li->qtd==li->aux){
          li->aux+=aux;
          li->dados=realloc(li->dados, li->aux * sizeof(struct aluno));
          if(li->dados==NULL) return -1;
    }

    int k, i =0;
    while(i<li->qtd && li->dados[i].matricula<al.matricula)
       i++;
    for(k=li->qtd-1; k>=i; k--)
       li->dados[k+1] = li->dados[k];

    li->dados[i]=al;
    li->qtd++;
    return 0;
}

int compactar_lista(Lista* li){
    if(li==NULL) 
        return -1;
    int num = ceil(li->qtd/ li->tam_inicial) * li->tam_inicial;
    if (li->qtd > num)
        li->dados = realloc(li->dados, num * sizeof(struct aluno));
    return 0;
    li->aux=num;
}

int remove_lista(Lista *li, int mat){
    if(li==NULL) return -1;
    if(li->qtd == 0) return -1;
    int k, i=0;

    while(i<li->qtd && li->dados[i].matricula !=mat)
        i++;
    if(i==li->qtd)//elemento não encontrado
        return 0;
    
    for(k=i; k<li->qtd-1; k++)
       li->dados[k]=li->dados[k+1];
    li->qtd--;
    return 0;
}

int remove_lista_otimizado(Lista *li, int mat){
    if(li==NULL) return -1;
    if(li->qtd == 0) return -1;
    int i=0;

    while(i<li->qtd && li->dados[i].matricula !=mat)
        i++;
    if(i==li->qtd)//elemento não encontrado
        return 0;

    li->qtd--;
    li->dados[i] = li->dados[li->qtd];
    return 0;
}

int remove_lista_inicio(Lista *li){
    if(li==NULL) return -1;
    if(li->qtd==0) return -1;
    int k = 0;
    for(k=0; k<li->qtd-1; k++)
      li->dados[k]=li->dados[k+1];
    li->qtd --;
    return 0;
}

int remove_lista_final(Lista*li){
    if(li==NULL) return -1;
    if(li->qtd==0) return -1;
    li->qtd--;
    return 0;
}

int tamanho_lista(Lista*li){
    if(li==NULL) return -1;
    else 
    return li->qtd;
}

int lista_cheia(Lista*li){
    if(li==NULL)
       return -1;
    return (li->qtd==li->tam_inicial);
}

int lista_vazia(Lista *li){
    if(li==NULL) return -1;
    return (li->qtd == 0);
}

int imprime_lista(Lista* li){
    if(li==NULL) return -1;

    int i;
    for(i=0;i<li->qtd; i++){
        printf("Matricula: %d\n",li->dados[i].matricula);
        printf("Nome: %s\n",li->dados[i].nome);
        printf("Notas: %f %f %f\n", li->dados[i].n1, li->dados[i].n2,li->dados[i].n3);
        printf("----------------------------------\n");
    }
    return 0;
}














    