#include "game.h"

SDL_Surface **init_mob(int mob, SDL_Surface *aff)
{
  SDL_Surface **tab = NULL;
  int i = 0;

  tab = malloc(sizeof (SDL_Surface *) * mob);
  for (i = 0; i < mob; i++)
      tab[i] = add_ennemy(E_E_EASY, 0, 80, aff);

  return (tab);
}

int **init_map(char *file)
{
  int **tab = NULL;
  int i = 0;
  int j = 0;
  FILE *map;
  int c = 0;

  tab = malloc(sizeof (int *) * 21);
  for (i = 0; i < 22; i++)
    tab[i] = malloc(sizeof (int) * 23);

  if ((map = fopen(file,"r+")) == NULL)
    exit(EXIT_FAILURE);
  j = 0;
  i = 0;
  while ((c = fgetc(map)) != EOF)
  {
    if (c == '\n')
    {
      j = 0;
      ++i;
      c = fgetc(map);
    }
    if (c == '0')
      tab[i][j] = E_GROUND;
    if (c == '1')
      tab[i][j] = E_TOWER;
    if (c == '2')
      tab[i][j] = E_PATH;
    if (c == '3')
      tab[i][j] = E_T_1;
    if (c == '4')
      tab[i][j] = E_T_2;
    if (c == '5')
      tab[i][j] = E_T_3;
    if (c == '6')
      tab[i][j] = E_NONE;
    j++;
  }
  fclose(map);

  return (tab);
}
