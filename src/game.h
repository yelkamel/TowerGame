#ifndef GAME_H_
# define GAME_H_

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <SDL/SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <SDL_video.h>
# include <SDL_image.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>


typedef enum direction
{
  HAUT,
  DROITE,
  BAS,
  GAUCHE
} e_dir;

typedef enum type_tower
{
  E_T_EASY,
  E_T_MEDIUM,
  E_T_HARD
} e_tower;

typedef enum type_ennemy
{
  E_E_EASY,
  E_E_MEDIUM,
  E_E_HARD,
} e_ennemy;

typedef enum type_block
{
  E_GROUND,
  E_TOWER,
  E_PATH,
  E_T_1,
  E_T_2,
  E_T_3,
  E_NONE
} e_block;

typedef struct player
{
  int life;
  int money;
  int nbr_turret;
}     s_player;

typedef struct ennemy
{
  e_ennemy      type;
  int           number;
  int           max_life;
  int           life;
  int           speed;
  e_dir         dir;
  e_dir         prev_d;
  SDL_Rect      rec;
  char          *aff;
  struct ennemy *next;
}               s_ennemy;

typedef struct tower
{
  int          type;
  int          cost;
  int          damage;
  int          radius;
  int          x;
  int          y;
  struct tower *next;
}              s_tower;

int **init_map(char              *file);
SDL_Surface **init_mob(int       mob, SDL_Surface *aff);
void new_image(char              *name, int posx, int posy);
int **mouvement(int              **tab);
SDL_Surface *add_ennemy(e_ennemy type, int x, int y, SDL_Surface *aff);
SDL_Rect pos_ennemy(int          nbr);
SDL_Rect move_ennemy(int         nbr, int **tab);
s_ennemy *go_right(int           i, int j, int **tab,s_ennemy *guy);
s_ennemy *go_left(int            i, int j, int **tab,s_ennemy *guy);
s_ennemy *go_down(int            i, int j, int **tab,s_ennemy *guy);
s_ennemy *go_up(int              i, int j, int **tab, s_ennemy *guy);
void touch_ennemy(int            nbr, int dmg, SDL_Surface *enn);

#endif /* !GAME_H_ */
