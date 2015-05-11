#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "TableauDynamiqueTir.h"
#include "Tir.h"

unsigned short TirsGetCapacite(const Tirs * tableau)
{
    assert(tableau);
    return tableau->capacite;
}

unsigned short TirsGetTailleUtilisee(const Tirs * tableau)
{
    assert(tableau);
    return tableau->taille_utilisee;
}

Tir ** TirsGetAdresse(const Tirs * tableau)
{
    assert(tableau);
    return tableau->adresse;
}

void TirsSetCapacite(Tirs * tableau, unsigned short capacite)
{
    assert(tableau);
    tableau->capacite = capacite;
}

void TirsSetTailleUtilisee(Tirs * tableau, unsigned short taille)
{
    assert(tableau);
    tableau->taille_utilisee = taille;
}

void TirsSetAdresse(Tirs * tableau, Tir ** adresse)
{
    assert(tableau);
    tableau->adresse = adresse;
}

Tirs * TirsInitialiser()
{
    Tirs * tableau = (Tirs *)malloc(sizeof(Tirs));
	tableau->adresse = (Tir **)malloc(sizeof(Tir *));
	tableau->capacite = 1;
	tableau->taille_utilisee = 0;
	return tableau;
}

void TirsTestament(Tirs * tableau)
{
	if(tableau->adresse != NULL)
	{
		free(tableau->adresse);
		tableau->capacite = 0;
		tableau->taille_utilisee = 0;
	}
	free(tableau);
}

void TirsAjouterTir(Tirs * tableau, Tir * e)
{
	if((tableau->taille_utilisee) == (tableau->capacite))
	{
		unsigned short i;
		Tir** temp = tableau->adresse;
		tableau->adresse = (Tir**)malloc(2*(tableau->capacite)*sizeof(Tir*));
		assert(tableau->adresse);
		for(i = 0; i < tableau->capacite; i++)
		{
			tableau->adresse[i] = temp[i];
		}
		tableau->capacite *= 2;
		free(temp);
	}
    tableau->adresse[tableau->taille_utilisee] = e;
	tableau->taille_utilisee++;
}

Tir * TirsValeurIeme(const Tirs * tableau, unsigned short i)
{
	return tableau->adresse[i];
}

void TirsModifierValeurIeme(Tirs * tableau, Tir * e, unsigned short i)
{
	tableau->adresse[i] = e;
}

void TirsSupprimer(Tirs * tableau, unsigned short position)
{
	unsigned short i;

    if(tableau->taille_utilisee != 1)
    {
        for(i = position; i < tableau->taille_utilisee -1; ++i)
        {
            tableau->adresse[i] = tableau->adresse[i+1];
        }
    }
    --tableau->taille_utilisee;
	#ifdef DEBUG
        printf("Taille utilisee : %d Capacite : %d\n", tableau->taille_utilisee, tableau->capacite);
    #endif
}
