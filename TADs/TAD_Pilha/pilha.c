#include "lista_encadeada.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

struct pilha{
    List *li;
};

Pilha *cria_pilha(){
    Pilha *stack = malloc(sizeof(Pilha)); 
    if( stack == NULL)
        return NULL;
    else{
        stack->li = list_creat();
        if(stack->li == NULL){
            free(stack);
            return NULL;
        }
        return stack;
    }
}

void libera(Pilha* stack){
    list_free(stack->li);
    free(stack);
}

int push(Pilha* stack, struct aluno al){
    int i = list_push_front(stack->li, al);
    return i;
}

int pop (Pilha* stack){
    int i = list_pop_front(stack->li);
    return i;
}

int imprime(Pilha* stack){
    int i = list_print(stack->li);
    return i;
}

int get_elem(Pilha* stack, struct aluno *al){
    int i = list_front(stack->li, al);
    return i;
}

int pilha_vazia(Pilha* stack){
    int qtd = list_size(stack->li);
    return (qtd == 0);
}

int pilha_cheia(Pilha* stack){
    int qtd = list_size(stack->li);
    return (qtd != 0);
}
