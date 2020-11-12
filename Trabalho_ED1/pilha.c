#include"pilha.h"
#include<string.h>

struct caracter{
    int *Pilha;
    int current_size;
    int final_size;
};

Pilha* stack_create(int tam){
    Pilha* stack = malloc(sizeof(Pilha));
    if(stack == NULL)
       return NULL;
    stack->final_size = tam;
    stack->Pilha = malloc(tam * sizeof(int));
    if(stack->Pilha == NULL){
        free(stack);
        return NULL;
    } 
    stack->current_size = 0;
    return stack;
}

int push(Pilha *stack, int n){
    if(stack == NULL)
         return INVALID_NULL_POINTER;
    stack->Pilha[stack->current_size] = n;
    
    stack->current_size += 1;

    return SUCCESS; 
}

int pop(Pilha *stack){
    if(stack == NULL)
        return INVALID_NULL_POINTER;
    if(stack->current_size == 0)
        return OUT_OF_RANGE;

    stack->current_size --;
    return SUCCESS;
}

int get_element(Pilha *stack, int *elemento){
    if(stack == NULL)
        return INVALID_NULL_POINTER;  
    *elemento = stack->Pilha[stack->current_size - 1];
    return SUCCESS;
}

int stack_free(Pilha *stack){
    if(stack == NULL)
        return INVALID_NULL_POINTER;
    free(stack->Pilha);
    free(stack);
    return SUCCESS;
}

int stack_empty(Pilha *stack){
    if(stack == NULL)
       return INVALID_NULL_POINTER;
    return (stack->current_size == 0);
}

int stack_crowded(Pilha *stack){
    if(stack == NULL)
       return INVALID_NULL_POINTER;
    return (stack->current_size == stack->final_size);
}

int stack_size(Pilha *stack){
    if(stack == NULL)
       return INVALID_NULL_POINTER;
    return stack->current_size;    
}
