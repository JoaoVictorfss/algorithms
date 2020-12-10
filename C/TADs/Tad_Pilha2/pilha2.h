#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define INVALID_POSITION -5

typedef struct caracter Caracter;

Caracter* stack_creat(int tam);
int bemFormada (char *s, int tam);
int push(Caracter *stack, char caracter);
int pop(Caracter *stack);
int get_element(Caracter *stack, char *elemento);
int stack_free(Caracter *stack);
int stack_empty(Caracter *stack);
int stack_crowded(Caracter *stack);
int stack_size(Caracter *stack);
char *infixaParaPosfixa(char *str);
int calculo_posfix (char *posfix);