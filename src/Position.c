#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Position.h"

Position * PositionConstructeur(const unsigned char positionX,const unsigned char positionY)
{
    Position * position;
    position = (Position*)malloc(sizeof(Position));
    if(position != NULL)
    {
        position->positionX = positionX;
        position->positionY = positionY;
    }
    return position;
}

void PositionDestructeur (Position * position)
{
    position->positionX=0;
    position->positionY=0;
    free(position);
}

unsigned char PositionGetX(const Position * position)
{
    assert(position);
    return position->positionX;
}

unsigned char PositionGetY(const Position * position)
{
    return position->positionY;
}

void PositionSetX(Position * position, const unsigned char x)
{
    position->positionX = x;
}

void PositionSetY(Position * position, const unsigned char y)
{
    position->positionY = y;
}

Position PositionDirectionSuivante(const Position * position, const unsigned char direction)
{
    assert(direction < 8);
    unsigned char x = PositionGetX(position);
    unsigned char y = PositionGetY(position);
    switch(direction)
    {
        case 1:
            --x;
            ++y;
            break;
        case 2:
            --x;
            break;
        case 3:
            --x;
            --y;
            break;
        case 4:
            --y;
            break;
        case 5:
            ++x;
            --y;
            break;
        case 6:
            ++x;
            break;
        case 7:
            ++x;
            ++y;
            break;
        default:
            ++y;
    }
    Position p = {x,y};
    return p;
}

void PositionTestRegression()
{
    unsigned char a = 123;
    unsigned char b = 150;

    Position * p = PositionConstructeur(a,a);

    printf("\n-- Position Test de regression --\n\n");
    printf("-> Creation : OK\n");
    if((PositionGetX(p) == PositionGetY(p)) && (PositionGetX(p) == 123))
        printf("->Accesseurs : OK\n");

    PositionSetX(p, b);
    PositionSetY(p, b);

    if((PositionGetX(p) == PositionGetY(p)) && (PositionGetX(p) == 150))
        printf("->Mutateurs : OK\n");

    PositionDestructeur(p);
    printf("->Destructeurs : OK\n");

    printf("\n-- Fin du test, Merci et a bientot --\n\n");
}
