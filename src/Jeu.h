#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "Terrain.h"
#include "Joueur.h"
#include "Manche.h"
#include "TableauDynamiqueTir.h"
#include "TableauDynamiqueEnnemi.h"
#include "Tir.h"
#include "Sprite.h"
#include "Musique.h"

/**
    Bonjour et bienvenu dans le module Jeu
    @brief Ce module a pour vocation de mettre en place un moteur de jeu performant alliant puissance et optimisation
    @author Jonathan P.

    @struct Jeu
*/

typedef struct
{
    Terrain * terrain; /*!< \brief Pointeur sur le terrain du jeu */
    Joueur * joueur; /*!< \brief Pointeur sur le joueur */
    Manche * manche; /*!< \brief Pointeur sur manche */
    Tirs * tirs; /*!< \brief Tableau Dynamique de pointeurs sur tir */
    Ennemis * ennemis; /*!< \brief Tableau Dynamique de pointeurs sur bateau */
    Musique * musique; /*!< \brief Pointeur sur musique */
    Sprite ** spritesTir; /*!< \brief Tableau de pointeurs sur les sprites de tir */
    Sprite ** spritesJoueur; /*!< \brief Tableau de pointeurs sur les sprites du joueur */
    Sprite ** spritesEnnemis; /*!< \brief Tableau de pointeurs sur les sprites des ennemis */
} Jeu;

/**
    @brief Constructeur pour Jeu
    @return Pointeur sur une structure Jeu correctement initialisee
*/
Jeu * JeuConstructeur();

/**
    @brief Destructeur pour Jeu
    @param [in,out] jeu Pointeur sur Jeu
    @return Pas de retour
*/
void JeuDestructeur(Jeu * jeu);

/**
    @brief Accesseur pour Joueur
    @param [in] jeu Pointeur sur Jeu
    @return Pointeur sur structure Joueur
*/
Joueur * JeuGetJoueur(Jeu * jeu);

/**
    @brief Accesseur pour Terrain
    @param [in] jeu Pointeur sur Jeu
    @return Pointeur sur structure Terrain
*/
Terrain * JeuGetTerrain(Jeu * jeu);

/**
    @brief Accesseur pour Manche
    @param [in] jeu Pointeur sur Jeu
    @return Pointeur sur structure Manche
*/
Manche * JeuGetManche(Jeu * jeu);

/**
    @brief Accesseur pour Tirs
    @param [in] jeu Pointeur sur Jeu
    @return Pointeur sur tableau dynamique de tir
*/
Tirs * JeuGetTirs(Jeu * jeu);

/**
    @brief Accesseur pour Ennemis
    @param [in] jeu Pointeur sur Jeu
    @return Pointeur sur tableau dynamique d'ennemis
*/
Ennemis * JeuGetEnnemis(Jeu * jeu);

/**
    @brief Accesseur pour Musique
    @param [in] jeu Pointeur sur Jeu
    @return Pointeur sur structure Musique
*/
Musique * JeuGetMusique(Jeu * jeu);

/**
    @brief Accesseur pour un sprite au choix
    @param [in] jeu Pointeur sur Jeu
    @param [in] type Chaine de caractere du sprite voulu (Tx pour tir, Jx pour joueur, Ex pour ennemi, x l'indice commencant a 0)
    @return Pointeur sur structure Sprite
*/
Sprite * JeuGetSprite(Jeu * jeu, const char * type);

/**
    @brief Fonction qui fait tirer le joueur
    Si le tir est valide, un tir est cree et ajoute au tableau dynamique
    @param [in,out] jeu Pointeur sur Jeu
    @return Pas de retour
*/
void JeuTirJoueur(Jeu * jeu);

/**
    @brief Fonction d'association d'une touche a une action
    @param [in,out] jeu Pointeur sur Jeu
    @param [in] touche Caractere de la touche associee
    @return Pas de retour
*/
void JeuActionClavier(Jeu * jeu, const char touche);

/**
    @brief Fonction qui fait evoluer le jeu en appelant les autres fonctions
    @param [in,out] jeu Pointeur sur Jeu
    @param [in,out] gameOver Entier pour mettre fin à la boucle de jeu (Game Over)
    @param [in,out] pauseManche Entier qui permet un laps de temps entre les manches
    @param [in,out] dephasage Entier qui permet un rafraichissement des tirs plus rapide
    @return Pas de retour
*/
void JeuEvolution(Jeu * jeu, unsigned char * gameOver, unsigned char * pauseManche, unsigned char * dephasage);

/**
    @brief Test de regression pour le Jeu
    @return Pas de retour
*/
void JeuTestRegression();

#endif
