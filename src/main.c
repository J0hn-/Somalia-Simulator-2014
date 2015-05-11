/*#include "Position.h"
#include "Sprite.h"
#include "Tir.h"
#include "Terrain.h"
#include "Manche.h"
#include "Jeu.h"
#include "testnCurses.h"

int main(void)
{
    PositionTestRegression();
    SpriteTestRegression();
    TirTestRegression();
    TerrainTestRegression();
    BateauTestRegression();
    MancheTestRegression();
    JoueurTestRegression();

    JeuTestRegression();

    printf("#SWAG #YOLO\n");

    Jeu * jeu = JeuConstructeur();
    //MusiqueMusiqueChoix(JeuGetMusique(jeu), 5);
    nCursesBoucle(jeu);
    JeuDestructeur(jeu);
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#define _SDL_main_h
#include "SDLjeu.h"

int main2 ()
{
    PositionTestRegression();
    SpriteTestRegression();
    TirTestRegression();
    TerrainTestRegression();
    BateauTestRegression();
    MancheTestRegression();
    JoueurTestRegression();

    JeuTestRegression();

    return 0;
}
