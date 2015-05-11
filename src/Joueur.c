#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "Joueur.h"
#include "Constantes.h"

Joueur * JoueurConstructeur(Sprite * sprite)
{
    Joueur * joueur = (Joueur *)malloc(sizeof(Joueur));
    joueur->argent = 0;
    joueur->bateau = BateauConstructeur(10, 1, 20, 100, 100, 1, 0, 54, 32, sprite);
    joueur->ptsAmelioration = 0;
    return joueur;
}

void JoueurDestructeur(Joueur * joueur)
{
    assert(joueur);
    BateauDestructeur(joueur->bateau);
    joueur->ptsAmelioration = 0;
    free(joueur);
    joueur = NULL;
}

unsigned int JoueurGetArgent(Joueur * joueur)
{
    assert(joueur);
    return joueur->argent;
}

void JoueurSetArgent(Joueur * joueur, unsigned int argent)
{
    assert(joueur);
    joueur->argent = argent;
}

unsigned int JoueurGetPtsAmelioration(Joueur * joueur)
{
    assert(joueur);
    return joueur->ptsAmelioration;
}

void JoueurSetPtsAmelioration(Joueur * joueur, unsigned int ptsAmelioration)
{
    assert(joueur);
    joueur->ptsAmelioration = ptsAmelioration;
}

Bateau * JoueurGetBateau(Joueur * joueur)
{
    assert(joueur);
    return joueur->bateau;
}

void JoueurUpgradeVie(Joueur * joueur, Sprite * sprite)
{
    assert(joueur);
    assert(sprite);

    unsigned short vieMax = BateauGetVieMax(joueur->bateau);
    unsigned int prix = vieMax/10+(10*vieMax/100)*vieMax/100;

    if(JoueurGetArgent(joueur) >= prix)
    {
        JoueurSetArgent(joueur, JoueurGetArgent(joueur) - prix);
        BateauSetVieMax(joueur->bateau, vieMax + 100);
        BateauSetVie(joueur->bateau, vieMax + 100);
        JoueurUpgradeSprite(joueur, prix, sprite);
    }
}

void JoueurUpgradePuissance(Joueur * joueur, Sprite * sprite)
{
    unsigned char puissance = BateauGetPuissance(joueur->bateau);
    unsigned int prix = puissance/10+(10*puissance/10)*puissance/10;
    if(JoueurGetArgent(joueur) >= prix)
    {
        JoueurSetArgent(joueur, JoueurGetArgent(joueur) - prix);
        BateauSetPuissance(joueur->bateau, puissance + 10);
        JoueurUpgradeSprite(joueur, prix, sprite);
    }
}

void JoueurUpgradePortee(Joueur * joueur, Sprite * sprite)
{
    unsigned char portee = BateauGetPortee(joueur->bateau);
    unsigned int prix = (portee%10)*100+portee*portee-20;
    if(joueur->argent >= prix && portee < 100)
    {
        joueur->argent = joueur->argent - prix;
        BateauSetPortee(joueur->bateau, portee + 3);
        JoueurUpgradeSprite(joueur, prix, sprite);
    }
}

void JoueurUpgradeVitesse(Joueur * joueur, Sprite * sprite)
{
    unsigned char vitesse = BateauGetVitesse(joueur->bateau);
    unsigned int prix = vitesse*100 ;
    if(JoueurGetArgent(joueur) >= prix && vitesse < 6)
    {
        JoueurSetArgent(joueur, JoueurGetArgent(joueur) - prix);
        BateauSetVitesse(joueur->bateau, vitesse+1);
        JoueurUpgradeSprite(joueur, prix, sprite);
    }
}

void JoueurUpgradeSprite(Joueur * joueur, unsigned int prix, Sprite * sprite)
{
    unsigned char ptsAm = JoueurGetPtsAmelioration(joueur);
    JoueurSetPtsAmelioration(joueur, ++ptsAm);

    if(ptsAm == 5 || ptsAm == 10 || ptsAm == 15 || ptsAm == 20)
    {
        BateauSetAspect(joueur->bateau, sprite);
        BateauSetTaille(joueur->bateau, BateauGetTaille(joueur->bateau)+1);
    }
}


void JoueurAvancer(Joueur * joueur, Ennemis * ennemis, Terrain * terrain)
{
    BateauAvancer(JoueurGetBateau(joueur), ennemis, terrain);
}

void JoueurReculer(Joueur * joueur)
{
    BateauReculer(JoueurGetBateau(joueur));
}

void JoueurTournerDroite(Joueur * joueur, Ennemis * ennemis, Terrain * terrain)
{
    BateauTournerDroite(JoueurGetBateau(joueur), ennemis, terrain);
}

void JoueurTournerGauche(Joueur * joueur, Ennemis * ennemis, Terrain * terrain)
{
    BateauTournerGauche(JoueurGetBateau(joueur), ennemis, terrain);
}

void JoueurPrivateAffichageStats(Joueur * joueur)
{
    assert(joueur);
    printf("Puissance : %d\n", BateauGetPuissance(joueur->bateau));
    printf("Vitesse : %d\n", BateauGetVitesse(joueur->bateau));
    printf("Portee : %d\n", BateauGetPortee(joueur->bateau));
    printf("Vie : %d/%d\n", BateauGetVie(joueur->bateau), BateauGetVieMax(joueur->bateau));
    printf("Taille : %d\n", BateauGetTaille(joueur->bateau));
    printf("Direction : %d\n", BateauGetDirection(joueur->bateau));
}

void JoueurTestRegression(void)
{
    printf("\n-- Joueur Test de regression --\n\n");

    printf("- Constructeur -\n");
    Sprite * texture = SpriteConstructeur(10,10,0);
    Joueur * joueur = JoueurConstructeur(texture);
    if(joueur != NULL)
        printf("->Constructeur Joueur : OK\n");

    printf("- Fonctions d'Upgrade -\n");
    JoueurSetArgent(joueur, JoueurGetArgent(joueur) + 100000);
    printf("->Accesseur et mutateur d'argent : OK\n");
    JoueurUpgradeVie(joueur, texture);
    JoueurUpgradePuissance(joueur, texture);
    JoueurUpgradePortee(joueur, texture);
    JoueurUpgradeVitesse(joueur, texture);

    JoueurPrivateAffichageStats(joueur);

    printf("- Destructeur de joueur -\n");
    JoueurDestructeur(joueur);
    SpriteDestructeur(texture);
    printf("->Destruction confirmee : OK\n");

    printf("-- Joueur Fin du test, Merci et a bientot --\n\n");
}
