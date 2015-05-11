#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Bateau.h"

Bateau * BateauConstructeur(const unsigned char puissance, const unsigned char vitesse,
                            const unsigned char portee, const unsigned short vieMax, const unsigned short vie,
                            const unsigned char taille, const unsigned char direction,
                            const unsigned char positionX, const unsigned char positionY, Sprite * sprite)
{
    Bateau * bateau;
    bateau = (Bateau *)malloc(sizeof(Bateau));
    assert(bateau != NULL);
    bateau->puissance = puissance;
    bateau->vitesse = vitesse;
    bateau->portee = portee;
    bateau->vieMax = vieMax;
    bateau->vie = vie;
    bateau->taille = taille;
    bateau->direction = direction;
    bateau->positionAvant = PositionConstructeur(positionX,positionY);
    bateau->aspect = sprite;
    return bateau;
}

void BateauDestructeur(Bateau * bateau)
{
    PositionDestructeur(bateau->positionAvant);
    free(bateau);
    bateau = NULL;
}

unsigned char BateauGetPuissance(const Bateau * bateau)
{
    return bateau->puissance;
}

unsigned char BateauGetVitesse(const Bateau * bateau)
{
    return bateau->vitesse;
}

unsigned char BateauGetPortee(const Bateau * bateau)
{
    return bateau->portee;
}

unsigned short BateauGetVie(const Bateau * bateau)
{
    return bateau->vie;
}

unsigned short BateauGetVieMax(const Bateau * bateau)
{
    return bateau->vieMax;
}

unsigned char BateauGetDirection(const Bateau * bateau)
{
    return bateau->direction;
}

unsigned char BateauGetTaille(const Bateau * bateau)
{
    return bateau->taille;
}

Position * BateauGetPosition(const Bateau * bateau)
{
    return bateau->positionAvant;
}

Sprite * BateauGetAspect(const Bateau * bateau)
{
    return bateau->aspect;
}

void BateauSetPuissance(Bateau * bateau, const unsigned char puissance)
{
    bateau->puissance = puissance;
}

void BateauSetVitesse(Bateau * bateau, const unsigned char vitesse)
{
    bateau->vitesse = vitesse;
}

void BateauSetPortee(Bateau * bateau, const unsigned char portee)
{
    bateau->portee = portee;
}

void BateauSetVie(Bateau * bateau, const unsigned short vie)
{
    assert(vie <= BateauGetVieMax(bateau));
    bateau->vie = vie;
}

void BateauSetVieMax(Bateau * bateau, const unsigned short vieMax)
{
    bateau->vieMax = vieMax;
}

void BateauSetDirection(Bateau * bateau, const unsigned char direction)
{
    assert(direction < 8);
    bateau->direction = direction;
}

void BateauSetTaille(Bateau * bateau, const unsigned char taille)
{
    assert(bateau);
    bateau->taille = taille;
}

void BateauSetPosition(Bateau * bateau, const unsigned char positionX, const unsigned char positionY)
{
    assert(bateau->positionAvant != NULL);
    PositionSetX(bateau->positionAvant, positionX);
    PositionSetY(bateau->positionAvant, positionY);
}

void BateauSetAspect(Bateau * bateau, Sprite * sprite)
{
    assert(sprite != NULL);
    bateau->aspect = sprite;
}

Position BateauGetHitBoxInferieur(Bateau * bateau)
{
    Position p;
    unsigned char x = PositionGetX(bateau->positionAvant);
    unsigned char y = PositionGetY(bateau->positionAvant);
    unsigned char largeur = SpriteGetX(bateau->aspect);
    unsigned char longueur = SpriteGetY(bateau->aspect);
    unsigned char decallage = (unsigned char) (largeur)/2;
    switch(bateau->direction)
    {
        case 0:
            p.positionX = x - decallage;
            p.positionY = y;
            break;
        case 1:
            p.positionX = x - longueur + 1;
            p.positionY = y;
            break;
        case 2:
            p.positionX = x - longueur + 1;
            p.positionY = y - decallage;
            break;
        case 3:
            p.positionX = x - longueur + 1;
            p.positionY = y - longueur + 1;
            break;
        case 4:
            p.positionX = x - decallage;
            p.positionY = y - longueur + 1;
            break;
        case 5:
            p.positionX = x;
            p.positionY = y - longueur + 1;
            break;
        case 6:
            p.positionX = x;
            p.positionY = y - decallage;
            break;
        default:
            p.positionX = x;
            p.positionY = y;
            break;
    }
    return p;
}

