#include "game.h"

/** \paran static s_ennemy *g_ennemy = NULL
** Global variable for the list of ennemies.
*/
static s_ennemy *g_ennemy = NULL;

/** \fn static s_ennemy *type_ennemy(e_ennemy type, s_ennemy *guy)
** It initializes the level of monsters.
*/
static s_ennemy *type_ennemy(e_ennemy type, s_ennemy *guy)
{
  if (type == E_E_EASY)
  {
    guy->max_life = 50;
    guy->life = 50;
    guy->speed = 1;
    guy->aff = malloc(sizeof (char) * 14);
    strcpy(guy->aff, "src/ennemi.bmp");
  }
  if (type == E_E_MEDIUM)
  {
    guy->max_life = 100;
    guy->life = 100;
    guy->speed = 2;
    guy->aff = malloc(sizeof (char) * 14);
    strcpy(guy->aff, "src/ennemi.bmp");
  }
  if (type == E_E_HARD)
  {
    guy->max_life = 200;
    guy->life = 200;
    guy->speed = 4;
    guy->aff = malloc(sizeof (char) * 14);
    strcpy(guy->aff, "src/ennemi.bmp");
  }

  return (guy);
}

/** \fn static void kill_ennemy(s_ennemy *guy, s_ennemy *prev)
** It is erasing the monster in its list.
*/
static void kill_ennemy(s_ennemy *guy, s_ennemy *prev, SDL_Surface *enn)
{
  s_ennemy *next;
  int i = 0;

  next = guy->next;
  free(guy->aff);
  guy->aff = NULL;
  free(guy);
  guy = NULL;
  SDL_FreeSurface(enn);
  if (next == NULL)
    prev->next = NULL;
  else
    prev->next = next;

  i = prev->number;
  while (prev->next != NULL)
  {
    prev->next->number = i + 1;
    prev->next = prev;
  }
}

/** \fn s_ennemy *init_ennemy(e_ennemy type, int x, int y)
** It is initializing the monster.
*/
s_ennemy *init_ennemy(e_ennemy type, int x, int y)
{
  g_ennemy = malloc(sizeof (s_ennemy));
  g_ennemy->type = type;
  g_ennemy->number = 0;
  g_ennemy = type_ennemy(type, g_ennemy);
  g_ennemy->dir = DROITE;
  g_ennemy->rec.x = x;
  g_ennemy->rec.y = y;
  g_ennemy->next = NULL;

  return (g_ennemy);
}

/** \fn SDL_Surface *add_ennemy(e_ennemy type, int x, int y, SDL_Surface *aff)
** It is adding the monster in its list.
*/
SDL_Surface *add_ennemy(e_ennemy type, int x, int y, SDL_Surface *aff)
{
  s_ennemy *guy = g_ennemy;
  int i = 0;
  s_ennemy *prev;
  SDL_Surface *img = NULL;
  SDL_Rect pos;

  if (guy == NULL)
    guy = init_ennemy(type, x, y);
  else
  {
    while (guy->next != NULL)
    {
      guy = guy->next;
      i++;
    }
    i++;
    prev = guy;
    guy = guy->next;
    guy = malloc(sizeof (s_ennemy));
    prev->next = guy;
    guy->type = type;
    guy = type_ennemy(type, guy);
    guy->dir = DROITE;
    guy->number = i;
    guy->rec.x = x;
    guy->rec.y = y;
    guy->next = NULL;
  }
  pos.x = guy->rec.x;
  pos.y = guy->rec.y;
  img = IMG_Load(guy->aff);
  SDL_BlitSurface(img, NULL, aff, &pos);

return (img);
}

/** \fn void touch_ennemy(int nbr, int dmg)
** It is seeing is the monster is touch by a bullet or not
*/
void touch_ennemy(int nbr, int dmg, SDL_Surface *enn)
{
  s_ennemy *guy = g_ennemy;
  s_ennemy *prev;

  while ((guy->number != nbr) && (guy->next != NULL))
  {
    prev = guy;
    guy = guy->next;
  }

  if (guy->number == nbr)
    guy->life = guy->life - dmg;
  if (guy->life <= 0)
    kill_ennemy(guy, prev, enn);
  if (guy->number == nbr)
    guy->life = guy->life - dmg;
  if (guy->life <= 0)
    kill_ennemy(guy, prev, enn);
}

/** \fn SDL_Rect move_ennemy(int nbr, int **tab)
** It is moving the monster in function of its direction.
*/
SDL_Rect move_ennemy(int nbr, int **tab)
{
  s_ennemy *guy = g_ennemy;
  int      i = 0;
  int      j = 0;

  while ((guy->number != nbr) && (guy->next != NULL))
    guy = guy->next;

  if (guy->life <= 0)
    guy->rec.x = 920;

  i = (guy->rec.x) / 40;
  j = (guy->rec.y) / 40;

  if (guy->dir == DROITE)
    guy = go_right(i, j, tab, guy);
  else
    if (guy->dir == GAUCHE)
      guy = go_left(i, j, tab, guy);
    else
      if (guy->dir == HAUT)
	guy = go_up(i, j, tab, guy);
      else
	if (guy->dir == BAS)
	  guy = go_down(i, j, tab, guy);
  return (guy->rec);
}
