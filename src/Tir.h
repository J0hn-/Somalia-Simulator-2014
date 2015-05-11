#ifndef TIR_H_INCLUDED
#define TIR_H_INCLUDED

#include "Position.h"
#include "Sprite.h"
#include "Terrain.h"

/**
    Voici le module Tir, qui permet la création des tirs
    @author Cyril C.
    @version 0.1

    @struct Tir
*/

typedef struct
{
    unsigned char puissance;  /*!< \brief Puissance du Tir (entre 0 et 255)*/
    unsigned char portee;  /*!< \brief Portee du Tir (entre 0 et 25) */
    unsigned char direction;  /*!< \brief Direction du tir : entre 0 et 7 dans le sens horraire*/
    Position * positionTir;  /*!< \brief Coordonnees du tir */
    Sprite * aspect; /*!< \brief Aspect du Tir */
} Tir;

/**
    @brief Constructeur pour Tir
    @param [in] puissance Entier compris entre 0 et 255
    @param [in] portee Entier compris entre 0 et 25
    @param [in] direction Entier compris entre 0 et 7
    @param [in] x Position en X
    @param [in] y Position en Y
    @return tir Structure Tir
*/

Tir * TirConstructeur(const unsigned char puissance , const unsigned char portee , const unsigned char direction , const unsigned char x, const unsigned char y, Sprite * aspect);

/**
    @brief Destructeur pour Tir
    @param [in-out] tir Structure Tir
*/

void TirDestructeur (Tir * tir);

/**
    @brief Accesseur pour aspect
    @param [in] tir Structure Tir
    @return aspect Structure Sprite
*/

Sprite * TirGetAspect(const Tir * tir);

/**
    @brief Accesseur pour direction
    @param [in] tir Structure Tir
    @return direction Entier entre 0 et 7
*/

unsigned char TirGetDirection (const Tir * tir);

/**
    @brief Accesseur pour puissance
    @param [in] tir Structure Tir
    @return puissance Entier entre 0 et 255
*/

unsigned char TirGetPuissance (const Tir * tir);

/**
    @brief Accesseur pour portee
    @param [in] tir Structure Tir
    @return portee Entier entre 0 et 25
*/

unsigned char TirGetPortee (const Tir * tir);

/**
    @brief Accesseur pour position
    @param [in] tir Structure Tir
    @return position Structure Position
*/

Position * TirGetPosition (const Tir * tir);

/**
    @brief Mutateur pour portee
    @param [in,out] tir Structure Tir
    @param [in] portee Entier entre 0 et 25
    @return Pas de retour
*/
void TirSetPortee (Tir * tir, const unsigned char portee);

/**
    @brief Test de Regression de Tir
*/

void TirTestRegression();
 #endif



