#ifndef SDLJEU_H_INCLUDED
#define SDLJEU_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#define _SDL_main_h
#include <SDL/SDL.h>
#include <SDL/SDL_getenv.h>

#ifdef linux
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>
#endif
#ifdef __WIN32__
#include <SDL_rotozoom.h>
#include <SDL_ttf.h>
#endif

#include "Jeu.h"

/**
    @brief Module de jeu SDL, permet de faire tourner et afficher le jeu grace à SDL
    @author Jonathan P.

    @struct SDLjeu
*/
typedef struct
{
	Jeu * jeu; /*!< Pointeur sur une structure de jeu */
	SDL_Surface* surface_ecran; /*!< Pointeur sur la surface de l'ecran */
	SDL_Surface* surface_fond; /*!< Pointeur sur la surface de fond (terrain) */
	SDL_Surface* surface_bandeau; /*!< Pointeur sur la surface de fond du bandeau */
	SDL_Surface** surface_micro; /*!< Tableau de pointeur de surface pour le bandeau */
	SDL_Surface** surface_ennemi; /*!< Tableau de pointeur de surface ennemis */
	SDL_Surface** surface_joueur; /*!< Tableau de pointeur de surface joueur */
	SDL_Surface** surface_tir; /*!< Tableau de pointeur de surface de tir */
	SDL_Surface** surface_menu; /*!< Tableau de pointeur des surfaces du menu */
	SDL_Surface** surface_dialogue; /*!< Tableau de pointeur des surfaces des dialogues de boss */
	TTF_Font * police1; /*!< Pointeur sur la premiere police d'ecriture */
	TTF_Font * police2; /*!< Pointeur sur la seconde police d'ecriture */
	FILE * fichier;  /*!< Pointeur sur le fichier de données du jeu */
	unsigned short largeur; /*!< Largeur max de la fenetre d'affichage en pixels */
	unsigned short hauteur; /*!< Hauteur max de la fenetre d'affichage en pixels */
	unsigned char profondeur;   /*!< Profondeur max de la fenetre d'affichage en pixels */
} SDLjeu;

/**
    @brief Fonction d'initialisation du jeu
    @return Pointeur sur la structure SDLjeu correctement initialisee
*/
SDLjeu * SDLjeuInit();

/**
    @brief Fonction qui permet l'affichage d'un menu de selection
    @param [in,out] sdlJeu Pointeur sur une structure SDLjeu initialisee
    @return Pas de retour
*/
void SDLjeuMenu(SDLjeu * sdlJeu);

/**
    @brief Fonction d'affichage du tutoriel d'un style tres voluptueux
    @param [in,out] sdlJeu Pointeur sur une structure SDLjeu initialisee
    @return Pas de retour
*/
void SDLjeuTuto(SDLjeu * sdlJeu);

/**
    @brief Fonction d'affichage du credit final qui vous laissera sans voix !
    @param [in,out] sdlJeu Pointeur sur une structure SDLjeu initialisee
    @return Pas de retour
*/
void SDLjeuCredit(SDLjeu * sdlJeu);

/**
    @brief Fonction qui permet de crier "Game Over Yeah!" avant d'arreter le jeu
    @param [in,out] sdlJeu Pointeur sur une structure SDLjeu initialisee
    @return Pas de retour
*/
void SDLjeuGameOver(SDLjeu * sdlJeu);

/**
    @brief Fonction de boucle de jeu
    @param [in,out] sdlJeu Pointeur sur une structure SDLjeu initialisee
    @return Pas de retour
*/
void SDLjeuBoucle(SDLjeu * sdlJeu);

/**
    @brief Destructeur de la structure SDLjeu
    @param [in,out] sdlJeu Pointeur sur une structure SDLjeu initialisee
    @return Pas de retour
*/
void SDLjeuLibere(SDLjeu * sdlJeu);

/**
    @brief Cette fonction permet de redimentionner au mieux une surface
    @param [in] sdlJeu Pointeur sur une structure SDLjeu
    @param [in] surfaceOriginale Pointeur sur la surface d'origine
    @return Pointeur sur la surface redimentionnee
*/
SDL_Surface * SDLjeuRedimentionneImage(SDLjeu * sdlJeu, SDL_Surface * surfaceOriginale);

/**
    @brief Cette fonction permet d'orienter une surface selon la direction
    @param [in] surfaceOrigine Pointeur sur la surface d'origine
    @param [in] direction Direction de l'image entre 0 et 7
    @return Pointeur sur la surface rototournee
*/
SDL_Surface * SDLorientation(SDL_Surface * surfaceOrigine, unsigned char direction);

/**
    @brief Cette fonction permet de faire une pause d'affichage de duree voulue
    @param [in] temps Temps de pause desire en secondes
    @return Pas de retour
*/
void SDLjeuPause(unsigned char temps);

#endif
