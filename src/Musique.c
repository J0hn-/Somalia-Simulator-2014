#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Musique.h"

Musique * MusiqueConstructeur()
{
    Musique * musique;
    unsigned char i;

    musique = (Musique *) malloc(sizeof(Musique));

    FMOD_System_Create(&musique->systeme);
    FMOD_System_Init(musique->systeme, 64, FMOD_INIT_NORMAL, NULL);

    musique->musiques = (FMOD_SOUND **) malloc(NOMBRE_MUSIQUE * sizeof(FMOD_SOUND *));
    musique->sons = (FMOD_SOUND **) malloc(NOMBRE_MUSIQUE * sizeof(FMOD_SOUND *));

    for(i = 1; i <= NOMBRE_MUSIQUE; i++)
        musique->musiques[i - 1] = MusiqueMusiqueConstructeur(musique->systeme, i);

    for(i = 1; i <= NOMBRE_SON; i++)
        musique->sons[i - 1] = MusiqueSonConstructeur(musique->systeme, i);

    return musique;
}

void MusiqueDestructeur(Musique * musique)
{
    unsigned char i;

    for(i = 1; i <= NOMBRE_MUSIQUE; i++)
        FMOD_Sound_Release(musique->musiques[i-1]);

    for(i = 1; i <= NOMBRE_SON; i++)
        FMOD_Sound_Release(musique->sons[i-1]);

    FMOD_System_Close(musique->systeme);
    FMOD_System_Release(musique->systeme);

    free(musique->musiques);
    free(musique->sons);
    free(musique);
}

void MusiqueSonChoix(Musique * musique , unsigned char nbPiste)
{
    assert(nbPiste <= NOMBRE_SON);

    FMOD_System_PlaySound(musique->systeme, nbPiste + 1, musique->sons[nbPiste - 1], 0, NULL);
}

void MusiqueMusiqueChoix(Musique * musique , unsigned char nbPiste)
{
    assert(nbPiste <= NOMBRE_MUSIQUE);

    FMOD_Sound_SetLoopCount(musique->musiques[nbPiste - 1], -1);
    FMOD_System_PlaySound(musique->systeme, 1, musique->musiques[nbPiste - 1], 0, NULL);
}

FMOD_SOUND * MusiqueSonConstructeur(FMOD_SYSTEM * systeme, unsigned char nbPiste)
{
    FMOD_SOUND * son = NULL;

    assert(nbPiste <= NOMBRE_SON);

    switch(nbPiste)
    {
    case 1:
        /* Objet permettant de gérer le son des tirs */
        FMOD_System_CreateSound(systeme, "data/musique/Fire Boulet.mp3", FMOD_CREATESAMPLE, 0, &son);
        break;
    case 2:
        /* Objet permettant de gérer le son du game over */
        FMOD_System_CreateSound(systeme, "data/musique/GameOverYeah.mp3", FMOD_CREATESAMPLE, 0, &son);
        break;
    case 3:
        /* Objet permettant de gérer le son de debut de manche */
        FMOD_System_CreateSound(systeme, "data/musique/Debut de manche.wma", FMOD_CREATESAMPLE, 0, &son);
        break;
    case 4:
        /* Objet permettant de gérer le son de fin de manche */
        FMOD_System_CreateSound(systeme, "data/musique/Fin de manche.wma", FMOD_CREATESAMPLE, 0,&son);
        break;
    case 5:
        /* Objet permettant de gérer le son d'intro du boss final */
        FMOD_System_CreateSound(systeme, "data/musique/IntroBoss.mp3", FMOD_CREATESAMPLE, 0,&son);
        break;
    default:
        break;
    }

    return son;
}


FMOD_SOUND * MusiqueMusiqueConstructeur(FMOD_SYSTEM * systeme, unsigned char nbPiste)
{
    FMOD_SOUND * musique;

    assert(nbPiste <= NOMBRE_MUSIQUE);

    switch(nbPiste)
    {
    case 1:
        /* Objet permettant de gérer la musique du jeu */
        FMOD_System_CreateSound(systeme, "data/musique/Project SS14.MP3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
        break;
    case 2:
        /* Objet permettant de gérer la musique des boss */
        FMOD_System_CreateSound(systeme, "data/musique/boss.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
        break;
    case 3:
        /* Objet permettant de gérer la musique du menu*/
        FMOD_System_CreateSound(systeme, "data/musique/menu.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
        break;
    case 4:
        /* Objet permettant de gérer la musique après le niveau 50 */
        FMOD_System_CreateSound(systeme, "data/musique/musiquePGM.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
        break;
    case 5:
        /* Objet permettant de gérer la musique du boss final */
        FMOD_System_CreateSound(systeme, "data/musique/Boss Final.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
        break;
    case 6:
        /* Objet permettant de gérer la musique du credit*/
        FMOD_System_CreateSound(systeme, "data/musique/credit.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
        break;
    default:
        break;
    }

    return musique;
}

void MusiqueStop(Musique * musique)
{
    FMOD_CHANNELGROUP *canal;
    FMOD_System_GetMasterChannelGroup(musique->systeme, &canal);
    FMOD_ChannelGroup_Stop(canal);
}
