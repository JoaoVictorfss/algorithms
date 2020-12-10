#include "aluno.h"

typedef struct pilha Pilha;
//para lista
Pilha *cria_pilha();
void libera(Pilha* pilha);
int push(Pilha* li, struct aluno al);
int pop (Pilha* li);
int imprime(Pilha* li);
int get_elem(Pilha* stack, struct aluno *al);
int pilha_vazia(Pilha* stack);
int pilha_cheia(Pilha* stack);

