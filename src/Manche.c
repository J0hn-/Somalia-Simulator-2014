#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "Manche.h"
#include "Constantes.h"

Manche * MancheConstructeur(Sprite ** spritesEnnemis)
{
    Manche * manche = (Manche*)malloc(sizeof(Manche));
    manche->numero = MANCHE_DE_DEBUT;
    manche->zodiac = spritesEnnemis[0];
    manche->requin = spritesEnnemis[1];
    manche->vedette = spritesEnnemis[2];
    manche->meyer = spritesEnnemis[3];
    manche->poutine = spritesEnnemis[4];
    manche->mille = spritesEnnemis[6];
    manche->genevaux = spritesEnnemis[5];
    manche->somalien = spritesEnnemis[2];
    return manche;
}

void MancheDestructeur(Manche * manche, Ennemis * ennemis)
{
    while(EnnemisGetTailleUtilisee(ennemis) > 0)
    {
        BateauDestructeur(EnnemisValeurIeme(ennemis, 0));
        EnnemisSupprimer(ennemis, 0);
    }
    manche->numero=0;
    free(manche);
}

void MancheDebut(Manche * manche, Ennemis * ennemis)
{
    if(manche->numero%10 != 9 || manche->numero>=50)
    {
        unsigned char i,x,y;
        unsigned char nbEnnemis = (manche->numero/10+2-manche->numero/30);
        Bateau * bateau;
        int puissance;
        int vie;

        (manche->numero)++;
        puissance = 10+10*(manche->numero/10);
        vie=50+50*(manche->numero/10);
        srand(time(NULL));

        for(i = 0; i < nbEnnemis; ++i)
        {
            bateau=NULL;
            if(rand()%2 == 0)
            {
                x = 3 + rand() % 23;
                y = 3 + rand() % 25;
            }
            else
            {
                do
                {
                    x = 70 + rand() % 45;
                    y = 5 + rand() % 50;
                }
                while(x >= 70 && x <= 105 && y >= 15 && y <= 50);
            }
            while (bateau == NULL)
            {
                if(manche->numero<20)
                {
                    bateau = BateauConstructeur(puissance,2,25,vie,vie,1,0,x,y,manche->zodiac);
                    EnnemisAjouterBateau(ennemis, bateau);
                }
                else if(manche->numero >= 21 && manche->numero <=39)
                {
                    if(rand()%(manche->numero)<10)
                    {
                        bateau = BateauConstructeur(puissance,2,25,vie,vie,1,0,x,y,manche->zodiac);
                        EnnemisAjouterBateau(ennemis, bateau);
                    }
                    else
                    {
                        bateau = BateauConstructeur(puissance/2,2,50,vie/2,vie/2,2,0,x,y,manche->vedette);
                        EnnemisAjouterBateau(ennemis, bateau);
                    }
                }
                else if (manche->numero >=41)
                {
                    if(rand()%(manche->numero)<10)
                    {
                        bateau = BateauConstructeur(puissance,2,25,vie,vie,1,0,x,y,manche->zodiac);
                        EnnemisAjouterBateau(ennemis, bateau);
                    }
                    else if (rand()%(manche->numero)<30 && rand()%(manche->numero)>=10)
                    {
                        bateau = BateauConstructeur(puissance/2,2,50,vie/2,vie/2,2,0,x,y,manche->vedette);
                        EnnemisAjouterBateau(ennemis, bateau);
                    }
                    else
                    {
                        bateau = BateauConstructeur(puissance*5,4,1,vie*2,vie*2,0,0,x,y,manche->requin);
                        EnnemisAjouterBateau(ennemis, bateau);
                    }
                }
            }
        }
    }
    else
    {
        if (manche->numero ==9)
        {
            Bateau * bateau = BateauConstructeur(25,2,25,700,700,3,3,54,32,manche->somalien);
            EnnemisAjouterBateau(ennemis, bateau);
            (manche->numero)++;
        }
        else if (manche->numero ==19)
        {
            Bateau * bateau = BateauConstructeur(50,2,30,1100,1100,3,3,54,32,manche->genevaux);
            EnnemisAjouterBateau(ennemis, bateau);
            (manche->numero)++;
        }
        else if (manche->numero ==29)
        {
            Bateau * bateau = BateauConstructeur(75,2,35,1600,1600,3,3,54,32,manche->mille);
            EnnemisAjouterBateau(ennemis, bateau);
            (manche->numero)++;
        }
        else if (manche->numero ==39)
        {
            Bateau * bateau = BateauConstructeur(100,2,40,2300,2300,3,3,54,32,manche->meyer);
            EnnemisAjouterBateau(ennemis, bateau);
            (manche->numero)++;
        }
        else if (manche->numero ==49)
        {
            Bateau * bateau = BateauConstructeur(150,2,50,4000,4000,3,3,54,32,manche->poutine);
            EnnemisAjouterBateau(ennemis, bateau);
            (manche->numero)++;
        }
    }
}

