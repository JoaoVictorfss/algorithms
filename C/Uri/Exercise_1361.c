/*
*@author João Victor
*@date 29.08.2020
* sort
*/

#include <stdio.h>
#include <stdlib.h>

struct floor
{
  int value;
  int positive;
};

typedef struct floor FLOOR;

void sort(FLOOR *arr, int low, int high);
int answer(int n);

int main()
{
  int n, cases, i;
  scanf("%d", &n);

  for (i = 0; i < n; i++)
  {
    scanf("%d", &cases);
    answer(cases);
  }

  return 0;
}

int answer(int n)
{
  FLOOR floors[n];
  int i;

  for (i = 0; i < n; i++)
  {
    int aux;
    scanf("%d", &aux);
    if (aux < 0)
    {
      floors[i].value = (-1 * aux);
      floors[i].positive = 0;
    }
    else
    {
      floors[i].value = aux;
      floors[i].positive = 1;
    }
  }

  sort(floors, 0, n - 1);

  int qtd = 1;
  FLOOR aux = floors[0];
  for (i = 1; i < n; i++)
  {
    if (aux.positive)
    {
      if (floors[i].positive == 0 && floors[i].value < aux.value)
      {
        aux = floors[i];
        qtd++;
      }
    }
    else
    {
      if (floors[i].positive == 1 && floors[i].value < aux.value)
      {
        aux = floors[i];
        qtd++;
      }
    }
  }

  printf("%d\n", qtd);

  return 0;
}

void swap(FLOOR *a, FLOOR *b)
{
  FLOOR t = *a;
  *a = *b;
  *b = t;
}

int partition(FLOOR *arr, int low, int high)
{
  int pivot = arr[high].value;
  int i = (low - 1);
  int j;
  for (j = low; j <= high - 1; j++)
  {
    if (arr[j].value > pivot)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[i + 1], &arr[high]);

  return (i + 1);
}

void sort(FLOOR *arr, int low, int high)
{
  if (low >= high)
    return;
  else
  {
    int j = partition(arr, low, high);
    sort(arr, low, j - 1);
    sort(arr, j + 1, high);
  }
}