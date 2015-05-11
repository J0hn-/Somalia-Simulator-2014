#ifndef MANCHE_H_INCLUDED
#define MANCHE_H_INCLUDED

#include "Bateau.h"
#include "TableauDynamiqueEnnemi.h"

/**
    @brief Voici le module Manche, qui permet la gestion des ennemis par 'manche'
    @author Cyril C.
    @author Jonathan P.
    @author Quentin DB.
    @version 0.2

    @struct Manche
*/

typedef struct
{
    unsigned char numero;    /*!< \brief Numero de la manche , Entier entre 0 et 255 */
    Sprite * zodiac;    /*!< Pointeur sur le sprite de l'ennemi Zodiac */
    Sprite * requin;    /*!< Pointeur sur le sprite de l'ennemi Requin */
    Sprite * vedette;   /*!< Pointeur sur le sprite de l'ennemi à longue portee */
    Sprite * meyer;   /*!< Pointeur sur le sprite du boss Meyer */
    Sprite * poutine;   /*!< Pointeur sur le sprite du boss Poutine */
    Sprite * mille;   /*!< Pointeur sur le sprite du boss Mille */
    Sprite * genevaux;   /*!< Pointeur sur le sprite du boss Genevaux */
    Sprite * somalien;  /*!< Pointeur sur le sprite du boss Somalien */
} Manche;

/**
    @brief Constructeur pour Manche
    @param spritesEnnemis Tableau de pointeur sur Sprites correspondant aux ennemis rencontres dans le jeu
    @return Pointeur sur Manche
*/
Manche * MancheConstructeur (Sprite ** spritesEnnemis);

/**
    @brief Destructeur pour Manche
    @param [in-out] manche , Pointeur sur Manche
*/
void MancheDestructeur(Manche * manche, Ennemis * ennemis);

/**
    @brief Initialisation de debut de manche
    @param [in,out] manche Pointeur sur Manche
    @param [in,out] ennemis Pointeur sur un tableau dynamique d'ennemis
*/
void MancheDebut(Manche * manche, Ennemis * ennemis);

/**
    @brief Accesseur pour numero
    @param [in] manche Structure Manche
    @return numero Entier compris entre 0 et 255
*/
unsigned char MancheGetNumero(const Manche * manche);

/**
    @brief Intelligence artificielle novice pour le deplacement
    @param [in,out] bateau Pointeur sur bateau
    @param [in] terrain Pointeur sur terrain
    @param [in] xJoueur Position en x du Joueur
    @param [in] yJoueur Position en y du Joueur
    @return 1 si un tir doit etre declanche, 0 sinon
*/
unsigned char MancheIANovice(Ennemis * ennemis, Bateau * bateau, Terrain * terrain, const unsigned char xJoueur, const unsigned char yJoueur);

/**
    @brief Intelligence artificielle pour le deplacement du requin
    @param [in,out] bateau Pointeur sur bateau
    @param [in] terrain Pointeur sur terrain
    @param [in] xJoueur Position en x du Joueur
    @param [in] yJoueur Position en y du Joueur
    @return 1 si un tir doit etre declanche, 0 sinon
*/

unsigned char MancheIARequin(Ennemis * ennemis , Bateau * bateau, Terrain * terrain, const unsigned char xJoueur, const unsigned char yJoueur);

/**
    @brief Selection de l'IA à utiliser
    @param [in,out] bateau Pointeur sur bateau
    @param [in] terrain Pointeur sur terrain
    @param [in] xJoueur Position en x du Joueur
    @param [in] yJoueur Position en y du Joueur
    @return 1 si un tir doit etre declanche, 0 sinon
*/
unsigned char MancheIA(Ennemis * ennemis ,Bateau * bateau, Terrain * terrain, const unsigned char xJoueur, const unsigned char yJoueur);


/**
    @brief Test de Regression de Manche
*/
void MancheTestRegression();

#endif
