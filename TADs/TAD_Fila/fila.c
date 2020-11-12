#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

struct fila {
  queueNode *begin;
  queueNode *end;
  int size;
};

struct queueNode{
    struct aluno data;
    queueNode *next;
    queueNode *prev;
};

Fila *create_queue(){
    Fila *queue = malloc(sizeof(Fila));
    if(queue != NULL){
        queue->size = 0;
        queue->begin = NULL;
        queue->end = NULL;    
    }
    return queue;
}

int free_queue(Fila *queue){
    if(queue == NULL)
        return INVALID_NULL_POINTER;
    queueNode *aux = queue->begin;

    while(aux != NULL){
        queue->begin = aux->next;
        free(aux); 
        aux = queue->begin;
    }
    free(queue);
    return SUCCESS;
}

int get_queue(Fila *queue, struct aluno *al){
    if(queue == NULL)
        return INVALID_NULL_POINTER;
    if(queue->size == 0)
        return OUT_OF_RANGE;
    *al = queue->begin->data;
     return SUCCESS;
}

int push(Fila *queue, struct aluno al){
    if(queue == NULL)
        return INVALID_NULL_POINTER;
    queueNode *node = malloc(sizeof(queueNode));
    if(node == NULL)
        return OUT_OF_MEMORY;
    node->data = al;
    node->next = NULL;
    if(queue->begin == NULL){ //caso a Fila esteja vazia
        queue->begin = node;
        queue->end = node;
        queue->begin->prev = NULL;
    }
    else{
        queue->end->next = node;
        node->prev = queue->end;
        queue->end = node; 
    }
    queue->size ++;
    return SUCCESS;
}

int queue_size(Fila *queue){
    if(queue == NULL)
         return INVALID_NULL_POINTER;

    return queue->size;
}

int pop(Fila *queue){
    if(queue == NULL)
        return  INVALID_NULL_POINTER;
    if(queue->size == 0)
        return OUT_OF_RANGE;
    if(queue->size == 1){
        queueNode *aux = queue->begin;
        queue->begin = NULL;
        free(aux); 
        queue->end = NULL;
    }
    else{
        queueNode *aux = queue->begin;
        queue->begin = queue->begin->next;
        queue->begin->prev = NULL;   
        free(aux);
    }

    queue->size--;
    return SUCCESS;
}

int imprime(Fila *queue){
    if(queue == NULL)
        return INVALID_NULL_POINTER;
    if(queue->size == 0)
        return OUT_OF_RANGE ;
    queueNode *aux = queue->begin;
    while(aux != NULL){
        printf("\n--------------------------------------------------------------------------");
        printf("\nNome: %s\nMatrícula: %d\nNotas: %.2lf, %.2lf, %.2lf.\n", aux->data.nome, aux->data.matricula, aux->data.n1, aux->data.n2, aux->data.n3);
        printf("---------------------------------------------------------------------------\n");
        aux = aux->next;
    }
    return SUCCESS;
}
