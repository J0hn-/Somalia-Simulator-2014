#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Terrain.h"
#include "Position.h"

Terrain * TerrainConstructeur(const char * nomFichier)
{
    int x,y,X,Y;

    FILE* fichier = fopen(nomFichier, "r");

    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s", nomFichier);
        return NULL;
    }

    Terrain * terrain = (Terrain*)malloc(sizeof(Terrain));
    assert(terrain != NULL);

    fscanf(fichier, "%d %d\n", &X, &Y);
    terrain->tailleX = X;
    terrain->tailleY = Y;
    terrain->carte = (int *)malloc(sizeof(int)*X*Y);
    for(y=0;y<Y;++y)
    {
        for(x=0;x<X;++x)
        {
            terrain->carte[x+X*y] = fgetc(fichier);
        }
    }

    fclose(fichier);

    return terrain;
}

void TerrainDestructeur(Terrain * terrain)
{
    free(terrain->carte);
    terrain->tailleX = 0;
    terrain->tailleY = 0;
    terrain->carte = NULL;
    free(terrain);
}

unsigned char TerrainGetX(Terrain * terrain)
{
    return terrain->tailleX;
}

unsigned char TerrainGetY(Terrain * terrain)
{
    return terrain->tailleY;
}

int TerrainGetCase(Terrain * terrain, unsigned char x, unsigned char y)
{
    assert(x <= terrain->tailleX);
    assert(y <= terrain->tailleY);
    assert(terrain->carte != NULL);
    return terrain->carte[x+(terrain->tailleX)*y];
}

void TerrainTestRegression()
{
    Terrain * yolo;
    int test;

    yolo = TerrainConstructeur("data/map.txt");

    printf("Dimension x: %d, Dimension y: %d\n", TerrainGetX(yolo), TerrainGetY(yolo));

    test=TerrainGetCase(yolo,53,9);
    printf(" %d \n",test);
    printf("Accesseurs de case operationels\n");

    TerrainDestructeur(yolo);

    printf("Le terrain Yolo a bien ete supprime");
}
