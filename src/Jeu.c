#include <assert.h>

#include "Jeu.h"
#include "Constantes.h"

void JeuInitialiserSprites(Jeu * jeu)
{
    unsigned char i;
    assert(jeu);

    jeu->spritesTir = (Sprite **)malloc(NOMBRE_SPRITE_TIR*sizeof(Sprite *));
    assert(jeu->spritesTir);

    /* Plage de réservation des sprites de tir */
    for(i = 0; i < NOMBRE_SPRITE_TIR; ++i)
        jeu->spritesTir[i] = SpriteConstructeur(1,1,i);

    jeu->spritesJoueur = (Sprite **)malloc(NOMBRE_SPRITE_JOUEUR*sizeof(Sprite *));
    assert(jeu->spritesJoueur);

    /* Plage de réservation des sprites du joueur */
    jeu->spritesJoueur[0] = SpriteConstructeur(3,6,0);
    jeu->spritesJoueur[1] = SpriteConstructeur(3,6,1);
    jeu->spritesJoueur[2] = SpriteConstructeur(3,7,2);
    jeu->spritesJoueur[3] = SpriteConstructeur(5,10,3);
    jeu->spritesJoueur[4] = SpriteConstructeur(4,12,4);

    jeu->spritesEnnemis = (Sprite **)malloc(NOMBRE_SPRITE_ENNEMI*sizeof(Sprite *));
    assert(jeu->spritesEnnemis);

    /* Plage de réservation des sprites des ennemis */
    jeu->spritesEnnemis[0] = SpriteConstructeur(3,6,0);
    jeu->spritesEnnemis[1] = SpriteConstructeur(3,8,1);
    jeu->spritesEnnemis[2] = SpriteConstructeur(3,7,2);
    jeu->spritesEnnemis[3] = SpriteConstructeur(5,8,3);
    jeu->spritesEnnemis[4] = SpriteConstructeur(4,17,4);
    jeu->spritesEnnemis[5] = SpriteConstructeur(5,5,5);
    jeu->spritesEnnemis[6] = SpriteConstructeur(6,11,6);
    jeu->spritesEnnemis[7] = SpriteConstructeur(6,11,7);
    jeu->spritesEnnemis[8] = SpriteConstructeur(6,11,8);
}

Sprite * JeuGetSprite(Jeu * jeu, const char * type)
{
    switch(type[0])
    {
    case 'T':
        return jeu->spritesTir[(type[1] -1 -'0')];
        break;
    case 'J':
        return jeu->spritesJoueur[(type[1] -1 -'0')];
        break;
    case 'E':
        return jeu->spritesEnnemis[(type[1] -1 -'0')];
        break;
    }
    return SpriteConstructeur(0,0,0);
}

Jeu * JeuConstructeur()
{
    Jeu * jeu = (Jeu *)malloc(sizeof(Jeu));
    assert(jeu);

    JeuInitialiserSprites(jeu);

    jeu->joueur = JoueurConstructeur(JeuGetSprite(jeu, "J1"));
    jeu->terrain = TerrainConstructeur("data/map.txt");
    jeu->tirs = TirsInitialiser();
    jeu->ennemis = EnnemisInitialiser();
    jeu->manche = MancheConstructeur(jeu->spritesEnnemis);
    jeu->musique = MusiqueConstructeur();

    return jeu;
}

void JeuDestructeur(Jeu * jeu)
{
    unsigned char i;

    assert(jeu);

    JoueurDestructeur(jeu->joueur);
    TerrainDestructeur(jeu->terrain);

    while(TirsGetTailleUtilisee(JeuGetTirs(jeu)) > 0)
    {
        TirDestructeur(TirsValeurIeme(JeuGetTirs(jeu), 0));
        TirsSupprimer(JeuGetTirs(jeu), 0);
    }
    TirsTestament(jeu->tirs);

    MancheDestructeur(jeu->manche, jeu->ennemis);
    EnnemisTestament(jeu->ennemis);

    MusiqueDestructeur(jeu->musique);

    for(i = 0; i < NOMBRE_SPRITE_TIR; ++i)
        SpriteDestructeur(jeu->spritesTir[i]);
    for(i = 0; i < NOMBRE_SPRITE_JOUEUR; ++i)
        SpriteDestructeur(jeu->spritesJoueur[i]);
    for(i = 0; i < NOMBRE_SPRITE_ENNEMI; ++i)
        SpriteDestructeur(jeu->spritesEnnemis[i]);

    free(jeu->spritesTir);
    free(jeu->spritesJoueur);
    free(jeu->spritesEnnemis);
    free(jeu);
}

