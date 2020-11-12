/*
*@ João Victor
*@date 23.08.2020
*dynamic programming
*/

#include <stdio.h>

#define W 50

void christmasPresents()
{
  int packs = 0, n, i, w, weight;
  scanf("%d", &n);

  int toys[n], weights[n], memo[n + 1][W + 1], el[n];

  for (i = 0; i < n; i++)
    scanf("%d %d", &toys[i], &weights[i]);

  for (i = 1; i <= n; i++)
    memo[i][0] = 0;

  for (w = 0; w <= W; w++)
    memo[0][w] = 0;

  for (i = 1; i <= n; i++)
  {
    weight = weights[i - 1];

    int qtt_toys = toys[i - 1];

    for (w = 1; w <= W; w++)
    {
      if (weight <= w)
      {
        if ((qtt_toys + memo[i - 1][w - weight]) > memo[i - 1][w])
          memo[i][w] = qtt_toys + memo[i - 1][w - weight];
        else
          memo[i][w] = memo[i - 1][w];
      }
      else
        memo[i][w] = memo[i - 1][w];
    }
  }

  weight = 0;
  w--;
  i--;
  while (i > 0)
  {
    if ((memo[i][w] != memo[i - 1][w]))
    {
      weight += weights[i - 1];
      packs++;
      w -= weights[i - 1];
    }
    i--;
  }

  printf("%d brinquedos\n", memo[n][W]);
  printf("Peso: %d kg\n", weight);
  printf("sobra(m) %d pacote(s)\n\n", n - packs);
}

int main()
{
  int n, i;
  scanf("%d", &n);

  for (i = 0; i < n; i++)
    christmasPresents();

  return 0;
}