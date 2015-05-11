#ifndef BATEAU_H_INCLUDED
#define BATEAU_H_INCLUDED

#include "Terrain.h"
#include "Position.h"
#include "Sprite.h"
#include "TableauDynamiqueEnnemi.h"

/**
    @brief Voici le module Bateau, qui permet la gestion des bateaux
    @author Jonathan P.
    @version 0.1

    @struct Bateau
*/
typedef struct s_bateau
{
    unsigned char puissance;  /*!< \brief Puissance du bateau (entre 0 et 255)*/
    unsigned char vitesse;  /*!< \brief Vitesse du bateau (entre 0 et 255) */
    unsigned char portee;  /*!< \brief Portee du bateau (entre 0 et 25) */
    unsigned short vieMax;  /*!< \brief Vie Maximum du bateau */
    unsigned short vie;  /*!< \brief Vie du bateau à un instant donné, Vie <= VieMax */
    unsigned char taille;  /*!< \brief Taille/niveau du bateau nombre entre 0 et x */
    unsigned char direction;  /*!< \brief Direction du bateau : entre 0 et 7 dans le sens horraire*/
    Position * positionAvant;  /*!< \brief Coordonnees de l'avant du bateau */
    Sprite * aspect; /*!< \brief Pointeur sur un Sprite, Aspect du bateau */
} Bateau;

/**
    @brief Constructeur pour Bateau
    @param [in] puissance Entier compris entre 0 et 255
    @param [in] vitesse Entier compris entre 0 et 255
    @param [in] portee Entier compris entre 0 et 255
    @param [in] vie Entier compris entre 0 et VieMax
    @param [in] vieMax Entier compris supérieur à 0
    @param [in] direction Entier compris entre 0 et 7
    @param [in] taille Entier impair compris entre 3 et 17
    @param [in] position Pointeur sur structure Position
    @param [in] sprite Pointeur sur Sprite
    @return Bateau *  Pointeur sur structure Bateau initalisee
*/
Bateau * BateauConstructeur(const unsigned char puissance, const unsigned char vitesse,
                            const unsigned char portee, const unsigned short vieMax, const unsigned short vie,
                            const unsigned char taille, const unsigned char direction, const unsigned char positionX,
                            const unsigned char positionY, Sprite * sprite);

/**
    @brief Destructeur pour Bateau
    @param [in,out] bateau Structure Bateau
*/
void BateauDestructeur(Bateau * bateau);

/**
    @brief Test de regression
    @return Pas de retour
*/
void BateauTestRegression();

/**
    @brief Accesseur pour Puissance
    @param [in,out] bateau Structure Bateau
    @return Puissance, Entier compris entre 0 et 255
*/
unsigned char BateauGetPuissance(const Bateau * bateau);

/**
    @brief Accesseur pour Vitesse
    @param [in,out] bateau Structure Bateau
    @return Vitesse, Entier compris entre 0 et 255
*/
unsigned char BateauGetVitesse(const Bateau * bateau);

/**
    @brief Accesseur pour Portee
    @param [in,out] bateau Structure Bateau
    @return Portee, Entier compris entre 0 et 255
*/
unsigned char BateauGetPortee(const Bateau * bateau);

/**
    @brief Accesseur pour Vie
    @param [in,out] bateau Structure Bateau
    @return Vie, Entier inférieur ou égal à VieMax
*/
unsigned short BateauGetVie(const Bateau * bateau);

/**
    @brief Accesseur pour VieMax
    @param [in,out] bateau Structure Bateau
    @return VieMax, Vie maximum du bateau
*/
unsigned short BateauGetVieMax(const Bateau * bateau);

/**
    @brief Accesseur pour Direction
    @param [in,out] bateau Structure Bateau
    @return Direction, Entier compris entre 0 et 7
*/
unsigned char BateauGetDirection(const Bateau * bateau);

/**
    @brief Accesseur pour Taille
    @param [in,out] bateau Structure Bateau
    @return Taille, Entier impair compris entre 3 et 17
*/
unsigned char BateauGetTaille(const Bateau * bateau);

/**
    @brief Accesseur pour Position
    @param [in,out] bateau Structure Bateau
    @return Position, Position de l'avant du bateau
*/
Position * BateauGetPosition(const Bateau * bateau);

/**
    @brief Accesseur pour Position
    @param [in,out] bateau Structure Bateau
    @return Aspect, Sprite du bateau
*/
Sprite * BateauGetAspect(const Bateau * bateau);

/**
    @brief Fonction qui retourne la position de la hit box inférieur
    @param [in] bateau Structure Bateau
    @return Position, position de la hit box inférieur du bateau
*/
Position BateauGetHitBoxInferieur(Bateau * bateau);

