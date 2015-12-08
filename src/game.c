#include "game.h"

static SDL_Surface *g_screen= NULL;

/**
**\file game.c
**\fn static void mypause(void)
**\brief do game in pause
*/
static void mypause(void)
{
  int       continuer = 1;
  SDL_Event event;

  while (continuer)
  {
    SDL_Flip(g_screen);
    SDL_WaitEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
      continuer = 0;
    }
  }
}

/**
** \file game.c
** \fn static SDL_Surface *imgfond(const char *img)
** \brief create backgroud image
*/
static SDL_Surface *imgfond(const char *img)
{
  SDL_Surface *fond = NULL;
  SDL_Rect    posfond;

  posfond.x = 0;
  posfond.y = 0;
  fond =  IMG_Load(img);
  SDL_BlitSurface(fond, NULL, g_screen, &posfond);

  return (fond);
}

/**
** \file game.c
**\fn void new_image(char *name, int posx, int posy)
**\brief create new image
*/
void new_image(char *name, int posx, int posy)
{
  SDL_Surface *image = NULL;
  SDL_Rect    position;

  position.x = posx;
  position.y = posy;
  image = IMG_Load(name);
  SDL_BlitSurface(image, NULL, g_screen, &position);
}

/**
**\file game.c
**\fn static SDL_Color color(int r, int g, int b)
**\brief create new color
*/
static SDL_Color color(int r, int g, int b)
{
  SDL_Color color;

  color.r = r;
  color.g = g;
  color.b = b;
  return (color);
}

/**
**\file game.c
**\fn static SDL_Surface *text(char *text, int posx, int posy, SDL_Color c)
**\brief create text area
*/
static SDL_Surface *text(char *text, int posx, int posy, SDL_Color c)
{
  TTF_Font    *police = NULL;
  SDL_Surface *texte ;
  SDL_Rect    position;

  if (TTF_Init() == -1)
  {
    fprintf(stderr, "Erreur: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  police = TTF_OpenFont("./src/TechnoHideo.ttf", 40);
  texte = TTF_RenderText_Solid(police, text, c);
  position.x = posx;
  position.y = posy;
  SDL_BlitSurface(texte, NULL, g_screen, &position);
  TTF_CloseFont(police);

  return (texte);
}

void screen(int w, int h, char *name)
{
  Uint32 color;

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    fprintf(stderr, "Erreur de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  g_screen = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (g_screen == NULL)
  {
      fprintf(stderr, "Impossible : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption(name, NULL);
  color = SDL_MapRGB(g_screen->format, 54, 40, 30);
  SDL_FillRect(g_screen, NULL, color);
}

/**
**\file game.c
**\fn void infinity(void)
**\brief do body of function
*/
void infinity(void)
{
  SDL_Surface *texte;
  int         **tab;
  int          cont = 1;
  SDL_Event    event;

  tab = init_map("./src/map.txt");
  texte = text("0000", 40, 40, color(0, 0, 0));
  screen(920, 840, "WORLD OF ACU");
  imgfond("./src/map.bmp");
  new_image("./src/Canon.png", 840, 120);
  new_image("./src/AA.png", 840, 280);
  new_image("./src/missile.png", 840, 440);
  while (cont)
  {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      cont = 0;
    tab = mouvement(tab);
    SDL_Flip(g_screen);
    sleep(1);
  }
  mypause();
  SDL_FreeSurface(texte);
  TTF_Quit();
  SDL_Quit();
}

int main(void)
{
  infinity();
  return (0);
}
