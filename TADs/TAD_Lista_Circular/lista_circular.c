#include<stdio.h>
#include<stdlib.h>
#include"lista_circular.h"

typedef struct circnode CircNode;

/*
*********************************************
*Exercício1
*********************************************
*/
struct circlist{
    CircNode *end;
    int size;
    int n_times_shown;//armazena o índidice do último elemento mostrado da lista 
};

struct circnode{
    struct aluno data;
    CircNode *next;
};

Circlist *create_circular_list(){
    Circlist *li;
    li = malloc (1 * sizeof(Circlist));
    if(li == NULL){
        return NULL;
    }
    li->end = NULL;
    li->size = 0;
    li->n_times_shown = 0;
    return li;
}

int free_circular_list(Circlist *li){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    CircNode *aux;
    aux = li->end->next;
    for(int i = 1; i <= li->size; i++){
        free(aux);
        aux = aux->next;
    }
    free(li);
    return SUCCESS;
}
 
int push_front(Circlist *li, struct aluno al){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    CircNode *node = malloc(sizeof(CircNode));
    if(node == NULL){
        return OUT_OF_MEMORY;
    }
    node->data = al;
    if(li->size == 0){//lista vazia
        li->end = node;
        li->end->next = node;
    }
    else{
        node->next = li->end->next;
        li->end->next = node;
    }
    li->size ++;
    return SUCCESS;
}

int push_back(Circlist *li, struct aluno al){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    CircNode *node = malloc(1*sizeof(CircNode));
    if(node == NULL){
        return OUT_OF_MEMORY;
    }
    node->data = al;
    if(li->size == 0){//lista vazia
        li->end = node;
        li->end->next = node;
    }
    else{
        node->next = li->end->next;
        li->end->next = node;
        li->end = node;
    }
    li->size ++;
    return SUCCESS;
}

int pop_front(Circlist *li){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    if(li->size == 0){
        return OUT_OF_MEMORY;
    }
    CircNode *aux = li->end->next;
    li->end->next = aux->next;
    free(aux);
    li->size --; 
    return SUCCESS;
}

int pop_back(Circlist *li){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    if(li->size == 0){
        return OUT_OF_MEMORY;
    }
    CircNode *aux = li->end->next;
    CircNode *aux2 = NULL;
    for(int i = 1; i < li->size; i++){
        aux = aux->next;
    }
    aux->next = li->end->next;
    aux2 = li->end;
    free(aux2);
    li->end = aux;
    li->size --;
    return SUCCESS;
}

int pop_mat(Circlist *li, int mat){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    if(li->size == 0){
        return OUT_OF_MEMORY;
    }
    CircNode *aux = li->end->next;
    CircNode *aux2 = NULL;
    int i = 1;
    while (i <= li->size && aux->data.matricula != mat){  
        aux2 = aux; 
        aux = aux->next;
        i++;
    }
    if( i > li->size) return ELEM_NOT_FOUND;
    if(i == 1) return pop_front(li);
    else if(i == li->size) return pop_back(li);
    else aux2->next = aux->next;
    free(aux);
    return SUCCESS;
}
 
int imprime(Circlist *li){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    CircNode *aux;
    aux = li->end->next;
    for(int i = 1; i <= li->size; i++){
        printf("________________________________________________________\n");
        printf("nome: %s\n", aux->data.nome);
        printf("matricula: %d\n", aux->data.matricula);
        printf("Notas: %f, %f, %f\n", aux->data.n1, aux->data.n2, aux->data.n3);
        printf("\n");
        aux = aux->next;
    }
    return SUCCESS;
}

int size_circular_list(Circlist *li){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    return li->size;
}

/*
*******************************
*  Exercício2
*******************************
*/

int show_element(Circlist *li){
    if(li == NULL){
        return INVALID_NULL_POINTER;
    }
    if(li->size == 0){
        return OUT_OF_MEMORY;
    }
    if(li->n_times_shown == li->size){
        li->n_times_shown = 0;
    }
    CircNode *node = li->end->next;
    for(int i = 0; i < li->n_times_shown; i++){
        node = node->next;
    }
    printf("________________________________________________________\n");
    printf("\nnome: %s\n", node->data.nome);
    printf("matricula: %d\n", node->data.matricula);
    printf("Notas: %f, %f, %f\n", node->data.n1, node->data.n2, node->data.n3);
    printf("\n");
    li->n_times_shown ++;
    return SUCCESS;
}
