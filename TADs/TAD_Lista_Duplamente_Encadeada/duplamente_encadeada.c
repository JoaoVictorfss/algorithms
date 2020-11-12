#include "duplamente_encadeada.h"
#include <stdio.h>
#include <stdlib.h>

struct DlinkedList {
  dlnode *begin;
  dlnode *end;
  int size;
};

struct dlnode{
    struct aluno data;
    dlnode *next;
    dlnode *prev;
};

List *list_create(){
    List *li = malloc(sizeof(List));
    if(li != NULL){
        li->size = 0;
        li->begin = NULL;
        li->end = NULL;    
    }
    return li;
}

int list_free(List *li){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    dlnode *aux = li->begin;

    while(aux != NULL){
        li->begin = aux->next;
        free(aux); 
        aux = li->begin;
    }
    free(li);
    return SUCCESS;
}


int list_push_front(List *li, struct aluno al){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    dlnode *node = malloc(sizeof(dlnode));
    if(node == NULL)
        return OUT_OF_MEMORY;
    node->data = al;
    node->prev = NULL;
    if(li->begin == NULL){ //caso a lista esteja vazia
        node->next = NULL;
        li->begin = node;
        li->end = node;
    }
    else{
        node->next = li->begin;
        li->begin->prev = node;
        li->begin = node;
    }
    li->size ++;
    return SUCCESS;
}

int list_push_back(List *li, struct aluno al){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    dlnode *node = malloc(sizeof(dlnode));
    if(node == NULL)
        return OUT_OF_MEMORY;
    node->data = al;
    node->next = NULL;
    if(li->begin == NULL){ //caso a lista esteja vazia
        li->begin = node;
        li->end = node;
        li->begin->prev = NULL;
    }
    else{
        li->end->next = node;
        node->prev = li->end;
        li->end = node; 
    }
    li->size ++;
    return SUCCESS;
}

int list_insert(List *li, int pos, struct aluno al){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    if(pos > li->size + 1 || pos <= 0)
        return INVALID_POSITION;
    if(pos == 1)//inserir na primeira posição
        return list_push_front(li, al);
    if(pos == li->size + 1)
        return list_push_back(li, al);

    dlnode *node = malloc(sizeof(dlnode));
    if(node == NULL)
        return OUT_OF_MEMORY;
    node->data = al;
    dlnode *prev = NULL;
    dlnode *current=li->begin;
    int i = 1;
    while(current->next != NULL && i < pos){
        prev = current;
        current = current->next;
        i++;      
    }
    prev->next = node;
    node->prev = prev;
    current->prev = node;
    node->next = current;

    li->size ++;
    return SUCCESS;
}

int list_size(List *li){
    if(li == NULL)
         return INVALID_NULL_POINTER;

    return li->size;
}

int list_find_pos(List *li, int pos, struct aluno *al){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    if(li->size == 0)
         return OUT_OF_RANGE;
    if(pos > li->size || pos < 0)
        return INVALID_POSITION;

    dlnode *aux = li->begin;
    int i = 1;
    while(aux->next != NULL && i < pos){
        aux = aux->next;
        i++; 
    }

    *al = aux->data;
     return SUCCESS;       
}

int list_find_mat(List *li, int nmat, struct aluno *al){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    if(li->size == 0)
         return OUT_OF_RANGE;

    dlnode *aux = li->begin;
    int i = 1;
    while(aux->next != NULL && aux->data.matricula != nmat){
        aux = aux->next;
        i++; 
    }
    if(i == li->size)
        return ELEM_NOT_FOUND;

    *al = aux->data;
     return SUCCESS;       
} 

int list_front(List *li, struct aluno *al){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->size == 0)
        return OUT_OF_RANGE;
    *al = li->begin->data;

    return SUCCESS;
}

int list_back(List *li, struct aluno *al){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->size == 0)
        return OUT_OF_RANGE;
    *al = li->end->data;

     return SUCCESS;
}

int list_get_pos(List *li, int nmat, int *pos){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->size == 0)
        return OUT_OF_RANGE;
    dlnode *aux = li->begin;
    int i =1;
    while(aux->next != NULL && aux->data.matricula != nmat){
        aux = aux->next;
        i++;
    }
    if(i > li->size)
        return OUT_OF_RANGE;
    *pos = i;
    return SUCCESS;   
}

int list_pop_front(List *li){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->size == 0)
        return OUT_OF_RANGE;
    
    if(li->size == 1){
        dlnode *aux = li->begin;
        li->begin = NULL;
        free(aux); 
        li->end = NULL;
    }
    else{
        dlnode *aux = li->begin;
        li->begin = li->begin->next;
        li->begin->prev = NULL;   
        free(aux);
    }

    li->size--;
    return SUCCESS;
}

int list_pop_back(List *li){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->size == 0)
        return OUT_OF_RANGE;
    if(li->size == 1)
       return list_pop_front(li);

    dlnode *aux = li->end;
    li->end = li->end->prev;
    li->end->next = NULL;
    free(aux);

    li->size --;
    return SUCCESS;  
} 

int list_erase(List *li, int pos){

    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->size == 0)
        return OUT_OF_RANGE;
    if(pos < 0 || pos > li->size)
        return INVALID_POSITION;
    if(pos == 1)
        return list_pop_front(li);
    if(pos == li->size)
        return list_pop_back(li);

    dlnode *current = li->begin;
    dlnode *prev = NULL;
    dlnode *next = current->next;
    
    int i = 1;
    while(next->next != NULL && i < pos){
        prev = current;
        current = current->next;
        next = current->next;
        i++;
    }
    prev->next = next;
    next->prev = prev;
    free(current);
    
    li->size --;
    return SUCCESS; 
}
        

int list_print_forward(List *li){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->size == 0)
        return OUT_OF_RANGE ;
    dlnode *aux = li->begin;
    while(aux != NULL){
        printf("\n--------------------------------------------------------------------------");
        printf("\nNome: %s\nMatrícula: %d\nNotas: %.2lf, %.2lf, %.2lf.\n", aux->data.nome, aux->data.matricula, aux->data.n1, aux->data.n2, aux->data.n3);
        printf("---------------------------------------------------------------------------\n");
        aux = aux->next;
    }
    return SUCCESS;
}
int list_print_reverse(List *li){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->size == 0)
        return OUT_OF_RANGE;
    dlnode *aux = li->end;
    while(aux != NULL){
        printf("\n--------------------------------------------------------------------------");
        printf("\nNome: %s\nMatrícula: %d\nNotas: %.2lf, %.2lf, %.2lf.\n", aux->data.nome, aux->data.matricula, aux->data.n1, aux->data.n2, aux->data.n3);
        printf("---------------------------------------------------------------------------\n");
        aux = aux->prev;
    }
    return SUCCESS;
}