Position BateauGetHitBoxSuperieur(Bateau * bateau)
{
    Position p;
    unsigned char x = PositionGetX(bateau->positionAvant);
    unsigned char y = PositionGetY(bateau->positionAvant);
    unsigned char taille = SpriteGetY(bateau->aspect);
    unsigned char decallage = (unsigned char) (SpriteGetX(bateau->aspect))/2;
    switch(bateau->direction)
    {
        case 0:
            p.positionX = x + decallage;
            p.positionY = y + taille - 1;
            break;
        case 1:
            p.positionX = x;
            p.positionY = y + taille - 1;
            break;
        case 2:
            p.positionX = x;
            p.positionY = y + decallage;
            break;
        case 3:
            p.positionX = x;
            p.positionY = y;
            break;
        case 4:
            p.positionX = x + decallage;
            p.positionY = y;
            break;
        case 5:
            p.positionX = x + taille - 1;
            p.positionY = y;
            break;
        case 6:
            p.positionX = x + taille - 1;
            p.positionY = y + decallage;
            break;
        default:
            p.positionX = x + taille - 1;
            p.positionY = y + taille - 1;
            break;
    }
    return p;
}

Position BateauGetPositionMilieu(Bateau * bateau)
{
    Position p = BateauGetHitBoxInferieur(bateau);
    unsigned char decallage = SpriteGetY(BateauGetAspect(bateau))/2;

    p.positionX = PositionGetX(BateauGetPosition(bateau));
    p.positionY = PositionGetY(BateauGetPosition(bateau));

    switch(BateauGetDirection(bateau))
    {
        case 0:
            p.positionY += decallage;
            break;
        case 1:
            p.positionX -= decallage;
            p.positionY += decallage;
            break;
        case 2:
            p.positionX -= decallage;
            break;
        case 3:
            p.positionX -= decallage;
            p.positionY -= decallage;
            break;
        case 4:
            p.positionY -= decallage;
            break;
        case 5:
            p.positionX += decallage;
            p.positionY -= decallage;
            break;
        case 6:
            p.positionX += decallage;
            break;
        default:
            p.positionX += decallage;
            p.positionY += decallage;
            break;
    }
    return p;
}

unsigned char BateauTestCollision(Ennemis * ennemis, Bateau * bateau, unsigned char x, unsigned char y)
{
    unsigned char j, xInf, xSup, yInf, ySup;
    Bateau * ennemi;
    Position p;

    for(j = 0; j < EnnemisGetTailleUtilisee(ennemis); ++j)
    {
        ennemi = EnnemisValeurIeme(ennemis, j);
        if(ennemi != bateau) /* Si l'ennemi n'est pas notre bateau */
        {
            p = BateauGetHitBoxInferieur(ennemi);
            xInf = PositionGetX(&p);
            yInf = PositionGetY(&p);
            p = BateauGetHitBoxSuperieur(ennemi);
            xSup = PositionGetX(&p);
            ySup = PositionGetY(&p);
            if(x >= xInf && x <= xSup && y >= yInf && y <= ySup)
                return 1;
        }
    }
    return 0;
}

