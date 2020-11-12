#define SUCCESS 0
#define OUT_OF_MEMORY -1
#define ELEM_NOT_FOUND -2
#define INVALID_NULL_POINTER -3
#define INVALID_VALOR -4

struct aluno{
    char nome[30];
    int matricula;
    float n1, n2, n3;
};

typedef struct list List;

List* list_creat();
int list_free(List *li);

int list_push_front(List *li, struct aluno al);//insere início
int list_push_back(List *li, struct aluno al);//insere final
int list_insert(List *li, int pos, struct aluno al);//insere lista pela posição
int list_insert_sorted(List *li, struct aluno al);//insere lista ordenada
int list_size(List *li);//tamanho da lista

int list_pop_front(List *li);//apagar o primeiro elemento
int list_pop_back(List *li);//apagar o ultimo elemento
int list_erase(List *li, int pos);//apaga pela posição

int list_find_pos(List *li, int pos, struct aluno *al);//pega o elemento pela posição
int list_find_mat(List *li, int nmat, struct aluno *al);//pega o elemento pela matricula
int list_front(List *li, struct aluno *al);//pega o primeiro elemento
int list_back(List *li, struct aluno *al);//pega o último elemento
int list_get_pos(List *li, int nmat, int *pos);//recebe pela matricula a posição

int list_print(List *li);