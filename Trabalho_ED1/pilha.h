#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 0
#define INVALID_NULL_POINTER -3
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -1
#define ELEM_NOT_FOUND -4
#define INVALID_POSITION -5

typedef struct caracter Pilha;

Pilha* stack_create(int tam);
int push(Pilha *stack, int n);
int pop(Pilha *stack);
int get_element(Pilha *stack, int *elemento);
int stack_free(Pilha *stack);
int stack_empty(Pilha *stack);
int stack_crowded(Pilha *stack);
int stack_size(Pilha *stack);