void BateauAvancer(Bateau * bateau, Ennemis * ennemis, Terrain * terrain)
{
    unsigned char maxX = TerrainGetX(terrain) -2;
    unsigned char maxY = TerrainGetY(terrain) -2;
    unsigned char x = PositionGetX(BateauGetPosition(bateau));
    unsigned char y = PositionGetY(BateauGetPosition(bateau));

    assert(maxX > 0);
    assert(maxY > 0);

    switch(BateauGetDirection(bateau))
    {
        case 1:
            if(y > 1 && x < maxX && TerrainGetCase(terrain, ++x,--y)=='0'
               && BateauTestCollision(ennemis, bateau, x, y) == 0)
                BateauSetPosition(bateau, x, y);
            break;
        case 2:
            if(x < maxX && TerrainGetCase(terrain, ++x,y)=='0'
               && BateauTestCollision(ennemis, bateau, x, y) == 0)
                BateauSetPosition(bateau, x, y);
            break;
        case 3:
            if(y < maxY && x < maxX && TerrainGetCase(terrain, ++x,++y)=='0'
               && BateauTestCollision(ennemis, bateau, x, y) == 0)
                BateauSetPosition(bateau, x, y);
            break;
        case 4:
            if(y < maxY && TerrainGetCase(terrain, x,++y)=='0'
               && BateauTestCollision(ennemis, bateau, x, y) == 0)
                BateauSetPosition(bateau, x, y);
            break;
        case 5:
            if(y < maxY && x > 1 && TerrainGetCase(terrain, --x,++y)=='0'
               && BateauTestCollision(ennemis, bateau, x, y) == 0)
                BateauSetPosition(bateau, x, y);
            break;
        case 6:
            if(x > 1 && TerrainGetCase(terrain, --x,y)=='0'
               && BateauTestCollision(ennemis, bateau, x, y) == 0)
                BateauSetPosition(bateau, x, y);
            break;
        case 7:
            if(x > 1 && y > 1 && TerrainGetCase(terrain, --x,--y)=='0'
               && BateauTestCollision(ennemis, bateau, x, y) == 0)
                BateauSetPosition(bateau, x, y);
            break;
        default:
            if(y > 1 && TerrainGetCase(terrain, x,--y)=='0'
               && BateauTestCollision(ennemis, bateau, x, y) == 0)
                BateauSetPosition(bateau, x, y);
    }
}

void BateauReculer(Bateau * bateau)
{
    unsigned char x = PositionGetX(BateauGetPosition(bateau));
    unsigned char y = PositionGetY(BateauGetPosition(bateau));
    unsigned char decalage = SpriteGetY(bateau->aspect) - 1;

    switch(BateauGetDirection(bateau))
    {
        case 1:
            BateauSetPosition(bateau, x - decalage, y + decalage);
            break;
        case 2:
            BateauSetPosition(bateau, x - decalage, y);
            break;
        case 3:
            BateauSetPosition(bateau, x - decalage, y - decalage);
            break;
        case 4:
            BateauSetPosition(bateau, x, y - decalage);
            break;
        case 5:
            BateauSetPosition(bateau, x + decalage, y - decalage);
            break;
        case 6:
            BateauSetPosition(bateau, x + decalage, y);
            break;
        case 7:
            BateauSetPosition(bateau, x + decalage, y + decalage);
            break;
        default:
            BateauSetPosition(bateau, x, y + decalage);
    }
    BateauSetDirection(bateau, (BateauGetDirection(bateau)+4)%8);
}

