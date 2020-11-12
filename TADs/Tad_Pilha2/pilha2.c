#include"pilha2.h"
#include<string.h>

struct caracter{
    char *caracter;
    int current_size;
    int final_size;
};

Caracter* stack_creat(int tam){
    Caracter* stack = malloc(sizeof(Caracter));
    if(stack == NULL)
       return NULL;
    stack->final_size = tam;
    stack->caracter = malloc(tam * sizeof(char));
    if(stack->caracter == NULL){
        free(stack);
        return NULL;
    } 
    stack->current_size = 0;
    return stack;
}

int push(Caracter *stack, char caracter){
    if(stack == NULL)
         return INVALID_NULL_POINTER;
    stack->caracter[stack->current_size] = caracter;
    
    stack->current_size += 1;

    return SUCCESS; 
}

int pop(Caracter *stack){
    if(stack == NULL)
        return INVALID_NULL_POINTER;
    if(stack->current_size == 0)
        return OUT_OF_RANGE;

    stack->current_size --;
    return SUCCESS;
}

int get_element(Caracter *stack, char *elemento){
    if(stack == NULL)
        return INVALID_NULL_POINTER;  
    *elemento = stack->caracter[stack->current_size - 1];
    return SUCCESS;
}

int stack_free(Caracter *stack){
    if(stack == NULL)
        return INVALID_NULL_POINTER;
    free(stack->caracter);
    free(stack);
    return SUCCESS;
}

int stack_empty(Caracter *stack){
    if(stack == NULL)
       return INVALID_NULL_POINTER;
    return (stack->current_size == 0);
}

int stack_crowded(Caracter *stack){
    if(stack == NULL)
       return INVALID_NULL_POINTER;
    return (stack->current_size == stack->final_size);
}

int stack_size(Caracter *stack){
    if(stack == NULL)
       return INVALID_NULL_POINTER;
    return stack->current_size;    
}

int bemFormada (char s[], int tam){
   Caracter *stack = stack_creat(tam);
   for (int i = 0; s[i] != '\0'; i++) {
      char c;
      switch (s[i]){
         case ')': if (stack_empty(stack))
                      return 0; 
                   get_element(stack, &c);
                   if (c != '(') 
                      return 0;
                   pop(stack);
                   break;
         case ']': if (stack_empty(stack))
                      return 0; 
                   get_element(stack, &c);
                   if (c != '[') 
                      return 0;
                   pop(stack);
                   break;
         default:  push(stack, s[i]);
      }
   }
   if(stack_empty(stack))
        printf("\nBEM FORMADA\n");
   free(stack);
   return SUCCESS;
}

char *infixaParaPosfixa(char *str){
   char *vetPosf; 
   vetPosf = malloc ((strlen (str)+1) * sizeof (char));
   Caracter *stack = stack_creat(strlen (str));
   if(stack == NULL){
       return NULL;
   }
   int j = 0;
   for (int i = 0; str[i] != '\0'; i++) {
      switch (str[i]){
         char x;
         case '(': push(stack, str[i]);
                   break;
         case ')': get_element(stack, &x);
                   pop(stack);
                   while (x != '('){
                      vetPosf[j++] = x;
                      get_element(stack, &x);
                      pop(stack);
                   }
                   break;
         case '+': 
         case '-': get_element(stack, &x);
                   pop(stack);
                   while (x != '(') {
                      vetPosf[j++] = x;
                      get_element(stack, &x);
                      pop(stack);
                   }
                   push(stack, x);
                   push(stack, str[i]);
                   break;
         case '*':
         case '/': get_element(stack, &x);
                   pop(stack);
                   while (x != '(' && x != '+' && x != '-') {
                      vetPosf[j++] = x;
                      get_element(stack, &x);
                      pop(stack);
                   }
                   push(stack, x);
                   push(stack, str[i]);
                   break;
         default:  vetPosf[j++] = str[i];
      }
   }
   free(stack);
   vetPosf[j] = '\0';     
   return vetPosf;
}  

int calculo_posfix (char *posfix){
    int tam = strlen(posfix);
    Caracter *stackNumero = stack_creat(tam);
    int resultado = 0;
    char  aux;
    char aux2;
    int auxint1 = 0, auxint2 = 0;
    for(int i = 0; posfix[i] != '\0'; i++){
         switch (posfix[i]){
               case '+':
                        get_element(stackNumero, &aux);
                        pop(stackNumero);
                        get_element(stackNumero, &aux2);
                        pop(stackNumero);
                        auxint1 = aux - '0';
                        auxint2 = aux2 - '0';
                        resultado = auxint1 + auxint2; 
                        aux = resultado + '0';
                        push(stackNumero, aux);  
               break;
               case '-':
                        get_element(stackNumero, &aux);
                        pop(stackNumero);
                        get_element(stackNumero, &aux2);
                        pop(stackNumero);
                        auxint1 = aux - '0';
                        auxint2 = aux2 - '0';
                        resultado = auxint2 - auxint1; 
                        aux = resultado + '0';                          
                        push(stackNumero, aux); 
               break;
               case '*':
                        get_element(stackNumero, &aux);
                        pop(stackNumero);
                        get_element(stackNumero, &aux2);
                        pop(stackNumero);
                        auxint1 = aux - '0';
                        auxint2 = aux2 - '0';
                        resultado = auxint1 * auxint2; 
                        aux = resultado + '0';
                        push(stackNumero, aux);   
               break;
               case '/':
                        get_element(stackNumero, &aux);
                        pop(stackNumero);
                        get_element(stackNumero, &aux2);
                        pop(stackNumero);
                        auxint1 = aux - '0';
                        auxint2 = aux2 - '0';
                        resultado = auxint2 / auxint1; 
                        aux = resultado + '0';                          
                        push(stackNumero, aux);  
               break;
               default: push(stackNumero, posfix[i]);
         }
   }
   printf("Resultado: %d\n", resultado);
   free(stackNumero);
   return SUCCESS;
}
