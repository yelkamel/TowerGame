#include "game.h"

/** \param static const int g_int = 40;
** Global variable for the speed of each monsters.
*/
static const int g_int = 40;

/** \fn s_ennemy *compare(int i, int j, s_ennemy *guy)
** Compare the placement of the monster and its last position in the tab**
*/
/*s_ennemy *compare(int i, int j, s_ennemy *guy)
{
  if (guy->dir == guy->prev_d)
  {
    guy->y_prev = j;
    guy->x_prev = i;
  }
  if ((guy->dir != guy->prev_d))
  {
    if (guy->rec.x == j && guy->rec.y == i)
    {
      guy->dir = guy->prev_d;
    }
  }

  return (guy);
}*/

/** \fn s_ennemy *go_right(int i, int j, int **tab, s_ennemy *guy)
** This function take the direction of the monster and see where he has to go.
*/
s_ennemy *go_right(int i, int j, int **tab, s_ennemy *guy)
{
  if ((i < 23) && (tab[j][i + 1] == E_PATH))
  {
    guy->rec.x += g_int * guy->speed;
    guy->dir = DROITE;
  }
  else
    if ((j < 21) && (tab[j + 1][i] == E_PATH))
    {
      guy->rec.y += g_int * guy->speed;
      guy->dir = BAS;
    }
    else
      if ((j > 0) && (tab[j - 1][i] == E_PATH))
    {
      guy->rec.y -= g_int * guy->speed;
      guy->dir = HAUT;
    }

  return (guy);
}

/** \fn s_ennemy *go_left(int i, int j, int **tab, s_ennemy *guy)
** This function take the direction of the monster
** It sees where it has to go from this left direction
*/
s_ennemy *go_left(int i, int j, int **tab, s_ennemy *guy)
{
  if ((i - 1) > 0 && (tab[j][i - 1] == E_PATH))
  {
    guy->rec.x -= g_int * guy->speed;
    guy->dir = GAUCHE;
  }
  else
    if ((j < 21) && (tab[j + 1][i] == E_PATH))
    {
      guy->rec.y += g_int * guy->speed;
      guy->dir = BAS;
    }
    else
      if ((j > 0) && (tab[j - 1][i] == E_PATH))
      {
	guy->rec.y -= g_int * guy->speed;
	guy->dir = HAUT;
      }

  return (guy);
}


/** \fn s_ennemy *go_up(int i, int j, int **tab, s_ennemy *guy)
** This function take the direction of the monster
** It sees where it has to go from this Top direction
*/
s_ennemy *go_up(int i, int j, int **tab, s_ennemy *guy)
{

  if ((i < 23) && (tab[j][i + 1] == E_PATH))
  {
    guy->rec.x += g_int * guy->speed;
    guy->dir = DROITE;
  }
  else
    if ((i > 0) && (tab[j][i - 1] == E_PATH))
    {
      guy->rec.x -= g_int * guy->speed;
      guy->dir = GAUCHE;
    }
    else
      if ((j > 0) && (tab[j - 1][i] == E_PATH))
      {
	guy->rec.y -= g_int * guy->speed;
	guy->dir = HAUT;
      }

  return (guy);
}


/** \fn s_ennemy *go_down(int i, int j, int **tab, s_ennemy *guy)
** This function take the direction of the monster
** It sees where it has to go from this Bottom direction
*/
s_ennemy *go_down(int i, int j, int **tab, s_ennemy *guy)
{
  if ((i <= 23) && (tab[j][i + 1] == E_PATH))
  {
    guy->rec.x += g_int * guy->speed;
    guy->dir = DROITE;
  }
  else
    if ((i >= 0) && (tab[j][i - 1] == E_PATH))
    {
      guy->rec.x -= g_int * guy->speed;
      guy->dir = GAUCHE;
    }
    else
      if ((j < 21) && (tab[j + 1][i] == E_PATH))
      {
	guy->rec.y += g_int * guy->speed;
	guy->dir = BAS;
      }
     else
       if ((j < 21) && (tab[j + 1][i] == E_PATH))
       {
       guy->rec.y += 40 * guy->speed;
       guy->dir = BAS;
       }

  return (guy);
}