Joueur * JeuGetJoueur(Jeu * jeu)
{
    assert(jeu);
    return jeu->joueur;
}

Terrain * JeuGetTerrain(Jeu * jeu)
{
    assert(jeu);
    return jeu->terrain;
}

Tirs * JeuGetTirs(Jeu * jeu)
{
    assert(jeu);
    return jeu->tirs;
}

Ennemis * JeuGetEnnemis(Jeu * jeu)
{
    assert(jeu);
    return jeu->ennemis;
}

Musique * JeuGetMusique(Jeu * jeu)
{
    assert(jeu);
    return jeu->musique;
}

Manche * JeuGetManche(Jeu * jeu)
{
    assert(jeu);
    return jeu->manche;
}

void JeuTirJoueur(Jeu * jeu)
{
    Joueur * joueur = JeuGetJoueur(jeu);
    Bateau * bateau = JoueurGetBateau(joueur);
    Tirs * tirs = JeuGetTirs(jeu);
    Tir * tir;
    Sprite * sprite;

    unsigned char x = PositionGetX(BateauGetPosition(bateau));
    unsigned char y = PositionGetY(BateauGetPosition(bateau));

    assert(jeu);

    if(BateauGetTaille(bateau) == 1)
        sprite = JeuGetSprite(jeu, "T1");
    else if(BateauGetTaille(bateau) == 5)
        sprite = JeuGetSprite(jeu, "T2");
    else
        sprite = JeuGetSprite(jeu, "T3");

    tir = TirConstructeur(BateauGetPuissance(bateau), BateauGetPortee(bateau),
                                BateauGetDirection(bateau), x, y, sprite);
    if(tir != NULL)
        TirsAjouterTir(tirs, tir);
}

void JeuTirEnnemi(Jeu * jeu, Bateau * bateau)
{
    assert(jeu);
    assert(bateau);

    unsigned char x = PositionGetX(BateauGetPosition(bateau));
    unsigned char y = PositionGetY(BateauGetPosition(bateau));
    unsigned char numero = SpriteGetTexture(BateauGetAspect(bateau));
    char type[2] = "T2";

    Tirs * tirs = JeuGetTirs(jeu);

    /*MusiqueSonChoix(JeuGetMusique(jeu), 1);*/

    if(numero >= 3 && numero <= 8)
        type[1] = numero + 1 + '0';

    Tir * tir = TirConstructeur(BateauGetPuissance(bateau), BateauGetPortee(bateau),
                                BateauGetDirection(bateau), x, y, JeuGetSprite(jeu, type));
    if(tir != NULL)
        TirsAjouterTir(tirs, tir);
}

