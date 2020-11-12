/*
*@author João Victor
*@date 23.08.2020
* binary search tree
* Tower of Hanoi => dynamic programming
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Hanoi()
{
  int v = 2, n, i;
  int stop = 1;
  int position = 1;

  scanf("%d", &n);

  int *memo = calloc(n, sizeof(int));

  memo[0] = 1;

  while (stop)
  {
    for (i = 0; i < n; i++)
    {
      int raiz = (int)sqrt(memo[i] + v);
      if (pow(raiz, 2) == memo[i] + v)
      {
        if (memo[i] == 0)
          position++;

        memo[i] = v;
        i = n;
      }
      else
      {
        if (i == n - 1 && position == n)
          stop = 0;
        else
        {
          if (i == position)
          {
            memo[position] = v;
            position++;
            i = n;
          }
        }
      }
    }

    v++;
  }

  printf("%d\n", v - 2);

  free(memo);
}

int main()
{
  int n, i;
  scanf("%d", &n);

  for (i = 0; i < n; i++)
    Hanoi();

  return 0;
}