/*
*@author João Victor
*@date 29.08.2020
*/

#include <stdio.h>

int main()
{
  int i, n, cont;
  int n_att = 1;

  while (1)
  {
    scanf("%d", &n);
    if (n == 0)
      break;

    while (1)
    {
      cont = 0;
      for (i = 1; i <= n; i++)
      {
        int aux;
        scanf("%d", &aux);
        if (aux == i)
          cont++;
      }

      if (cont == n)
      {
        printf("%d\n", n_att);
        n_att = 1;
        break;
      }
      else
        n_att++;
    }
  }
  return 0;
}