void JeuDeplacementTir(Jeu * jeu)
{
    unsigned char x, y, tailleMaxX, tailleMaxY, j;
    unsigned char xBateauInf, yBateauInf, xBateauSup, yBateauSup;
    Ennemis * ennemis = JeuGetEnnemis(jeu);
    unsigned char nbEnnemis = EnnemisGetTailleUtilisee(ennemis);
    Terrain * terrain = JeuGetTerrain(jeu);
    Tirs * tirs = JeuGetTirs(jeu);
    unsigned short nbTirs = TirsGetTailleUtilisee(tirs);
    unsigned short i;
    Tir * tirActuel;
    Position * positionTir;
    Position position;
    Bateau * bateau;

    /* On prend chaque boulet 1 à 1 du tableau dynamique */
    for(i = 0; i < nbTirs; ++i)
    {
        tirActuel = TirsValeurIeme(tirs, i);
        assert(tirActuel);
        /* On vérifie que le boulet n'a pas atteint sa limite */
        if(TirGetPortee(tirActuel) == 0)
        {
            TirDestructeur(tirActuel);
            TirsSupprimer(tirs, i);
            i--;
            nbTirs=nbTirs-1;
        }
        else
        {
            TirSetPortee(tirActuel, TirGetPortee(tirActuel)-1);
            positionTir = TirGetPosition(tirActuel);
            assert(positionTir);
            x = PositionGetX(positionTir);
            y = PositionGetY(positionTir);
            tailleMaxX = TerrainGetX(terrain) -1;
            tailleMaxY = TerrainGetY(terrain) -1;

            /* Voyons si notre tir n'a pas atteint le bord de la map */
            if(x == 0 || y == 0 || x >= tailleMaxX || y >= tailleMaxY)
            {
                TirDestructeur(tirActuel);
                TirsSupprimer(tirs, i);
                i--;
                nbTirs=nbTirs-1;
            }

            /*Voyons si il y a une collision avec le décor */
            else if(TerrainGetCase(terrain,x,y) == '2')
            {
                TirDestructeur(tirActuel);
                TirsSupprimer(tirs, i);
                i--;
                nbTirs=nbTirs-1;
            }
            else
            {
                 /* On effectue le deplacement */
                switch(TirGetDirection(tirActuel))
                {
                    case 0:
                        if(y > 0)
                            PositionSetY(positionTir, --y);
                        break;
                    case 1:
                        if(x < tailleMaxX && y > 0)
                        {
                                PositionSetX(positionTir, ++x);
                                PositionSetY(positionTir, --y);
                        }
                        break;
                    case 2:
                        if(x < tailleMaxX)
                            PositionSetX(positionTir, ++x);
                        break;
                    case 3:
                        if(x < tailleMaxX && y < tailleMaxY)
                        {
                            PositionSetX(positionTir, ++x);
                            PositionSetY(positionTir, ++y);
                        }
                        break;
                    case 4:
                        if(y < tailleMaxY)
                            PositionSetY(positionTir , ++y);
                        break;
                    case 5:
                        if(x > 0 && y < tailleMaxY)
                        {
                            PositionSetX(positionTir, --x);
                            PositionSetY(positionTir, ++y);
                        }
                        break;
                    case 6:
                        if(x > 0)
                            PositionSetX(positionTir, --x);
                        break;
                    case 7:
                        if(x > 0 && y > 0)
                        {
                            PositionSetX(positionTir, --x);
                            PositionSetY(positionTir, --y);
                        }
                        break;
                }

                /* On va tester la collision */
                x = PositionGetX(positionTir);
                y = PositionGetY(positionTir);

                /* Voyons si notre tir n'a pas atteint le bord de la map */
                if(x == 0 || y == 0 || x == tailleMaxX || y == tailleMaxY)
                {
                    TirDestructeur(tirActuel);
                    TirsSupprimer(tirs, i);
                    i--;
                    nbTirs--;
                }
                else
                {
                    bateau = JoueurGetBateau(JeuGetJoueur(jeu));

                    /* Voyons si le bateau du joueur n'est pas touché */
                    position = BateauGetHitBoxInferieur(bateau);
                    xBateauInf = PositionGetX(&position);
                    yBateauInf = PositionGetY(&position);
                    position = BateauGetHitBoxSuperieur(bateau);
                    xBateauSup = PositionGetX(&position);
                    yBateauSup = PositionGetY(&position);
                    if(x >= xBateauInf && y >= yBateauInf && x <= xBateauSup && y <= yBateauSup)
                    {
                        if(BateauGetVie(bateau) - TirGetPuissance(tirActuel) > 0)
                            BateauSetVie(bateau, BateauGetVie(bateau)-TirGetPuissance(tirActuel));
                        else
                            BateauSetVie(bateau, 0);
                        TirDestructeur(tirActuel);
                        TirsSupprimer(tirs, i);
                        i--;
                        nbTirs--;
                    }
                    else
                    {
                        /* Voyons si un bateau est percuté */
                        for(j = 0; j < nbEnnemis; ++j)
                        {
                            bateau = EnnemisValeurIeme(ennemis, j);
                            position = BateauGetHitBoxInferieur(bateau);
                            xBateauInf = PositionGetX(&position);
                            yBateauInf = PositionGetY(&position);
                            position = BateauGetHitBoxSuperieur(bateau);
                            xBateauSup = PositionGetX(&position);
                            yBateauSup = PositionGetY(&position);
                            #ifdef DEBUG
                                printf("HitBox : %d, %d / %d, %d\n", xBateauInf, yBateauInf, xBateauSup, yBateauSup);
                            #endif
                            if(x >= xBateauInf && y >= yBateauInf && x <= xBateauSup && y <= yBateauSup)
                            {
                                if(BateauGetVie(bateau) > TirGetPuissance(tirActuel))
                                    BateauSetVie(bateau, BateauGetVie(bateau)-TirGetPuissance(tirActuel));
                                else
                                    BateauSetVie(bateau, 0);
                                TirDestructeur(tirActuel);
                                TirsSupprimer(tirs, i);
                                i--;
                                nbTirs--;

                                /* Si le bateau ennemi a perdu toute sa vie */
                                if(BateauGetVie(bateau) <= 0)
                                {
                                    if(BateauGetPortee(bateau)>49)
                                        {
                                            JoueurSetArgent(JeuGetJoueur(jeu), JoueurGetArgent(JeuGetJoueur(jeu))
                                         +((BateauGetVieMax(bateau)/10)+5+5*(MancheGetNumero(JeuGetManche(jeu))/10))*2);
                                        }
                                    else
                                        {JoueurSetArgent(JeuGetJoueur(jeu), JoueurGetArgent(JeuGetJoueur(jeu))
                                         +(BateauGetVieMax(bateau)/10)+5+5*(MancheGetNumero(JeuGetManche(jeu))/10));
                                        }
                                    BateauDestructeur(bateau);
                                    EnnemisSupprimer(ennemis, j);
                                    nbEnnemis--;
                                    j--;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void JeuDeplacementEnnemi(Jeu * jeu)
{
    unsigned char j, x, y;
    Ennemis * ennemis = JeuGetEnnemis(jeu);
    unsigned char nbEnnemis = EnnemisGetTailleUtilisee(ennemis);
    Bateau * bateau;
    Position p;

    p = BateauGetPositionMilieu(JoueurGetBateau(JeuGetJoueur(jeu)));
    x = PositionGetX(&p);
    y = PositionGetY(&p);

    for(j = 0; j < nbEnnemis; ++j)
    {
        bateau = EnnemisValeurIeme(ennemis, j);
        if(MancheIA(ennemis, bateau, JeuGetTerrain(jeu), x, y) == 1)
        {
            if(BateauGetTaille(bateau) == 0)
            {
                JeuTirEnnemi(jeu, bateau);
                JoueurSetArgent(JeuGetJoueur(jeu), JoueurGetArgent(JeuGetJoueur(jeu))+BateauGetVieMax(bateau)*2);
                BateauDestructeur(bateau);
                EnnemisSupprimer(ennemis, j);
                nbEnnemis--;
                j--;
            }
            else
            {
                JeuTirEnnemi(jeu, bateau);
            }
        }
    }
}

void JeuActionClavier(Jeu * jeu, const char touche)
{
    char type[] = "J0";
    if(BateauGetTaille(JoueurGetBateau(JeuGetJoueur(jeu))) < NOMBRE_SPRITE_JOUEUR)
        type[1] = BateauGetTaille(JoueurGetBateau(JeuGetJoueur(jeu))) + 1 + '0';
    else
        type[1] = BateauGetTaille(JoueurGetBateau(JeuGetJoueur(jeu))) + '0';

    switch(touche)
    {
        case 'd':
            JoueurTournerDroite(JeuGetJoueur(jeu), JeuGetEnnemis(jeu), JeuGetTerrain(jeu));
            break;
        case 'q':
            JoueurTournerGauche(JeuGetJoueur(jeu), JeuGetEnnemis(jeu), JeuGetTerrain(jeu));
            break;
        case 'z':
            JoueurAvancer(JeuGetJoueur(jeu), JeuGetEnnemis(jeu), JeuGetTerrain(jeu));
            break;
        case 's':
            JoueurReculer(JeuGetJoueur(jeu));
            break;
        case ' ':
            JeuTirJoueur(jeu);
            break;
        case 'a':
            JoueurUpgradeVie(JeuGetJoueur(jeu), JeuGetSprite(jeu, type));
            break;
        case 'e':
            JoueurUpgradePuissance(JeuGetJoueur(jeu), JeuGetSprite(jeu, type));
            break;
        case 'r':
            JoueurUpgradePortee(JeuGetJoueur(jeu), JeuGetSprite(jeu, type));
            break;
        case 't':
            JoueurUpgradeVitesse(JeuGetJoueur(jeu), JeuGetSprite(jeu, type));
            break;
        default:
            break;
    }
}

void JeuEvolution(Jeu * jeu, unsigned char * gameOver, unsigned char * pauseManche, unsigned char * dephasage)
{
    if(BateauGetVie(JoueurGetBateau(JeuGetJoueur(jeu))) > 0)
    {
        unsigned char vitesseEnnemis;
        vitesseEnnemis = MancheGetNumero(JeuGetManche(jeu))/20;
        if (vitesseEnnemis >5)
            vitesseEnnemis = 5;
        JeuDeplacementTir(jeu);
        if(*dephasage == 0)
        {
            JeuDeplacementEnnemi(jeu);
            *dephasage = 1;
        }
        else if(*dephasage == (6 - vitesseEnnemis))
        {
            *dephasage = 0;
        }
        else
            *dephasage+= 1;

        if(EnnemisGetTailleUtilisee(JeuGetEnnemis(jeu)) == 0)
        {
            if(* pauseManche == 0) /* Fin de manche */
            {
                if(MancheGetNumero(JeuGetManche(jeu)) == 50) /* Quand on a tué le boss final */
                {
                    MusiqueStop(JeuGetMusique(jeu));
                    MusiqueMusiqueChoix(JeuGetMusique(jeu),4);
                    MusiqueSonChoix(JeuGetMusique(jeu),4);
                    * pauseManche = 1;
                }
                else if(MancheGetNumero(JeuGetManche(jeu)) == 49)
                {
                    MusiqueStop(JeuGetMusique(jeu));
                    MusiqueSonChoix(JeuGetMusique(jeu),5);
                    * pauseManche = 1;
                }
                else if(MancheGetNumero(JeuGetManche(jeu))%10 == 9
                        || MancheGetNumero(JeuGetManche(jeu))%10 == 0)
                {
                    MusiqueStop(JeuGetMusique(jeu));
                    MusiqueSonChoix(JeuGetMusique(jeu),4);
                    * pauseManche = 1;
                }
                else
                {
                    MusiqueSonChoix(JeuGetMusique(jeu),4);
                    * pauseManche = 1;
                }

            }
            if(* pauseManche == 3)
            {
                if(MancheGetNumero(JeuGetManche(jeu)) >= 50) /* Manche PGM */
                {
                    MancheDebut(JeuGetManche(jeu), JeuGetEnnemis(jeu));
                    MusiqueSonChoix(JeuGetMusique(jeu), 3);
                    * pauseManche = 0;
                }
                else
                {
                    if(MancheGetNumero(JeuGetManche(jeu)) == 49) /* Boss Final */
                    {
                        MancheDebut(JeuGetManche(jeu), JeuGetEnnemis(jeu));
                        MusiqueSonChoix(JeuGetMusique(jeu), 3);
                        MusiqueMusiqueChoix(JeuGetMusique(jeu),5);
                        * pauseManche = 0;
                    }
                    else
                    {
                        if(MancheGetNumero(JeuGetManche(jeu))%10 == 9) /* Manche de boss */
                        {
                            MancheDebut(JeuGetManche(jeu), JeuGetEnnemis(jeu));
                            MusiqueSonChoix(JeuGetMusique(jeu), 3);
                            MusiqueMusiqueChoix(JeuGetMusique(jeu),2);
                            * pauseManche = 0;
                        }
                        else if(MancheGetNumero(JeuGetManche(jeu))%10 == 0) /* Manche après boss */
                        {
                            MancheDebut(JeuGetManche(jeu), JeuGetEnnemis(jeu));
                            MusiqueSonChoix(JeuGetMusique(jeu), 3);
                            MusiqueMusiqueChoix(JeuGetMusique(jeu),1);
                            * pauseManche = 0;
                        }
                        else /* Manche normale */
                        {
                            MancheDebut(JeuGetManche(jeu), JeuGetEnnemis(jeu));
                            MusiqueSonChoix(JeuGetMusique(jeu), 3);
                            * pauseManche = 0;
                        }
                    }
                }
            }
        }
    }
    else
    {
        *gameOver = 0;
    }
}

void JeuTestRegression()
{
    printf("\n-- Jeu Test de regression --\n\n");

    printf("- Constructeur -\n");
    Jeu * jeu = JeuConstructeur();
    if(jeu != NULL)
        printf("->Constructeur Jeu : OK\n");
    else
        printf("/!\\ Constructeur Jeu : FAIL\n");
    printf("- Destructeur de jeu -\n");
    JeuDestructeur(jeu);
    printf("->Destruction confirmee : OK\n");

    printf("-- Jeu Fin du test, Merci et a bientot --\n\n");
}
