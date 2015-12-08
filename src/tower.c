#include "game.h"

static s_tower *g_tower = NULL;

/**
**\file tower.c
**\fn static s_tower *towers(int type, int cost, int damage, int radius)
**\brief initiaze new s_tower
*/
static s_tower *towers(int type, int cost, int damage, int radius)
{
  s_tower *t = NULL;

  t = malloc(sizeof (s_tower));
  t->type = type;
  t->cost = cost;
  t->damage = damage;
  t->radius = radius;
  t->next = NULL;

  return (t);
}

/**
**\file tower.c
**\fn static s_tower *init_tower(int type)
**\brief choose type of tower
*/
static s_tower *init_tower(int type)
{
  s_tower *t = NULL;

  if (type == E_T_1)
  {

    return (towers(E_T_1, 10, 1, 40));
  }
  if (type == E_T_2)
  {

    return (towers(E_T_2, 20, 2, 40));
  }
  if (type == E_T_3)
  {

    return (towers(E_T_3, 30, 3, 40));
  }

  return (t);
}

static s_tower *take_tower(int **tab,int bx, int by)
{
  s_tower *t;
  int     x;
  int     y;

  x = bx / 40;
  y = by / 40;
  t = init_tower(tab[y][x]);

  return(t);
}

/**
**\file tower.c
**\fn static void type_tower(int type, int x, int y)
**\brief load image of type of tower
*/
static void type_tower(int type, int x, int y)
{
  if (type == E_T_1)
    new_image("./src/Canon.png", x * 40, y * 40);
  if (type == E_T_2)
    new_image("./src/AA.png", x * 40, y * 40);
  if (type == E_T_3)
    new_image("./src/missile.png", x * 40, y * 40);
}

static int **initglob(int **tab, s_tower *new, int x, int y)
{
  s_tower *t;

  g_tower = malloc(sizeof (s_tower));
  t = new;
  g_tower->type = t->type;
  g_tower->cost = t->cost;
  g_tower->damage = t->damage;
  g_tower->radius = t->radius;
  g_tower->x = x;
  g_tower->y = y;
  g_tower->next = NULL;
  tab[y][x] = E_TOWER;
  type_tower(new->type, x, y);
  return (tab);
}

int **rectower(int **tab, s_tower *new, int x, int y)
{
  s_tower   *t;
  s_tower   *next;

  t = g_tower;
  while (t->next != NULL)
    t = t->next;
  next = new;
  t->next = next;
  next->next = NULL;
  next->x = x;
  next ->y = y;
  tab[y][x] = E_TOWER;
  type_tower(new->type, x, y);

  return (tab);
}

/**
**\file tower.c
**\fn static int **put_tower(int **tab, s_tower *new)
**\brief put tower in map
*/
static int **put_tower(int **tab, s_tower *new)
{
  SDL_Event event;
  int       x;
  int       y;
  int       cont = 1;

  while (cont)
  {
    SDL_PollEvent(&event);
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      x = event.button.x / 40;
      y = event.button.y / 40;
      if (event.button.button == SDL_BUTTON_LEFT)
      {
	if (tab[y][x] == E_GROUND)
	{
	  cont = 0;
	  if (g_tower == NULL)
	    tab = initglob(tab, new, x, y);
	  else
	    tab = rectower(tab, new, x, y);
	}
      }
    }
  }

  return (tab);
}


/**
**\file tower.c
**\fn int **mouvement(int **tab)
**\brief take and put a tower in the map
*/
int **mouvement(int **tab)
{
  s_tower   *t;
  int       next = 1;
  int       x;
  int       y;
  SDL_Event event;

  while (next)
  {
    SDL_PollEvent(&event);
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      if (event.button.button == SDL_BUTTON_LEFT)
      {
	x = event.button.x;
	y = event.button.y;
	if ((t = take_tower(tab, x, y)) != NULL)
	  next = 0;
      }
    }
  }

  return (put_tower(tab, t));
}
