/*
*@author João Victor
* binary search tree
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE *BinTree;
typedef struct NODE NODE;

int jump = 0;

struct NODE
{
  int id;
  struct NODE *left;
  struct NODE *right;
};

BinTree *create()
{
  BinTree *raiz = (BinTree *)malloc(sizeof(BinTree));
  if (raiz != NULL)
    *raiz = NULL;
  return raiz;
}

void free_NODE(struct NODE *node)
{
  if (node == NULL)
    return;
  free_NODE(node->left);
  free_NODE(node->right);
  free(node);
  node = NULL;
}

void free_BinTree(BinTree *raiz)
{
  if (raiz == NULL)
    return;
  free_NODE(*raiz);
  free(raiz);
}

void preOrder(BinTree *raiz)
{
  if (*raiz != NULL)
  {

    if (jump == 1)
      printf(" %d", (*raiz)->id);
    else
    {
      printf("%d", (*raiz)->id);
      jump = 1;
    }
    preOrder(&((*raiz)->left));
    preOrder(&((*raiz)->right));
  }
}

void inOrder(BinTree *raiz)
{
  if (*raiz != NULL)
  {
    inOrder(&((*raiz)->left));
    if (jump == 1)
      printf(" %d", (*raiz)->id);
    else
    {
      printf("%d", (*raiz)->id);
      jump = 1;
    }
    inOrder(&((*raiz)->right));
  }
}

void postOrder(BinTree *raiz)
{
  if (*raiz != NULL)
  {
    postOrder(&((*raiz)->left));
    postOrder(&((*raiz)->right));
    if (jump == 1)
      printf(" %d", (*raiz)->id);
    else
    {
      printf("%d", (*raiz)->id);
      jump = 1;
    }
  }
}

int insertion(BinTree *raiz, int id)
{
  struct NODE *node;
  node = (struct NODE *)malloc(sizeof(struct NODE));
  node->id = id;
  node->right = NULL;
  node->left = NULL;

  if (*raiz == NULL) 
    *raiz = node;
  else
  {
    struct NODE *atual = *raiz;
    struct NODE *ant = NULL;
    while (atual != NULL)
    {
      ant = atual;
      if (id == atual->id) 
      {
        free(node);
        return 0;
      }
      if (id > atual->id)
        atual = atual->right;
      else
        atual = atual->left;
    }
    if (id > ant->id)
      ant->right = node;
    else
      ant->left = node;
  }
  return 1;
}

void walkTree(int m)
{
  BinTree *raiz = create();
  int n, i;
  scanf("%d", &n);

  for (i = 0; i < n; i++)
  {
    int aux;
    scanf("%d", &aux);
    insertion(raiz, aux);
  }

  printf("Case %d:\n", m + 1);

  printf("Pre.: ");
  preOrder(raiz);
  printf("\n");
  jump = 0;

  printf("In..: ");
  inOrder(raiz);
  printf("\n");
  jump = 0;

  printf("Post: ");
  postOrder(raiz);
  printf("\n");
  jump = 0;

  free_BinTree(raiz);
}

int main()
{
  int n, i;
  scanf("%d", &n);

  for (i = 0; i < n; i++)
  {
    walkTree(i);
    printf("\n");
  }
  return 0;
}