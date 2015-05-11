#include <stdlib.h>
#include <stdio.h>
#define _SDL_main_h
#include <SDL/SDL.h>
#include "Jeu.h"
#include "Musique.h"

int main9(int argc, char *argv[])
{
    Jeu * jeu = JeuConstructeur();

    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *joueur = NULL, *imageDeJeu = NULL;
    SDL_Surface *menuFond = NULL;
    SDL_Rect positionFond, positionJoueur, positionMenu;

    positionFond.x = 0;
    positionFond.y = 0;
    positionJoueur.x = 500;
    positionJoueur.y = 260;
    positionMenu.x = 0;
    positionMenu.y = 600;

    SDL_Init(SDL_INIT_VIDEO);



    ecran = SDL_SetVideoMode(1200, 675, 32, SDL_HWSURFACE);
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Somalia Simulator 2014", NULL);

    imageDeJeu = SDL_LoadBMP("data/SS14 Dark.bmp");
    SDL_BlitSurface(imageDeJeu, NULL, ecran, &positionFond);

    SDL_Flip(ecran);

    MusiqueMusiqueChoix(JeuGetMusique(jeu), 3);

    pause();

    MusiqueStop(JeuGetMusique(jeu));

    MusiqueMusiqueChoix(JeuGetMusique(jeu), 1);

    imageDeFond = SDL_LoadBMP("data/mapv1.bmp");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

    menuFond = SDL_LoadBMP("data/bandeau.bmp");
    SDL_BlitSurface(menuFond, NULL, ecran, &positionMenu);

    joueur = SDL_LoadBMP("data/joueur/sprite1.bmp");
    SDL_SetColorKey(joueur, SDL_SRCCOLORKEY, SDL_MapRGB(joueur->format, 195, 195, 195));
    SDL_BlitSurface(joueur, NULL, ecran, &positionJoueur);

    SDL_Flip(ecran);

    pause();

    SDL_FreeSurface(menuFond);
    SDL_FreeSurface(imageDeJeu);
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(joueur);
    SDL_Quit();

    JeuDestructeur(jeu);

    return EXIT_SUCCESS;
}

void pause()
{
    unsigned char continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            case SDL_KEYDOWN:
                continuer = 0;
        }
    }
}
