#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Tir.h"
#include "Position.h"
#include "Terrain.h"

Tir * TirConstructeur(const unsigned char puissance , const unsigned char portee , const unsigned char direction , const unsigned char x, const unsigned char y, Sprite * aspect)
{
    Tir * tir = (Tir*)malloc(sizeof(Tir));
    if(tir != NULL)
    {
        assert(direction <= 7);
        tir->aspect = aspect;
        tir->direction = direction;
        tir->portee = portee;
        tir->puissance = puissance;
        tir->positionTir = PositionConstructeur(x, y);
        if(tir->positionTir == NULL)
        {
            free(tir);
            tir = NULL;
        }
    }
    return tir;
}

void TirDestructeur(Tir * tir)
{
    tir->aspect = NULL;
    tir->direction = 0;
    tir->portee = 0;
    PositionDestructeur(tir->positionTir);
    tir->puissance = 0;
    free(tir);
}

Sprite * TirGetAspect(const Tir * tir)
{
    return tir->aspect;
}

unsigned char TirGetDirection (const Tir * tir)
{
    return tir->direction;
}

unsigned char TirGetPuissance (const Tir * tir)
{
    return tir->puissance;
}

unsigned char TirGetPortee (const Tir * tir)
{
    return tir->portee;
}

Position * TirGetPosition (const Tir * tir)
{
    return tir->positionTir;
}

void TirSetPortee(Tir * tir, const unsigned char portee)
{
    assert(tir);
    tir->portee = portee;
}

void TirTestRegression()
{
    unsigned char direction , puissance , portee , posX , posY , SprX, SprY , posX2 , posY2;
    Position * position;
    Sprite * aspect;
    Tir * tir;
    unsigned char texture = 1;
    direction = 5;
    puissance = 100;
    portee = 20;
    posX=25;
    posY=25;
    SprX=55;
    SprY=25;
    aspect = SpriteConstructeur (SprX , SprY, texture);
    tir = TirConstructeur(puissance , portee , direction , posX, posY, aspect);
    position=TirGetPosition(tir);
    posX2=PositionGetX(position);
    posY2=PositionGetY(position);
    portee=TirGetPortee(tir);
    printf("%d , %d , %d \n", posX2 , posY2, portee);
    TirDestructeur(tir);
}
