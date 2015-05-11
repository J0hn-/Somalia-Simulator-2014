#ifndef TABLEAUDYNAMIQUETIR_H_INCLUDED
#define TABLEAUDYNAMIQUETIR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "Tir.h"

/**
    @brief Voici le module du Tableau Dynamique de Tir (Tirs)
    @author Jonathan P.
    @version 0.1

 	\struct Tirs
 	@brief Structure d'un Tableau Dynamique de Tir
 */
typedef struct
{
    unsigned short capacite;/*!< \brief Capacite du tableau dynamique */
    unsigned short taille_utilisee; /*!< \brief Taille utilisee par le tableau */
    Tir ** adresse; /*!< \brief Tableau de pointeurs sur Tir */
} Tirs;

/**
    @brief Accesseur pour capacite
    @param tableau Pointeur sur un tableau dynamique de tir
    @return Capacite, entier
*/
unsigned short TirsGetCapacite(const Tirs * tableau);

/**
    @brief Accesseur pour taille utilisee
    @param tableau Pointeur sur un tableau dynamique de tir
    @return Taille utilisee, entier
*/
unsigned short TirsGetTailleUtilisee(const Tirs * tableau);

/**
    @brief Accesseur pour adresse
    @param tableau Pointeur sur un tableau dynamique de tir
    @return Tableau de pointeur sur Tir
*/
Tir ** TirsGetAdresse(const Tirs * tableau);

/**
    @brief Mutateur pour capacite
    @param tableau Pointeur sur un tableau dynamique de tir
    @param capacite entier
    @return Pas de retour
*/
void TirsSetCapacite(Tirs * tableau, unsigned short capacite);

/**
    @brief Mutateur pour taille utilisee
    @param tableau Pointeur sur un tableau dynamique de tir
    @param taille entier
    @return Pas de retour
*/
void TirsSetTailleUtilisee(Tirs * tableau, unsigned short taille);

/**
    @brief Mutateur pour adresse
    @param tableau Pointeur sur un tableau dynamique de tir
    @param adresse Tableau de pointeurs sur Tir
    @return Pas de retour
*/
void TirsSetAdresse(Tirs * tableau, Tir ** adresse);

/**
    @brief Precondition : tableau non prealablement initialise
    @brief Postcondition : tableau initialise a une alveole vide (taille utilisee nulle)
    @return Pointeur sur un tableau dynamique de tir
*/
Tirs * TirsInitialiser();

/**
    Precondition : tableau prealablement initialise
    Postcondition : tableau pret a disparaitre. La memoire allouee dynamiquement
    est liberee. On ne pourra plus appeler les sous-programmes qui
    necessitent que tableau soit initialise.
    @param tableau Pointeur sur un tableau dynamique de tir
    @return Pas de retour
*/
void TirsTestament(Tirs * tableau);

/**
    Precondition : tableau prealablement initialise
    Postcondition : L'element e est ajoute dans la premiere alveole inutilisee
    du tableau, la taille utilisee est incrementee de 1. Doublement de la
    capacite de tableau, si necessaire.
    @param tableau Pointeur sur un tableau dynamique de tir
    @param e Pointeur sur Tir
    @return Pas de retour
*/
void TirsAjouterTir(Tirs * tableau, Tir * e);

/**
    Precondition : tableau prealablement initialise, 0 <= i < tailleUtilisee(tableau)
    Resultat : retourne le i+1eme Element de tableau
    @param tableau Pointeur sur un tableau dynamique de tir
    @param i entier inferieur a la taille utilisee
    @return Pas de retour
*/
Tir * TirsValeurIeme(const Tirs * tableau, unsigned short i);

/**
    Precondition : tableau prealablement initialise et 0 <= i < tailleUtilisee(tableau)
    Postcondition : le i+1eme Element de tableau vaut e
    @param tableau Pointeur sur un tableau dynamique de tir
    @param e Pointeur sur Tir
    @param i entier inferieur a la taille utilisee
    @return Pas de retour
*/
void TirsModifierValeurIeme(Tirs * tableau, Tir * e, unsigned short i);

/**
    Precondition : tableau prealablement initialise et non vide
    Postcondition : la taille utilisee du tableau est decrementee de 1. Si
    tailleUtilisee < capacite/3, alors on divise la capacité par 2.
    @param tableau Pointeur sur un tableau dynamique de tir
    @param position entier inferieur a la taille utilisee
    @return Pas de retour
*/
void TirsSupprimer(Tirs * tableau, unsigned short position);

#endif
