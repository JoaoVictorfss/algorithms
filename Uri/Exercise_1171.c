/*
*@author João Victor
*@date 29.08.2020
*sort
*/

#include <stdio.h>
#include <stdlib.h>

void suffle(int *vet, int length);
void sort(int *arr, int low, int high);

int main()
{
  int n, i;
  scanf("%d", &n);
  int numbers[n];

  for (i = 0; i < n; i++)
    scanf("%d", &numbers[i]);

  suffle(numbers, n);
  sort(numbers, 0, n - 1);

  int cont = 1;
  for (i = 0; i < n; i++)
  {
    int aux = numbers[i + 1];
    if (aux == numbers[i])
      cont++;
    else
    {
      printf("%d aparece %d vez(es)\n", numbers[i], cont);
      cont = 1;
    }
  }

  return 0;
}

void suffle(int *vet, int length)
{
  int i;
  for ( i = 0; i < length; i++)
  {
    int r = rand() % length;

    int temp = vet[i];
    vet[i] = vet[r];
    vet[r] = temp;
  }
}

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int *arr, int low, int high)
{
  int pivot = arr[high];
  int i = (low - 1);
  int j;
  for (j = low; j <= high - 1; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[i + 1], &arr[high]);

  return (i + 1);
}

void sort(int *arr, int low, int high)
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