unsigned char MancheGetNumero(const Manche * manche)
{
    assert(manche);
    return manche->numero;
}

unsigned char MancheIARequin(Ennemis * ennemis, Bateau * bateau, Terrain * terrain,
                             const unsigned char xJoueur, const unsigned char yJoueur)
{
    assert(bateau);

    unsigned char x, y, portee;
    Position p;
    int xAvant , yAvant;

    xAvant=PositionGetX(BateauGetPosition(bateau));
    yAvant=PositionGetY(BateauGetPosition(bateau));

    p = BateauGetPositionMilieu(bateau);
    /* Voilà les position du bateau */
    x = PositionGetX(&p);
    y = PositionGetY(&p);

    portee = BateauGetPortee(bateau)+(SpriteGetY(BateauGetAspect(bateau))/2);

    if (abs(x-xJoueur)== abs(y-yJoueur)) /* le joueur est sur une des diagonales */
    {

        if((x-xJoueur >0) &&(y-yJoueur >0)) /*diagonale gauche haute */
        {
            if(x-xJoueur < portee)/* Il est à portée */
            {
                while (BateauGetDirection(bateau) != 7 &&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=7)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else /* Le bateau n'est pas à portée*/
            {
                while (BateauGetDirection(bateau) != 7&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=7)
                {
                    return 0;
                }
                else
                {
                    BateauAvancer(bateau,ennemis,terrain);
                    return 0;
                }
            }
        }
        if ((x-xJoueur > 0)&& (y-yJoueur < 0)) /* diagonale gauche basse*/
        {
            if(x-xJoueur < portee)/*il est à portée*/
            {
                while (BateauGetDirection(bateau) != 5&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=5)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                while (BateauGetDirection(bateau) != 5&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=5)
                {
                    return 0;
                }
                else
                {
                    BateauAvancer(bateau,ennemis,terrain);
                    return 0;
                }
            }
        }
        if((x-xJoueur)< 0 && (y-yJoueur)> 0) /*diagonale haute droite*/
        {
            if(abs(x-xJoueur) < portee)/*il est à portée*/
            {
                while (BateauGetDirection(bateau) != 1&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                while (BateauGetDirection(bateau) != 1&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=1)
                {
                    return 0;
                }
                else
                {
                    BateauAvancer(bateau,ennemis,terrain);
                    return 0;
                }
            }
        }
        if((x-xJoueur)< 0 && (y-yJoueur)< 0)/*diagonale basse droite*/
        {
            if((abs(x-xJoueur)) < portee)/*il est à portée*/
            {
                while (BateauGetDirection(bateau) != 3&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=3)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                while (BateauGetDirection(bateau) != 3&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=3)
                {
                    return 0;
                }
                else
                {
                    BateauAvancer(bateau,ennemis,terrain);
                    return 0;
                }
            }
        }
    }
    else/* Le joueur n'est pas en diagonale avec un pirate*/
        /*On va donc vérifier si ils sont alignés selon x ou y*/
    {
        if((x-xJoueur == 0)&& ((y-yJoueur) > 0) )/* Le joueur est à la verticale haute */
        {
            if(y-yJoueur < portee)/*il est à portée*/
            {
                while(BateauGetDirection(bateau) != 0&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=0)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                while (BateauGetDirection(bateau) != 0&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=0)
                {
                    return 0;
                }
                else
                {
                    BateauAvancer(bateau,ennemis,terrain);
                    return 0;
                }
            }
        }
        if((x-xJoueur == 0) && ((y-yJoueur) < 0) )/* Le joueur est à la verticale basse */
        {
            if(abs(y-yJoueur) < portee)/*il est à portée*/
            {
                while (BateauGetDirection(bateau) != 4&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=4)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                while (BateauGetDirection(bateau) != 4&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=4)
                {
                    return 0;
                }
                else
                {
                    BateauAvancer(bateau,ennemis,terrain);
                    return 0;
                }
            }
        }
        if ((x-xJoueur < 0)&& ((y-yJoueur) == 0) )/*Aligné horizontalement droit */
        {
            if(abs(x-xJoueur) < portee)/*il est à portée*/
            {
                while (BateauGetDirection(bateau) != 2&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=2)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                while (BateauGetDirection(bateau) != 2&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=2)
                {
                    return 0;
                }
                else
                {
                    BateauAvancer(bateau,ennemis,terrain);
                    return 0;
                }
            }
        }
        if ((x-xJoueur > 0) && ((y-yJoueur) == 0)) /* Aligné horizontalement gauche */
        {
            if(abs(x-xJoueur) < portee) /*il est à portée*/
            {
                while (BateauGetDirection(bateau) != 6&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=6)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                while (BateauGetDirection(bateau) != 6&&BateauTournerGauche(bateau, ennemis, terrain)==1)
                {
                    ;
                }
                if(BateauGetDirection(bateau)!=6)
                {
                    return 0;
                }
                else
                {
                    BateauAvancer(bateau,ennemis,terrain);
                    return 0;
                }
            }
        }
    }
    /* ICI le pirate n'est ni aligné, ni en diagonale, on va donc faire en sorte qu'il s'aligne avec le joueur */
    if ((x-xJoueur) < 0 && ((y-yJoueur) < 0)) /* Il est en bas à droite */
    {
        while (BateauGetDirection(bateau) != 3&&BateauTournerGauche(bateau, ennemis, terrain)==1)
        {
            ;
        }
        if (TerrainGetCase(terrain,xAvant+1,yAvant+1)=='0')
        {
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
        if(TerrainGetCase(terrain,xAvant+1,yAvant-1)=='0')
        {
            while( BateauGetDirection(bateau) != 2 && BateauTournerDroite(bateau, ennemis, terrain)== 1 );
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
        if(TerrainGetCase(terrain,xAvant-1,yAvant+1)=='0')
        {
            while (BateauGetDirection(bateau) != 4 && BateauTournerGauche(bateau, ennemis, terrain)==1)
            {
                ;
            }
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
    }
    else if((x-xJoueur) >0 && ((y-yJoueur) < 0)) /* Il est en bas à gauche*/
    {
        while (BateauGetDirection(bateau) != 5&&BateauTournerGauche(bateau, ennemis, terrain)==1)
        {
            ;
        }
        if (TerrainGetCase(terrain,xAvant-1,yAvant+1)=='0')
        {
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
        if(TerrainGetCase(terrain,xAvant-1,yAvant-1)=='0')
        {
            while (BateauGetDirection(bateau) != 6&&BateauTournerDroite(bateau, ennemis, terrain)==1)
            {
                ;
            }
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
        if(TerrainGetCase(terrain,xAvant+1,yAvant+1)=='0')
        {
            while (BateauGetDirection(bateau) != 4&&BateauTournerGauche(bateau, ennemis, terrain)==1)
            {
                ;
            }
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
    }
    else if ((x-xJoueur) < 0 && ((y-yJoueur) >0)) /* Il est en haut à droite*/
    {
        while (BateauGetDirection(bateau) != 1&&BateauTournerGauche(bateau, ennemis, terrain)==1)
        {
            ;
        }
        if (TerrainGetCase(terrain,xAvant+1,yAvant-1)=='0')
        {
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
        if(TerrainGetCase(terrain,xAvant+1,yAvant-1)=='0')
        {
            while (BateauGetDirection(bateau) != 2&&BateauTournerGauche(bateau, ennemis, terrain)==1)
            {
                ;
            }
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
        if(TerrainGetCase(terrain,xAvant-1,yAvant+1)=='0')
        {
            while (BateauGetDirection(bateau) != 0&&BateauTournerDroite(bateau, ennemis, terrain)==1)
            {
                ;
            }
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
    }
    else if ((x-xJoueur) > 0 && ((y-yJoueur) > 0)) /* Il est en haut à gauche*/
    {
        while (BateauGetDirection(bateau) != 7&&BateauTournerGauche(bateau, ennemis, terrain)==1)
        {
            ;
        }
        if (TerrainGetCase(terrain,xAvant-1,yAvant-1)=='0')
        {
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
        if(TerrainGetCase(terrain,xAvant-1,yAvant+1)=='0')
        {
            while (BateauGetDirection(bateau) != 6&&BateauTournerDroite(bateau, ennemis, terrain)==1)
            {
                ;
            }
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
        if(TerrainGetCase(terrain,xAvant+1,yAvant-1)=='0')
        {
            while (BateauGetDirection(bateau) != 0&&BateauTournerGauche(bateau, ennemis, terrain)==1)
            {
                ;
            }
            BateauAvancer(bateau, ennemis, terrain);
            return 0;
        }
    }
    /* aucun des cas de dessus, on renvoie 0.*/
    return 0;
}

unsigned char MancheIANovice(Ennemis * ennemis, Bateau * bateau, Terrain * terrain,
                             const unsigned char xJoueur, const unsigned char yJoueur)
{
    unsigned char x, y, portee;
    Position p;

    assert(bateau);
    assert(ennemis);
    assert(terrain);

    p = BateauGetPositionMilieu(bateau);
    /* Voilà les position du bateau */
    x = PositionGetX(&p);
    y = PositionGetY(&p);

    portee = BateauGetPortee(bateau)+(SpriteGetY(BateauGetAspect(bateau))/2);

    if( abs(x-xJoueur) == abs(y-yJoueur) ) /* le joueur est sur une des diagonales*/
    {
        if( (x-xJoueur >0) && (y-yJoueur >0) ) /* Diagonale gauche haute */
        {
            while( BateauGetDirection(bateau) != 7 && BateauTournerGauche(bateau,ennemis,terrain) == 1 );

            if( BateauGetDirection(bateau) != 7 )
                while( BateauGetDirection(bateau) != 7 && BateauTournerDroite(bateau,ennemis,terrain) == 1 );

            if( x-xJoueur < portee ) /* Il est à portée*/
                return 1;
            else
            {
                BateauAvancer(bateau,ennemis,terrain);
                return 0;
            }
        }
        if( (x-xJoueur > 0) && (y-yJoueur < 0) ) /* Diagonale gauche basse*/
        {
            while( BateauGetDirection(bateau) != 5 && BateauTournerGauche(bateau,ennemis,terrain) == 1 );

            if( BateauGetDirection(bateau) != 5 )
                while( BateauGetDirection(bateau) != 5 && BateauTournerDroite(bateau,ennemis,terrain) == 1 );

            if( x-xJoueur < portee ) /* Il est à portée */
                return 1;
            else
            {
                BateauAvancer(bateau,ennemis,terrain);
                return 0;
            }
        }
        if( (x-xJoueur)< 0 && (y-yJoueur)> 0 ) /*diagonale haute droite*/
        {
            while (BateauGetDirection(bateau) != 1 && BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=1)
                while (BateauGetDirection(bateau) != 1 && BateauTournerDroite(bateau,ennemis,terrain)==1);

            if(abs(x-xJoueur) < portee) /* Il est à portée*/
                return 1;
            else
            {
                BateauAvancer(bateau,ennemis,terrain);
                return 0;
            }
        }
        if((x-xJoueur)< 0 && (y-yJoueur)< 0)/*diagonale basse droite*/
        {
            while (BateauGetDirection(bateau) != 3 &&BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=3)
                while (BateauGetDirection(bateau) != 3&&BateauTournerDroite(bateau,ennemis,terrain)==1)

            if( (abs(x-xJoueur)) < portee )
                return 1;
            else
            {
                BateauAvancer(bateau,ennemis,terrain);
                return 0;
            }
        }
    }
    else/* Le joueur n'est pas en diagonale avec un pirate*/
        /*On va donc vérifier si ils sont alignés selon x ou y*/
    {
        if((x-xJoueur == 0)&& ((y-yJoueur) > 0) )/* Le joueur est à la verticale haute */
        {

            while(BateauGetDirection(bateau) != 0&&BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=0)
                while(BateauGetDirection(bateau) != 0&&BateauTournerDroite(bateau,ennemis,terrain)==1);

            if(y-yJoueur < portee)/*il est à portée*/
                return 1;
            else
            {
                BateauAvancer(bateau,ennemis,terrain);
                return 0;
            }
        }
        if((x-xJoueur == 0) && ((y-yJoueur) < 0) )/* Le joueur est à la verticale basse */
        {
            while (BateauGetDirection(bateau) != 4&&BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=4)
                while (BateauGetDirection(bateau) != 4&&BateauTournerDroite(bateau,ennemis,terrain)==1);

            if(abs(y-yJoueur) < portee)/*il est à portée*/
                return 1;
            else
            {
                BateauAvancer(bateau,ennemis,terrain);
                return 0;
            }
        }
        if ( (x-xJoueur < 0) && ((y-yJoueur) == 0) )/*Aligné horizontalement droit */
        {
            while (BateauGetDirection(bateau) != 2&&BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=2)
                while (BateauGetDirection(bateau) != 2&&BateauTournerDroite(bateau,ennemis,terrain)==1);

            if(abs(x-xJoueur) < portee) /*il est à portée*/
                return 1;
            else
            {
                BateauAvancer(bateau,ennemis,terrain);
                return 0;
            }
        }
        if ((x-xJoueur > 0) && ((y-yJoueur) == 0)) /* Aligné horizontalement gauche */
        {
            while (BateauGetDirection(bateau) != 6&&BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=6)
                while (BateauGetDirection(bateau) != 6&&BateauTournerDroite(bateau,ennemis,terrain)==1);

            if(abs(x-xJoueur) < portee) /*il est à portée*/
                return 1;
            else
            {
                BateauAvancer(bateau,ennemis,terrain);
                return 0;
            }
        }
    }
    /* ICI le pirate n'est ni aligné, ni en diagonale, on va donc faire en sorte qu'il s'aligne avec le joueur */
    /*On va vérifier si il est plus proche en x ou en y afin de l'aligner*/
    if (abs(x-xJoueur) < abs(y-yJoueur)) /* Le joueur est plus proche en x qu'en y */
    {
        if ((x-xJoueur) < 0) /* Il est sur la droite */
        {
            while (BateauGetDirection(bateau) != 2 && BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=2)
                while (BateauGetDirection(bateau) != 2 && BateauTournerDroite(bateau,ennemis,terrain)==1);

            BateauAvancer(bateau,ennemis,terrain);
            return 0;
        }
        else /* Il est sur la gauche ou alors dessus (mais dans ce cas osef)*/
        {
            while (BateauGetDirection(bateau) != 6&&BateauTournerGauche(bateau,ennemis,terrain)==1);
            if(BateauGetDirection(bateau)!=6)
                while (BateauGetDirection(bateau) != 6&&BateauTournerDroite(bateau,ennemis,terrain)==1);

            BateauAvancer(bateau,ennemis,terrain);
            return 0;
        }
    }
    if (abs(y-yJoueur) < abs(x-xJoueur)) /* Le joueur est plus proche en y qu'en x */
    {
        if ((y-yJoueur) < 0) /* Il est en bas */
        {
            while (BateauGetDirection(bateau) != 4&&BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=4)
                while (BateauGetDirection(bateau) != 4&&BateauTournerDroite(bateau,ennemis,terrain)==1);

            BateauAvancer(bateau,ennemis,terrain);
            return 0;
        }
        else /* Il est en haut ou alors dessus (mais dans ce cas osef)*/
        {
            while (BateauGetDirection(bateau) != 0&&BateauTournerGauche(bateau,ennemis,terrain)==1);

            if(BateauGetDirection(bateau)!=0 )
                while (BateauGetDirection(bateau) != 0&&BateauTournerDroite(bateau,ennemis,terrain)==1);

            BateauAvancer(bateau,ennemis,terrain);
            return 0;
        }
    }
    /* aucun des cas de dessus, on renvoie 0.*/
    return 0;
}

unsigned char MancheIA(Ennemis * ennemis, Bateau * bateau, Terrain * terrain,
                       const unsigned char xJoueur, const unsigned char yJoueur)
{
    unsigned char numero = SpriteGetTexture(BateauGetAspect(bateau));
    if(numero >= 6 && numero <= 8) /* Dans le cas de Cap'n Mille */
    {
        if(numero == 8)
            numero = 6;
        else
            ++numero;
        SpriteSetTexture(BateauGetAspect(bateau), numero);
    }
    if(BateauGetTaille(bateau) == 3 || BateauGetTaille(bateau) == 0)
        return MancheIARequin(ennemis,bateau,terrain,xJoueur,yJoueur);
    else
        return MancheIANovice(ennemis,bateau,terrain,xJoueur,yJoueur);
}

void MancheTestRegression()
{
    unsigned char i;
    Sprite ** sprites = (Sprite **) malloc(NOMBRE_SPRITE_ENNEMI*sizeof(Sprite *));

    printf("\n-- Manche Test de regression --\n\n");
    printf("- Constructeur -\n");

    for(i = 0; i < NOMBRE_SPRITE_ENNEMI; ++i)
        sprites[i] = SpriteConstructeur(0,0,0);
    Manche * manche = MancheConstructeur(sprites);

    Ennemis * ennemis = EnnemisInitialiser();

    if(manche != NULL)
       printf("->Constructeur Manche : OK\n");
    else
       printf("/!\\ Constructeur Manche : FAIL\n");
    MancheDebut(manche, ennemis);
    printf("%d\n", EnnemisGetTailleUtilisee(ennemis));
    BateauDestructeur(EnnemisValeurIeme(ennemis, 0));
    BateauDestructeur(EnnemisValeurIeme(ennemis, 1));
    EnnemisSupprimer(ennemis, 0);
    printf("%d\n", EnnemisGetTailleUtilisee(ennemis));
    EnnemisSupprimer(ennemis, 0);
    printf("%d\n", EnnemisGetTailleUtilisee(ennemis));
    printf("- Destructeur de manche -\n");
    MancheDestructeur(manche, ennemis);

    for(i = 0; i < NOMBRE_SPRITE_ENNEMI; ++i)
        SpriteDestructeur(sprites[i]);

    free(sprites);

    EnnemisTestament(ennemis);

    printf("->Destruction confirmee : OK\n");

    printf("-- Manche Fin du test, Merci et a bientot --\n\n");
}
