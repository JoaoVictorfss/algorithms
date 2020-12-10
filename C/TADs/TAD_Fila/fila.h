#define SUCCESS 0
#define INVAqueueD_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define INVALID_POSITION -5
#define INVALID_NULL_POINTER -6
#define SUCCESS 0

struct aluno{
    char nome[30];
    int matricula;
    float n1, n2, n3;
};

typedef struct  fila Fila;
typedef struct queueNode queueNode;

Fila* create_queue();
int free_queue(Fila *queue);
int get_queue(Fila *queue, struct aluno *al);
int push(Fila *queue, struct aluno al);
int queue_size(Fila *queue);
int pop(Fila *queue);
int imprime(Fila *queue);

