#include "lista_encadeada.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct list_node List_node;

struct list{
     List_node *head;
};

struct list_node{
    struct aluno data;
    List_node *next;
};

List *list_creat(){
    List *li;
    li = malloc(sizeof(List));
    if(li != NULL)
       li->head = NULL;
    return li; 
}

int list_push_front(List *li, struct aluno al){
     if(li == NULL)
         return INVALID_NULL_POINTER;
     List_node *node;
     node = malloc(sizeof(List_node));
     if(node == NULL)
          return OUT_OF_MEMORY;
     node->data = al;
     node->next = li->head;
     li->head = node;

     return SUCCESS;
}

int list_push_back(List *l, struct aluno al){
    if(l == NULL)
        return INVALID_NULL_POINTER;

    List_node *aux = l->head;
    List_node *node;
    node=malloc(sizeof(List_node));
    if(node == NULL)
        return OUT_OF_MEMORY;
    node->data = al;
    if(l->head == NULL){
       node->next=l->head;
       l->head=node;
    }
    else{
       while(aux->next != NULL){
            aux = aux->next;
       }
       aux->next = node;
       node->next = NULL;
    }
    return SUCCESS;
}

int list_insert(List *li, int pos, struct aluno al){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    int size = list_size(li);
    if(pos > size || pos < 0)
        return INVALID_VALOR;
    List_node *node = malloc(sizeof(List_node));
    if(node == NULL)
         return OUT_OF_MEMORY;
    node->data = al;
    List_node *aux1 = li->head, *aux2 = NULL;
    int i = 1;
    if(pos == 1){
        list_push_front(li, al);
    }
    else{
        while(aux1 != NULL && i < pos){
            aux2 = aux1;
            aux1 = aux1->next;
            i++;
        }
        aux2->next = node;
        node->next = aux1;
    }

    return SUCCESS;
}

int list_insert_sorted(List *li, struct aluno al){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    List_node *node = malloc(sizeof(List_node));
    node->data = al;
    if(node == NULL)
         return OUT_OF_MEMORY;
    if(li->head == NULL){
         node->next = li->head;
         li->head = node;
    }
    List_node *anterior = NULL, *atual = li->head;
    while(atual != NULL && al.matricula >= atual->data.matricula){
        anterior = atual;
        atual = atual->next;
    }
    if(atual == li->head){
        node->next = li->head;
        li->head = node;
    }
    else{
        anterior->next = node;
        node->next = atual;
    }
    return SUCCESS;   
}

int list_free(List *li){
    if(li == NULL)
         return INVALID_NULL_POINTER;

    List_node *node=li->head;
    while(node != NULL){
        li->head = node->next;
        free(node);
        node = li->head;    
    }

    free(li);

    return SUCCESS;    
}

int list_pop_front(List *li){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    if(li->head == NULL)
        return ELEM_NOT_FOUND;
    List_node *node;
    node = li->head;
    li->head=li->head->next;
    
    free(node);
    
    return SUCCESS;
}

int list_pop_back(List *li){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    if(li->head == NULL)
         return ELEM_NOT_FOUND;
    else{
         if(li->head->next == NULL){//tem somente um elemento
             free(li->head);
             li->head = NULL;
         }
         else{//lista com mais de um elemento
              List_node *anterior, *atual;
              anterior = li->head;
              atual = anterior->next;
              while(atual->next != NULL){
                  anterior = atual;
                  atual = atual->next;   
              }  
              anterior->next = NULL;
              free(atual);
         }
    } 
    return SUCCESS;
}

int list_erase(List *li, int pos){
    int size = list_size(li);

    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(pos < 0 || pos > size)
        return INVALID_VALOR;
    if(li->head == NULL)
        return ELEM_NOT_FOUND;

    else if(pos == 1){
        return list_pop_front(li);
    }

    List_node *anterior = NULL;
    List_node *atual = li->head;
    List_node *proximo = atual->next;
    int i = 1;
    while(proximo->next != NULL &&  i < pos){
         anterior = atual;
         atual = proximo;
         proximo = proximo->next;
         i++;
    }

    if(i == size){
        return list_pop_back(li);
    } else {
        anterior->next= proximo;
        free(atual);
    }
    
    return SUCCESS;        
}


int list_size(List *li){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    List_node *node = li->head;
    int i = 0;
    while(node != NULL){
        i++;
        node = node->next;   
    }
    return i;
}

int list_find_pos(List *li, int pos, struct aluno *al){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    int i = list_size(li);
    if(pos < 0 || pos > i)
        return INVALID_VALOR;
    if(i == 0)
        return ELEM_NOT_FOUND;
    List_node *node = li->head;
    int j = 1;
    while(node->next != NULL && j < pos){
         node = node->next;
         j++;
    }
    *al = node->data;
    return SUCCESS;
}


int list_find_mat(List *li, int nmat, struct aluno *al){
    if(li == NULL)
        return INVALID_NULL_POINTER;
    if(li->head == NULL)
        return ELEM_NOT_FOUND;
    List_node *node = li->head;
    int size = list_size(li);
    int i = 0;
    while(node != NULL && node->data.matricula != nmat){
         i++;
         node = node->next;
    }
    if(i == size)//matricula não encontrada
         return ELEM_NOT_FOUND;
    *al = node->data;
    return SUCCESS;
}

int list_front(List *li, struct aluno *al){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    if(li->head == NULL)
         return ELEM_NOT_FOUND;
    *al = li->head->data;
    return SUCCESS;
}

int list_back(List *li, struct aluno *al){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    if(li->head == NULL)
         return ELEM_NOT_FOUND;
    List_node *node = li->head;
    while(node->next != NULL)
          node = node->next;

    *al = node->data;
    return SUCCESS; 
}

int list_get_pos(List *li, int nmat, int *pos){
    int size = list_size(li);
    if(li == NULL)
         return INVALID_NULL_POINTER;
    if(li->head == NULL)
         return ELEM_NOT_FOUND;
    List_node *aux = li->head;
    int i = 1;
    while(aux->next != NULL && aux->data.matricula != nmat){
        aux = aux->next;
         i++;
    }
    if(i > size)
        return ELEM_NOT_FOUND;
    *pos = i;
    
    return SUCCESS;
}

int list_print(List *li){
    if(li == NULL)
         return INVALID_NULL_POINTER;
    List_node *node;
    node = li->head;
   
    while(node!=NULL){
         printf("nome: %s\n", node->data.nome);
         printf("matricula: %d\n", node->data.matricula);
         printf("Notas: %f, %f, %f\n", node->data.n1, node->data.n2, node->data.n3);
         printf("\n");
         node=node->next;
    }

    return SUCCESS;
}