#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Sprite.h"

Sprite * SpriteConstructeur (const unsigned char dimX, const unsigned char dimY, unsigned char texture)
{
    Sprite * sprite;
    sprite = (Sprite*)malloc(sizeof(Sprite));
    sprite->dimX = dimX;
    sprite->dimY = dimY;
    sprite->texture = texture;
    return sprite;
}

void SpriteDestructeur(Sprite * sprite)
{
    assert(sprite);
    free(sprite);
}

unsigned char SpriteGetX(const Sprite * sprite)
{
    return sprite->dimX;
}

unsigned char SpriteGetY(const Sprite * sprite)
{
    return sprite->dimY;
}

unsigned char SpriteGetTexture(const Sprite * sprite)
{
    return sprite->texture;
}

void SpriteSetDimX(Sprite * sprite , const unsigned char dimX)
{
    sprite->dimX = dimX;
}

void SpriteSetDimY(Sprite * sprite , const unsigned char dimY)
{
    sprite->dimY = dimY;
}

void SpriteSetTexture(Sprite * sprite , unsigned char texture)
{
    sprite->texture = texture ;
}

void SpriteTestRegression()
{
    Sprite * sprite;
    unsigned char dimX , dimY , x , y, texture, test ;
    dimX = 5;
    dimY = 7;
    texture = 1;
    sprite = SpriteConstructeur(dimX, dimY,texture);
    assert(sprite !=NULL);
    printf("Sprite Initialise \n");
    x=SpriteGetX(sprite);
    printf("dim X : %d \n",x);
    y=SpriteGetY(sprite);
    printf("dim Y : %d \n",y);
    test=SpriteGetTexture(sprite);
    printf("texture : %d \n",test);
    texture = 2;
    SpriteSetDimX(sprite,dimY);
    SpriteSetDimY(sprite,dimX);
    SpriteSetTexture(sprite,texture);
    x=SpriteGetX(sprite);
    printf("dim X Change : %d \n",x);
    y=SpriteGetY(sprite);
    printf("dim Y Change : %d \n",y);
    test=SpriteGetTexture(sprite);
    printf("texture Change : %d \n",test);
    SpriteDestructeur(sprite);
    printf("Sprite Detruit \n");
}
