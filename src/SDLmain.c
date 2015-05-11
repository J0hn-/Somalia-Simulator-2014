#include <stdio.h>
#include <stdlib.h>
#define _SDL_main_h
#include "SDLjeu.h"

int main (int argc, char** argv)
{
    SDLjeu * sj = SDLjeuInit();
    SDLjeuMenu(sj);
    SDLjeuLibere(sj);
    printf("Fin\n");
	return 0;
}
