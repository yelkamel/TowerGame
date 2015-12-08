#include "game.h"

SDL_Surface *imgfond(const char *img, SDL_Surface *affichage)
{
    SDL_Surface *fond = NULL;
    SDL_Rect posfond;

    posfond.x = 0;
    posfond.y = 0;
    fond =  IMG_Load(img);
    SDL_BlitSurface(fond, NULL, affichage,&posfond);
    return (fond);
}

int menujeux(const char *img, SDL_Surface *affichage)
{
    SDL_Surface *fond = NULL;
    SDL_Rect posfond;
    SDL_Event event;
    posfond.x = 0;
    posfond.y = 0;

    fond =  IMG_Load(img);
    SDL_BlitSurface(fond, NULL, affichage,&posfond);
    while (1)
    {
        SDL_FillRect(affichage,NULL,SDL_MapRGB(affichage->format,255,255,255));
        SDL_BlitSurface(fond, NULL, affichage, 0);
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return (0);
            case SDL_MOUSEBUTTONUP:
                if (event.button.x > 220
                        && event.button.x < 700
                        && event.button.y > 370
                        && event.button.y < 470)
                    return (1);
                else
                    if (event.button.x > 750
                            && event.button.y > 720)
                        return (2);
            default : break;
        }
        SDL_Flip(affichage);
    }
    return (0);
}

SDL_Rect projectil(SDL_Rect proj, SDL_Rect mec, SDL_Rect tour, SDL_Surface *en)
{
    int dist;
    dist = sqrt((pow(fabs(mec.x - proj.x),2) + pow(mec.y - proj.y,2)));

    if (dist <= 300)
    {
        if (mec.x == proj.x && mec.y > proj.y)
            proj.y += 2;
        else
            if (mec.x > proj.x && mec.y == proj.y)
                proj.x += 2;

            else
                if (mec.x == proj.x && mec.y < proj.y)
                    proj.y -= 2;
                else
                    if (mec.x < proj.x && mec.y == proj.y)
                        proj.x -= 2;
                    else
                        if (mec.x < proj.x && mec.y < proj.y)
                        {
                            proj.x -= 1;
                            proj.y -= 1;

                        }
                        else
                            if (mec.x > proj.x && mec.y > proj.y)
                            {
                                proj.x += 1;
                                proj.y += 1;
                            }

                            else
                                if (mec.x > proj.x && mec.y < proj.y)
                                {
                                    proj.x += 1;
                                    proj.y -= 1;
                                }
                                else
                                    if (mec.x < proj.x && mec.y > proj.y)
                                    {

                                        proj.x -= 1;
                                        proj.y += 1;
                                    }
                                    else
                                        if (mec.x == proj.x && proj.y == mec.y)
                                        {
                                            proj.x = tour.x;
                                            proj.y = tour.y;
                                        }

    }
    else
    {

        proj.x = tour.x;
        proj.y = tour.y;
        en = en;
    }
    return (proj);
}

int main(void)
{
    SDL_Surface *affichage = NULL;
    SDL_Surface *fond;
    int i = 0;
    int  continu = 0;
    SDL_Event event;
    SDL_Surface **mechant;
    SDL_Surface *tour;
    SDL_Surface *proj;
    SDL_Rect posmechant;
    SDL_Rect postour;
    SDL_Rect posproj;
    int j = 0;
    int nb_mob = 7;
    int **tab;

    postour.x = 355;
    postour.y = 425;
    posproj = postour;
    affichage = SDL_SetVideoMode(920, 840, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Worl Of ACU", NULL);

    continu = menujeux("src/menu.bmp",affichage);
    if (continu == 2)
    {
        tab = init_map("src/map2.txt");
        fond = imgfond("src/fond2.bmp", affichage);
    }
    else
    {
        fond = imgfond("src/fond.bmp", affichage);
        tab = init_map("src/map.txt");
    }
    mechant = init_mob(nb_mob,affichage);
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Error init SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    tour = imgfond("src/tour1.png", affichage);
    proj = imgfond("src/proj.bmp",affichage);
    while (continu)
    {
        SDL_FillRect(affichage,NULL,SDL_MapRGB(affichage->format,255,255,255));
        SDL_BlitSurface(fond, NULL, affichage, 0);
        SDL_BlitSurface(tour,NULL,affichage,&postour);
        SDL_BlitSurface(proj, NULL, affichage, &posproj);

        for (j = 0; j < nb_mob && j < (i / 50); j++)
        {
            SDL_BlitSurface(mechant[j], NULL, affichage, &posmechant);
            posmechant = move_ennemy(j, tab);

        }
        SDL_Delay(15);
        posproj = projectil(posproj, posmechant, postour,mechant[0]);

        SDL_Flip(affichage);

        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continu = 0;
            case SDL_MOUSEBUTTONUP:
                postour.x = event.button.x;
                postour.y = event.button.y;
            default : break;
        }
        if ((i / 50) <= nb_mob)
            i++;
    }
    SDL_FreeSurface(proj);
    SDL_FreeSurface(tour);
    for (j = 0; j < nb_mob; j++)
        SDL_FreeSurface(mechant[j]);
    SDL_FreeSurface(fond);
    return (0);
}