/**
    @brief Fonction qui retourne la position de la hit box suprieur
    @param [in] bateau Structure Bateau
    @return Position, position de la hit box superieur du bateau
*/
Position BateauGetHitBoxSuperieur(Bateau * bateau);

/**
    @brief Fonction qui retourne la position du milieu du bateau (pratique)
    @param [in] bateau Structure Bateau
    @return Position, position du milieu du bateau
*/
Position BateauGetPositionMilieu(Bateau * bateau);

/**
    @brief Fonction qui retourne test la collision de la position (x,y)
    @param [in] ennemis Tableau dynamique d'ennemis
    @param [in] bateau Structure Bateau
    @param [in] x Position en x
    @param [in] y Position en y
    @return 1 si collision avec un ennemi, 0 sinon
*/
unsigned char BateauTestCollision(Ennemis * ennemis, Bateau * bateau, unsigned char x, unsigned char y);

/**
    @brief Mutateur pour Puissance
    @param [in,out] bateau Structure bateau
    @param [in] puissance Entier compris entre 0 et 255
    @return Pas de retour
*/
void BateauSetPuissance(Bateau * bateau, const unsigned char puissance);

/**
    @brief Mutateur pour Vitesse
    @param [in,out] bateau Structure bateau
    @param [in] vitesse Entier compris entre 0 et 255
    @return Pas de retour
*/
void BateauSetVitesse(Bateau * bateau, const unsigned char vitesse);

/**
    @brief Mutateur pour Portee
    @param [in,out] bateau Structure bateau
    @param [in] portee Entier compris entre 0 et 255
    @return Pas de retour
*/
void BateauSetPortee(Bateau * bateau, const unsigned char portee);

/**
    @brief Mutateur pour Vie
    @param [in,out] bateau Structure bateau
    @param [in] vie Entier compris entre 0 et vieMax
    @return Pas de retour
*/
void BateauSetVie(Bateau * bateau, const unsigned short vie);

/**
    @brief Mutateur pour VieMax
    @param [in,out] bateau Structure bateau
    @param [in] vieMax Entier supérieur à 0
    @return Pas de retour
*/
void BateauSetVieMax(Bateau * bateau, const unsigned short vieMax);

/**
    @brief Mutateur pour Direction
    @param [in,out] bateau Structure bateau
    @param [in] direction Entier compris entre 0 et 7
    @return Pas de retour
*/
void BateauSetDirection(Bateau * bateau, const unsigned char direction);

/**
    @brief Mutateur pour Taille
    @param [in,out] bateau Structure bateau
    @param [in] taille Entier impair compris entre 3 et 17
    @return Pas de retour
*/
void BateauSetTaille(Bateau * bateau, const unsigned char taille);

/**
    @brief Mutateur pour Position
    @param [in,out] bateau Structure bateau
    @param [in] positionX Coordonnées en X
    @param [in] positionY Coordonnées en Y
    @return Pas de retour
*/
void BateauSetPosition(Bateau * bateau, const unsigned char positionX, const unsigned char positionY);

/**
    @brief Mutateur pour Aspect
    @param [in,out] bateau Structure bateau
    @param [in] sprite Pointeur sur un Sprite
    @return Pas de retour
*/
void BateauSetAspect(Bateau * bateau, Sprite * sprite);

/**
    @brief Fonction pour avancer le bateau d'une case
    @param [in,out] bateau Pointeur sur bateau
    @param [in] ennemis Pointeur sur un Tableau dynamique d'ennemis
    @param [in] terrain Pointeur sur le terrain
    @return Pas de retour
*/
void BateauAvancer(Bateau * bateau, Ennemis * ennemis, Terrain * terrain);

/**
    @brief Fonction pour inverser la position du bateau
    @param [in,out] bateau Pointeur sur bateau
    @return Pas de retour
*/
void BateauReculer(Bateau * bateau);

/**
    @brief Fonction pour tourner le bateau sur la droite
    @param [in,out] bateau Pointeur sur bateau
    @param [in] ennemis Tableau dynamique d'ennemis
    @param [in] terrain Pointeur sur le terrain
    @return 1 si le bateau à tourner, 0 si il y a collision
*/
unsigned char BateauTournerDroite(Bateau * bateau, Ennemis * ennemis, Terrain * terrain);

/**
    @brief Fonction pour tourner le bateau sur la gauche
    @param [in,out] bateau Pointeur sur bateau
    @param [in] ennemis Tableau dynamique d'ennemis
    @param [in] terrain Pointeur sur le terrain
    @return 1 si le bateau à tourner, 0 si il y a collision
*/
unsigned char BateauTournerGauche(Bateau * bateau, Ennemis * ennemis, Terrain * terrain);

#endif
