/*
*@authorJoão Victor
*@date 29.08.2020
*sort
*/

#include <stdio.h>
#include <stdlib.h>

void sort(int *arr, int low, int high);
void insertionSort(int *arr, int n);
int search(int x, int n, int *arr);
void suffle(int *vet, int length);

int main()
{

  int q, e, i, j, aux;
  scanf("%d %d", &q, &e);

  int visited[q + e];

  for (i = 0; i < e; i++)
    scanf("%d", &visited[i]);

  suffle(visited, e);
  sort(visited, 0, e - 1);

  aux = i;

  for (i = 0; i < q; i++)
  {
    int office;
    scanf("%d", &office);

    int found = search(office, aux, visited);

    if (found)
      printf("0\n");
    else
    {
      visited[aux] = office;
      aux++;
      insertionSort(visited, aux);
      printf("1\n");
    }
  }

  return 0;
}

void suffle(int *vet, int length)
{
  int i;
  for (i = 0; i < length; i++)
  {
    int r = rand() % length;

    int temp = vet[i];
    vet[i] = vet[r];
    vet[r] = temp;
  }
}

int search(int x, int n, int *arr)
{
  if (arr[0] == x)
    return 1;
  int e, m, d;
  e = 0;
  d = n - 1;
  while (e <= d)
  {
    m = (e + d) / 2;
    if (arr[m] == x)
      return m;
    if (arr[m] < x)
      e = m + 1;
    else
      d = m - 1;
  }
  return 0;
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

void insertionSort(int *arr, int n)
{
  int i, key, j;
  for (i = 1; i < n; i++)
  {
    key = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}