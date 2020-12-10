/*
*@author João Victors
* dictionary
*/

#include <stdio.h>
#include <string.h>

#define MAX 201

float get(char k)
{
  char key[] = {'E', 'H', 'Q', 'S', 'T', 'W', 'X'};
  float value[] = {0.125, 0.5, 0.25, 0.0625, 0.03125, 1.0, 0.015625};

  if (key[0] == k)
    return value[0];

  int e, m, d;
  e = 0;
  d = 6;

  while (e <= d)
  {
    m = (e + d) / 2;
    if (key[m] == k)
      return value[m];
    if (key[m] < k)
      e = m + 1;
    else
      d = m - 1;
  }
}

int main()
{
  char string[MAX];

  gets(string);

  while (string[0] != '*')
  {
    int i;
    float aux = 0.0;
    int total = 0;
    int lenght = strlen(string);
    int form = 0;

    for (i = 0; i < lenght; i++)
    {
      if (string[i] != '/' && form)
      {
        float value = get(string[i]);
        aux += value;
      }
      else
      {
        form++;
        if (aux == 1 && form == 2)
          total++;

        aux = 0.0;
        form = 1;
      }
    }

    printf("%d\n", total);

    gets(string);
  }

  return 0;
}