unsigned char BateauTournerDroite(Bateau * bateau, Ennemis * ennemis, Terrain * terrain)
{
    unsigned char maxX = TerrainGetX(terrain);
    unsigned char maxY = TerrainGetY(terrain);
    unsigned char x = PositionGetX(BateauGetPosition(bateau));
    unsigned char y = PositionGetY(BateauGetPosition(bateau));

    unsigned char pivot = (char)SpriteGetY(bateau->aspect)/2;

    assert(maxX > 0);
    assert(maxY > 0);

    switch(BateauGetDirection(bateau))
    {
        case 1:
            if( TerrainGetCase(terrain, x, y + pivot) == '0'
               && (BateauTestCollision(ennemis, bateau, x, y + pivot) == 0))
            {
                BateauSetPosition(bateau, x, y + pivot);
                BateauSetDirection(bateau, 2);
                return 1;
            }
            break;
        case 2:
            if((y + pivot <= maxY) && (y - pivot >= 0) && TerrainGetCase(terrain, x, y + pivot)=='0'
               && (BateauTestCollision(ennemis, bateau, x, y + pivot) == 0))
            {
                BateauSetPosition(bateau, x, y + pivot);
                BateauSetDirection(bateau, 3);
                return 1;
            }
            break;
        case 3:
            if( TerrainGetCase(terrain, x - pivot, y) == '0'
               && (BateauTestCollision(ennemis, bateau, x - pivot, y) == 0))
            {
                BateauSetPosition(bateau, x - pivot, y);
                BateauSetDirection(bateau, 4);
                return 1;
            }
            break;
        case 4:
            if((x + pivot <= maxX) && (x - pivot >= 0) && TerrainGetCase(terrain, x - pivot, y)=='0'
               && (BateauTestCollision(ennemis, bateau, x - pivot, y) == 0))
            {
                BateauSetPosition(bateau, x - pivot, y);
                BateauSetDirection(bateau, 5);
                return 1;
            }
            break;
        case 5:
            if( TerrainGetCase(terrain, x, y - pivot) == '0'
               && (BateauTestCollision(ennemis, bateau, x, y - pivot) == 0))
            {
                BateauSetPosition(bateau, x, y - pivot);
                BateauSetDirection(bateau, 6);
                return 1;
            }
            break;
        case 6:
            if((y + pivot <= maxY) && (y - pivot >= 0) && TerrainGetCase(terrain, x, y - pivot)=='0'
               && (BateauTestCollision(ennemis, bateau, x, y - pivot) == 0))
            {
                BateauSetPosition(bateau, x, y - pivot);
                BateauSetDirection(bateau, 7);
                return 1;
            }
            break;
        case 7:
            if( TerrainGetCase(terrain, x + pivot, y) == '0'
               && (BateauTestCollision(ennemis, bateau, x + pivot, y) == 0))
            {
                BateauSetPosition(bateau, x + pivot, y);
                BateauSetDirection(bateau, 0);
                return 1;
            }

            break;
        default:
            if((x + pivot <= maxX) && (x - pivot >= 0) && TerrainGetCase(terrain, x + pivot, y)=='0'
               && (BateauTestCollision(ennemis, bateau, x + pivot, y) == 0))
            {
                BateauSetPosition(bateau, x + pivot, y);
                BateauSetDirection(bateau, 1);
                return 1;
            }
    }
    return 0;
}

unsigned char BateauTournerGauche(Bateau * bateau, Ennemis * ennemis, Terrain * terrain)
{
    unsigned char maxX = TerrainGetX(terrain);
    unsigned char maxY = TerrainGetY(terrain);
    unsigned char x = PositionGetX(BateauGetPosition(bateau));
    unsigned char y = PositionGetY(BateauGetPosition(bateau));

    unsigned char pivot = (char)SpriteGetY(bateau->aspect)/2;

    assert(maxX > 0);
    assert(maxY > 0);

    switch(BateauGetDirection(bateau))
    {
        case 1:
            if(TerrainGetCase(terrain, x - pivot, y) == '0'
               && (BateauTestCollision(ennemis, bateau, x - pivot, y) == 0))
            {
                BateauSetPosition(bateau, x - pivot, y);
                BateauSetDirection(bateau, 0);
                return 1;
            }
            break;
        case 2:
            if((y + pivot <= maxY) && (y - pivot >= 0) && TerrainGetCase(terrain, x, y - pivot) == '0'
               && (BateauTestCollision(ennemis, bateau, x, y - pivot) == 0))
            {
                BateauSetPosition(bateau, x, y - pivot);
                BateauSetDirection(bateau, 1);
                return 1;
            }
            break;
        case 3:
            if(TerrainGetCase(terrain, x, y - pivot) == '0'
               && (BateauTestCollision(ennemis, bateau, x, y - pivot) == 0))
            {
                BateauSetPosition(bateau, x, y - pivot);
                BateauSetDirection(bateau, 2);
                return 1;
            }
            break;
        case 4:
            if((x + pivot <= maxX) && (x - pivot >= 0) && TerrainGetCase(terrain, x + pivot, y) == '0'
               && (BateauTestCollision(ennemis, bateau, x + pivot, y) == 0))
            {
                BateauSetPosition(bateau, x + pivot, y);
                BateauSetDirection(bateau, 3);
                return 1;
            }
            break;
        case 5:
            if(TerrainGetCase(terrain, x + pivot, y) == '0'
               && (BateauTestCollision(ennemis, bateau, x + pivot, y) == 0))
            {
                BateauSetPosition(bateau, x + pivot, y);
                BateauSetDirection(bateau, 4);
                return 1;
            }
            break;
        case 6:
            if((y + pivot <= maxY) && (y - pivot >= 0) && TerrainGetCase(terrain, x, y + pivot)=='0'
               && (BateauTestCollision(ennemis, bateau, x, y + pivot) == 0))
            {
                BateauSetPosition(bateau, x, y + pivot);
                BateauSetDirection(bateau, 5);
                return 1;
            }
            break;
        case 7:
            if( TerrainGetCase(terrain, x, y + pivot) == '0'
               && (BateauTestCollision(ennemis, bateau, x, y + pivot) == 0))
            {
                BateauSetPosition(bateau, x, y + pivot);
                BateauSetDirection(bateau, 6);
                return 1;
            }
            break;
        default:
            if((x + pivot <= maxX) && (x - pivot >= 0) && TerrainGetCase(terrain, x - pivot, y)=='0'
               && (BateauTestCollision(ennemis, bateau, x - pivot, y) == 0))
            {
                BateauSetPosition(bateau, x - pivot, y);
                BateauSetDirection(bateau, 7);
                return 1;
            }
            break;
    }
    return 0;
}

