#ifndef MUSIQUE_H_INCLUDED
#define MUSIQUE_H_INCLUDED

#include <stdio.h>

#ifdef linux
#include "../lib/FMOD/inc/fmod.h"
#endif
#ifdef __WIN32__
#include <fmodex/fmod.h>
#endif

#include "Constantes.h"

/**

    @brief Module de la Musique, Module qui permet de gérer la musique
    @author Cyril C.
    @author Jonathan P.
    @version 0.2
    @struct Musique
*/

typedef struct
{
    FMOD_SYSTEM * systeme; /*!< Objet Système permettant de gérer le son  */
    FMOD_SOUND ** musiques;/*!< Tableau de musique */
    FMOD_SOUND ** sons;    /*!< Tableau de sons */
}   Musique;

/**

    @brief Creer et initialise le pointeur sur Musique ce qui permet de gérer la musique.
    @return Renvoie un pointeur sur Musique
*/
Musique * MusiqueConstructeur();

/**

    @brief Detruit le pointeur sur Musique qui permet de gérer la musique.
    @param [in,out] musique Pointeur sur Musique
*/
void MusiqueDestructeur(Musique * musique);

/**
    @brief Choisit le son à jouer.
    @param [in,out] musique Pointeur sur Musique
    @param [in] nbPiste Entier de 1 à NOMBRE_SON
*/
void MusiqueSonChoix(Musique * musique , unsigned char nbPiste);

/**
    @brief Choisit la musique à jouer.
    @param [in,out] musique Pointeur sur Musique
    @param [in] nbPiste Entier de 1 à NOMBRE_MUSIQUE
*/
void MusiqueMusiqueChoix(Musique * musique , unsigned char nbPiste);

/**

    @brief Creer et initialise le pointeur sur FMOD_SOUND ce qui permet d'utiliser des sons
    @param [in,out] systeme Pointeur sur FMOD_SYSTEM
    @param [in] nbPiste Numero de la piste
    @return Renvoie un pointeur de FMOD_SOUND
*/
FMOD_SOUND * MusiqueSonConstructeur(FMOD_SYSTEM * systeme, unsigned char nbPiste);

/**
    @brief Creer et initialise le pointeur sur FMOD_SOUND ce qui permet d'utiliser des musique
    @param [in,out] systeme Pointeur sur FMOD_SYSTEM
    @param [in] nbPiste Numero de la piste
    @return Renvoie un pointeur de FMOD_SOUND
*/
FMOD_SOUND * MusiqueMusiqueConstructeur(FMOD_SYSTEM * systeme, unsigned char nbPiste);

/**
    @brief Stop tout les sons en cours
    @param [in,out] musique Pointeur sur musique
*/
void MusiqueStop(Musique * musique);

#endif
