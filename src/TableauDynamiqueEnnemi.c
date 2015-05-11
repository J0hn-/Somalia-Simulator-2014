#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "TableauDynamiqueEnnemi.h"

unsigned char EnnemisGetCapacite(const Ennemis * tableau)
{
    assert(tableau);
    return tableau->capacite;
}

unsigned char EnnemisGetTailleUtilisee(const Ennemis * tableau)
{
    assert(tableau);
    return tableau->taille_utilisee;
}

Bateau ** EnnemisGetAdresse(const Ennemis * tableau)
{
    assert(tableau);
    return tableau->adresse;
}

void EnnemisSetCapacite(Ennemis * tableau, unsigned char capacite)
{
    assert(tableau);
    tableau->capacite = capacite;
}

void EnnemisSetTailleUtilisee(Ennemis * tableau, unsigned char taille)
{
    assert(tableau);
    tableau->taille_utilisee = taille;
}

void EnnemisSetAdresse(Ennemis * tableau, Bateau ** adresse)
{
    assert(tableau);
    tableau->adresse = adresse;
}

Ennemis * EnnemisInitialiser()
{
    Ennemis * tableau = (Ennemis *)malloc(sizeof(Ennemis));
	tableau->adresse = (Bateau **)malloc(sizeof(Bateau *));
	tableau->capacite = 1;
	tableau->taille_utilisee = 0;
	return tableau;
}

void EnnemisTestament(Ennemis * tableau)
{
	if(tableau->adresse != NULL)
	{
		free(tableau->adresse);
		tableau->capacite = 0;
		tableau->taille_utilisee = 0;
	}
	free(tableau);
}

void EnnemisAjouterBateau(Ennemis * tableau, Bateau * e)
{
	if((tableau->taille_utilisee) == (tableau->capacite))
	{
		unsigned char i;
		Bateau** temp = tableau->adresse;
		tableau->adresse = (Bateau**)malloc(2*(tableau->capacite)*sizeof(Bateau*));
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

Bateau * EnnemisValeurIeme(const Ennemis * tableau, unsigned char i)
{
	return tableau->adresse[i];
}

void EnnemisModifierValeurIeme(Ennemis * tableau, Bateau * e, unsigned char i)
{
	tableau->adresse[i] = e;
}

void EnnemisSupprimer(Ennemis * tableau, unsigned char position)
{
    assert(position < tableau->taille_utilisee);
	unsigned char i;
	if(tableau->taille_utilisee != 1)
    {
        for(i = position; i < tableau->taille_utilisee - 1; ++i)
        {
            tableau->adresse[i] = tableau->adresse[i+1];
        }
    }
    tableau->taille_utilisee = tableau->taille_utilisee - 1;
}
