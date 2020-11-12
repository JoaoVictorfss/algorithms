/*
*@author João Victor
* sort
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void fill_array(int *sequence, int size)
{
  int i = 0;
  for (i = 0; i < size; i++)
  {
    scanf("%d", &sequence[i]);
  }
}

int selection_sort()
{
  int n = 0;

  scanf("%d", &n);
  int arr[n];

  int i;
  int j = 0;
  int exchanges = 0;

  fill_array(arr, n);

  for (i = 0; i < n - 1; i++)
  {

    j = i + 1;
    while (arr[i] != (i + 1) && j < n)
    {
      if (arr[j] == (i + 1))
      {
        swap(&arr[j], &arr[i]);
        exchanges++;
      }
      j++;
    }
  }

  return exchanges;
}

int main()
{
  int n, i;

  scanf("%d", &n);

  for (i = 0; i < n; i++)
  {
    int exchange = selection_sort();
    printf("%d\n", exchange);
  }

  return 0;
}
