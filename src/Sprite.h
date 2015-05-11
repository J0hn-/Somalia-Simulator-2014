#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

/**
    Voici le module Sprite, qui permet la gestion des Sprites du Jeu
    @author Cyril C.
    @version 0.1

    @struct Sprite
*/

typedef struct
{
    unsigned char dimX;    /**<! \brief Taille horizontale du Sprite, comprise entre 0 et 255 */
    unsigned char dimY;    /**<! \brief Taille verticale du Sprite, comprise entre 0 et 255 */
    unsigned char texture; /**<! \brief Numero de l'image de la texture */
} Sprite;

/**
    @brief Constructeur pour Sprite
    @param [in] dimX Entier
    @param [in] dimY Entier
    @param [in] texture Char *
    @return Pointeur sur Sprite
*/

Sprite * SpriteConstructeur (const unsigned char dimX ,const unsigned char dimY , unsigned char texture);

/**
    @brief Destructeur pour Sprite
    @param [in-out] sprite Structure Sprite
*/

void SpriteDestructeur (Sprite * sprite);

/**
    @brief Accesseur pour dimX
    @param [in] sprite Structure Sprite
    @return dimX, Entier compris entre 0 et 255
*/

unsigned char SpriteGetX(const Sprite * sprite);

/**
    @brief Accesseur pour dimY
    @param [in] sprite Structure Sprite
    @return dimY, Entier compris entre 0 et 255
*/

unsigned char SpriteGetY(const Sprite * sprite);

/**
    @brief Accesseur pour texture
    @param [in] sprite Structure Sprite
    @return texture, Chaîne de caractères
*/

unsigned char SpriteGetTexture(const Sprite * sprite);

/**
    @brief Mutateur pour texture
    @param [in-out] sprite Structure Sprite
    @param [in] texture Chaîne de caractères
*/

void SpriteSetTexture(Sprite * sprite , unsigned char texture);

/**
    @brief Mutateur pour dimX
    @param [in-out] sprite Structure Sprite
    @param [in] dimX Entier
*/

void SpriteSetDimX(Sprite * sprite , const unsigned char dimX);

/**
    @brief Mutateur pour dimY
    @param [in-out] sprite Structure Sprite
    @param [in] dimY Entier
*/

void SpriteSetDimY(Sprite * sprite , const unsigned char dimY);

/**
    @brief Test de Regression de Sprite
*/

void SpriteTestRegression();

#endif