void BateauTestRegression()
{
    printf("\n-- Bateau Test de regression --\n\n");

    printf("- Constructeur -\n");
    Sprite * texture = SpriteConstructeur(10,10,0);
    Bateau * mistral = BateauConstructeur(10, 10, 10, 500, 500, 7, 1, 25, 25, texture);
    if(mistral != NULL)
        printf("->Construction du bateau : OK\n");

    printf("- Accesseurs et mutateurs -\n");
    BateauSetDirection(mistral, BateauGetDirection(mistral) + 1);
    if(BateauGetDirection(mistral) == 2)
        printf("->Accesseurs et mutateurs de direction : OK\n");
    BateauSetPuissance(mistral, BateauGetVitesse(mistral) + 1);
    if(BateauGetPuissance(mistral) == 11)
        printf("->Accesseurs et mutateurs de puissance : OK\n");
    BateauSetVitesse(mistral, BateauGetPortee(mistral) + 2);
    if(BateauGetVitesse(mistral) == 12)
        printf("->Accesseurs et mutateurs de vitesse : OK\n");
    BateauSetPortee(mistral, BateauGetTaille(mistral) + 2);
    if(BateauGetPortee(mistral) == 9)
        printf("->Accesseurs et mutateurs de portee : OK\n");
    BateauSetVieMax(mistral, BateauGetVie(mistral) + 500);
    if(BateauGetVieMax(mistral) == 1000)
        printf("->Accesseurs et mutateurs de vieMax : OK\n");
    BateauSetVie(mistral, BateauGetVieMax(mistral) - 250);
    if(BateauGetVie(mistral) == 750)
        printf("->Accesseurs et mutateurs de vie : OK\n");
    BateauSetTaille(mistral, BateauGetTaille(mistral) + 4);
    if(BateauGetTaille(mistral) == 11)
        printf("->Accesseurs et mutateurs de taille : OK\n");
    BateauSetPosition(mistral, 27, 30);
    if(PositionGetX(BateauGetPosition(mistral)) == 27)
        if(PositionGetY(BateauGetPosition(mistral)) == 30)
            printf("->Accesseurs et mutateurs de position : OK\n");

    printf("- Destructeur de bateau -\n");
    BateauDestructeur(mistral);
    SpriteDestructeur(texture);
    printf("->Destruction confirmee : OK\n");

    printf("-- Bateau Fin du test, Merci et a bientot --\n\n");
}
