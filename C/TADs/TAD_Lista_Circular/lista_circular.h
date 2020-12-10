#define SUCCESS 0
#define OUT_OF_MEMORY -1
#define ELEM_NOT_FOUND -2
#define INVALID_NULL_POINTER -3
#define INVALID_VALOR -4
#define ELEMENT_OUT_OF_RANGE -5

struct aluno{
    char nome[30];
    int matricula;
    float n1, n2, n3;
};

typedef struct circlist Circlist;

Circlist *create_circular_list();
int free_circular_list(Circlist *li);
int push_front(Circlist *li, struct aluno al);
int push_back(Circlist *li, struct aluno al);
int pop_front(Circlist *li);
int imprime(Circlist *li);
int size_circular_list(Circlist *li);
int pop_back(Circlist *li);
int show_element(Circlist *li);
int pop_mat(Circlist *li, int mat);