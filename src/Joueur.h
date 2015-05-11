#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "Bateau.h"
#include "Sprite.h"
#include "Terrain.h"
#include "TableauDynamiqueTir.h"

/**
    @brief Voici le module Joueur, qui permet la gestion du joueur
    @author Jonathan P.
    @version 0.1

    @struct Joueur
*/
typedef struct
{
    Bateau * bateau; /*!< \brief Bateau du Joueur */
    unsigned int argent; /*!< \brief Argent du Joueur pour les upgrades */
    unsigned char ptsAmelioration; /*!< \brief Points d'amélioration du joueur correspondant au "Niveau du joueur" */
} Joueur;

/**
    @brief Constructeur pour Joueur
    @param [in] sprite Pointeur sur Sprite
    @return Joueur Pointeur sur structure Joueur initialisee
*/
Joueur * JoueurConstructeur(Sprite * sprite);

/**
    @brief Destructeur pour Joueur
    @param [in,out] joueur Pointeur sur Joueur
    @return Pas de retour
*/
void JoueurDestructeur(Joueur * joueur);

/**
    @brief Accesseur pour l'argent du Joueur
    @param [in,out] joueur Pointeur sur Joueur
    @return argent Entier
*/
unsigned int JoueurGetArgent(Joueur * joueur);

/**
    @brief Accesseur pour le bateau du Joueur
    @param [in,out] joueur Pointeur sur Joueur
    @return Pointeur sur Bateau
*/
Bateau * JoueurGetBateau(Joueur * joueur);

/**
    @brief Mutateur pour Joueur
    @param [in,out] joueur Pointeur sur Joueur
    @param [in] argent Entier
    @return Pas de retour
*/
void JoueurSetArgent(Joueur * joueur, unsigned int argent);

/**
    @brief Test de regression pour Joueur
    @return Pas de retour
*/
void JoueurTestRegression(void);

/**
    @brief Fonction d'upgrade de Vie pour Joueur
    @param [in,out] joueur Pointeur sur Joueur
    @param [in] sprite Pointeur sur le sprite suivant
    @return Pas de retour
*/
void JoueurUpgradeVie(Joueur * joueur, Sprite * sprite);

/**
    @brief Fonction d'upgrade de Puissance pour le Joueur
    @param [in,out] joueur Pointeur sur Joueur , sprite Pointeur sur Sprite
    @return Pas de retour
*/
void JoueurUpgradePuissance(Joueur * joueur, Sprite * sprite);

/**
    @brief Fonction d'upgrade de Portee pour Joueur
    @param [in,out] joueur Pointeur sur Joueur , sprite Pointeur sur Sprite
    @return Pas de retour
*/
void JoueurUpgradePortee(Joueur * joueur, Sprite * sprite);

/**
    @brief Fonction d'upgrade de Vitesse pour Joueur
    @param [in,out] joueur Pointeur sur Joueur , sprite Pointeur sur Sprite
    @return Pas de retour
*/
void JoueurUpgradeVitesse(Joueur * joueur, Sprite * sprite);

/**
    @brief Fonction d'upgrade de Sprite pour Joueur
    @param [in,out] joueur Pointeur sur Joueur , sprite Pointeur sur Sprite
    @return Pas de retour
*/

void JoueurUpgradeSprite(Joueur * joueur, unsigned int prix, Sprite * sprite);

/**
    @brief Fonction pour avancer le Joueur
    @param [in,out] joueur Pointeur sur Joueur
    @param [in] ennemis Tableau dynamique d'ennemis
    @param [in] terrain Pointeur sur le terrain, pour eviter les depassements
    @return Pas de retour
*/
void JoueurAvancer(Joueur * joueur, Ennemis * ennemis, Terrain * terrain);

/**
    @brief Fonction pour inverser le sens du Joueur
    @param [in,out] joueur Pointeur sur Joueur
    @return Pas de retour
*/
void JoueurReculer(Joueur * joueur);

/**
    @brief Fonction pour tourner le Joueur sur la droite
    @param [in,out] joueur Pointeur sur Joueur
    @param [in] ennemis Tableau dynamique d'ennemis
    @param [in] terrain Pointeur sur le terrain, pour eviter les depassements
    @return Pas de retour
*/
void JoueurTournerDroite(Joueur * joueur, Ennemis * ennemis, Terrain * terrain);

/**
    @brief Fonction pour tourner le Joueur sur la gauche
    @param [in,out] joueur Pointeur sur Joueur
    @param [in] ennemis Tableau dynamique d'ennemis
    @param [in] terrain Pointeur sur le terrain, pour eviter les depassements
    @return Pas de retour
*/
void JoueurTournerGauche(Joueur * joueur, Ennemis * ennemis, Terrain * terrain);

void JoueurTirer(Joueur * joueur, Tirs * tirs);

#endif
