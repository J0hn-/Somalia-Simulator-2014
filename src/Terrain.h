#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

/**
    Module Terrain, qui met en place le Terrain: le construit le detruit et teste les fonctions.
    @brief Module du Terrain
    @author QDB
    @author Jonathan
    @version 0.2
    @struct Terrain
*/

typedef struct
{
    unsigned int tailleX; /*!< Taille en X de la carte. */
    unsigned int tailleY; /*!< Taille en Y de la carte. */
    int * carte; /*!< Tableau de la carte.*/
}   Terrain;

/**

    @brief Cree le Terrain sur lequel on va jouer.
    @param [in] TailleX Entier
    @param [in] TailleY Entier
    @return Renvoie un terrain construit.
*/
Terrain * TerrainConstructeur(const char * nomFichier);

/**

    @brief  Detruit le terrain.
    @param [in, out] pCarte pointeur sur Terrain.
    @return Pas de retour

*/
void TerrainDestructeur(Terrain * terrain);

/**
    @brief Accesseur pour tailleX
    @param [in] terrain Structure Terrain
    @return tailleX, Entier compris entre 0 et 255
*/
unsigned char TerrainGetX(Terrain * terrain);

/**
    @brief Accesseur pour tailleY
    @param [in] terrain Structure Terrain
    @return tailleY, Entier compris entre 0 et 255
*/
unsigned char TerrainGetY(Terrain * terrain);

/**
    @brief Accesseur pour une case du Terrain
    @param [in] terrain Structure Terrain
    @param [in] x Coordonnee en x
    @param [in] y Coordonnee en y
    @return Caractere qui correspond à la case du terrain
*/
int TerrainGetCase(Terrain * terrain, unsigned char x, unsigned char y);

/**

    @brief Teste les fonctions contenues dans Terrain.h
    @param [in] Pas de parametres
    @return Pas de retour

*/
void TerrainTestRegression();

#endif
