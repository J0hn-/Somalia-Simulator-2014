#ifndef TESTNCURSES_H_INCLUDED
#define TESTNCURSES_H_INCLUDED
#include <curses.h>
#include "Jeu.h"
/**
    @brief Voici le module de l'affichage par ncurses.
    @author J.P
    @author QDB
    @version 0.1

*/


/**
    @brief proc�dure affichage du "tour" de jeu
    @param [in] win pointeur sur Window
    @param [in]  Jeu pointeur sur jeu
    @return Pas de retour.
*/
void nCursesAffichage(WINDOW* win, Jeu * jeu);

/**
    @brief Proc�dure de la boucle de jeu
    @param [in] Jeu pointeur sur jeu
    @return Pas de retour.
*/
void nCursesBoucle(Jeu * jeu);

/**
    @brief Test r�gression du module.
    @param [in] Jeu pointeur sur jeu
    @return Pas de retour.
*/
void nCursesTest();

#endif
