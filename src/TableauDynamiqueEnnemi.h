#ifndef TABLEAUDYNAMIQUEENNEMI_H_INCLUDED
#define TABLEAUDYNAMIQUEENNEMI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct s_bateau Bateau;

/**
    @brief Voici le module du Tableau Dynamique de Bateau (Ennemis)
    @author Jonathan P.
    @version 0.1

 	\struct Ennemis
 	@brief Structure d'un Tableau Dynamique de Bateau
 */
typedef struct
{
    unsigned char capacite;/*!< \brief Capacite du tableau dynamique */
    unsigned char taille_utilisee; /*!< \brief Taille utilisee par le tableau */
    Bateau ** adresse; /*!< \brief Tableau de pointeurs sur Bateau */
} Ennemis;

/**
    @brief Accesseur pour capacite
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @return Capacite, entier
*/
unsigned char EnnemisGetCapacite(const Ennemis * tableau);

/**
    @brief Accesseur pour taille utilisee
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @return Taille utilisee, entier
*/
unsigned char EnnemisGetTailleUtilisee(const Ennemis * tableau);

/**
    @brief Accesseur pour adresse
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @return Tableau de pointeur sur Bateau
*/
Bateau ** EnnemisGetAdresse(const Ennemis * tableau);

/**
    @brief Mutateur pour capacite
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @param capacite entier
    @return Pas de retour
*/
void EnnemisSetCapacite(Ennemis * tableau, unsigned char capacite);

/**
    @brief Mutateur pour taille utilisee
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @param taille entier
    @return Pas de retour
*/
void EnnemisSetTailleUtilisee(Ennemis * tableau, unsigned char taille);

/**
    @brief Mutateur pour adresse
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @param adresse Tableau de pointeurs sur Bateau
    @return Pas de retour
*/
void EnnemisSetAdresse(Ennemis * tableau, Bateau ** adresse);

/**
    @brief Precondition : tableau non prealablement initialise
    @brief Postcondition : tableau initialise a une alveole vide (taille utilisee nulle)
    @return Pointeur sur un tableau dynamique de Bateau
*/
Ennemis * EnnemisInitialiser();

/**
    Precondition : tableau prealablement initialise
    Postcondition : tableau pret a disparaitre. La memoire allouee dynamiquement
    est liberee. On ne pourra plus appeler les sous-programmes qui
    necessitent que tableau soit initialise.
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @return Pas de retour
*/
void EnnemisTestament(Ennemis * tableau);

/**
    Precondition : tableau prealablement initialise
    Postcondition : L'element e est ajoute dans la premiere alveole inutilisee
    du tableau, la taille utilisee est incrementee de 1. Doublement de la
    capacite de tableau, si necessaire.
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @param e Pointeur sur Bateau
    @return Pas de retour
*/
void EnnemisAjouterBateau(Ennemis * tableau, Bateau * e);

/**
    Precondition : tableau prealablement initialise, 0 <= i < tailleUtilisee(tableau)
    Resultat : retourne le i+1eme Element de tableau
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @param i entier inferieur a la taille utilisee
    @return Pas de retour
*/
Bateau * EnnemisValeurIeme(const Ennemis * tableau, unsigned char i);

/**
    Precondition : tableau prealablement initialise et 0 <= i < tailleUtilisee(tableau)
    Postcondition : le i+1eme Element de tableau vaut e
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @param e Pointeur sur Bateau
    @param i entier inferieur a la taille utilisee
    @return Pas de retour
*/
void EnnemisModifierValeurIeme(Ennemis * tableau, Bateau * e, unsigned char i);

/**
    Precondition : tableau prealablement initialise et non vide
    Postcondition : la taille utilisee du tableau est decrementee de 1. Si
    tailleUtilisee < capacite/3, alors on divise la capacité par 2.
    @param tableau Pointeur sur un tableau dynamique de Bateau
    @param position entier inferieur a la taille utilisee
    @return Pas de retour
*/
void EnnemisSupprimer(Ennemis * tableau, unsigned char position);

#endif
