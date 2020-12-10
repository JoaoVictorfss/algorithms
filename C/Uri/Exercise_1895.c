/*
*@author João Victor
* data structure
*/

#include <stdio.h>
#include <stdlib.h>

struct deck
{
  int *cards;
  int latest_position;
  int current_position;
  int size;
};

typedef struct deck Deck;

Deck *deck_creat(int size)
{

  Deck *deck = malloc(sizeof(Deck));
  if (deck == NULL)
    return NULL;

  deck->cards = malloc(size * sizeof(int));

  if (deck->cards == NULL)
  {
    free(deck);
    return NULL;
  }

  deck->latest_position = (size - 1);
  deck->current_position = (size - 1);
  deck->size = size;

  return deck;
}

int deck_push(Deck *deck, int card)
{
  if (deck == NULL)
    return -1;

  deck->cards[deck->current_position] = card;
  deck->current_position--;

  return 0;
}

int get_card(Deck *deck, int *card)
{
  if (deck == NULL)
    return -1;

  *card = deck->cards[deck->latest_position];

  deck->latest_position--;

  return 0;
}

int deck_free(Deck *deck)
{
  if (deck == NULL)
    return -1;

  free(deck->cards);
  free(deck);

  return 0;
}

int score(Deck *deck, int *t, int l)
{
  int a = 0;
  int b = 0;

  int i;
  for (i = 1; i <= deck->size; i++)
  {
    int s;
    get_card(deck, &s);

    int calc = abs(*t - s);
    if (calc <= l)
    {
      *t = s;
      if (i % 2 == 0)
        b += calc;
      else
        a += calc;
    }
  }

  printf("%d %d\n", a, b);

  return 0;
}

int main()
{
  int n, t, l;

  scanf("%d %d %d", &n, &t, &l);

  int size = n - 1;

  Deck *deck = deck_creat(size);

  int i;
  for (i = 0; i < size; i++)
  {
    int n;
    scanf("%d", &n);
    deck_push(deck, n);
  }

  score(deck, &t, l);

  deck_free(deck);
  return 0;
}
