#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "SDLjeu.h"
#include "Constantes.h"

SDL_Surface * SDL_load_image(const char* filename);
void SDL_apply_surface(SDL_Surface* source, SDL_Surface* destination, int x, int y);

SDLjeu * SDLjeuInit()
{
    unsigned char i;

    char nomFichier[30];
    char nomFichierBis[30];

    SDL_Surface * surface;

    SDLjeu * sdlJeu = (SDLjeu *)malloc(sizeof(SDLjeu));
    assert(sdlJeu);

	sdlJeu->jeu = JeuConstructeur();

    assert(SDL_Init(SDL_INIT_EVERYTHING) != -1);
	putenv("SDL_VIDEO_WINDOW_POS=center");

	SDL_Surface * icone = SDL_LoadBMP("data/SS14_icone.bmp");

	/* Récupère les informations sur le matériel vidéo actuel */
    const SDL_VideoInfo* myPointer = SDL_GetVideoInfo();

    sdlJeu->largeur = (unsigned short) myPointer->current_w;
    sdlJeu->hauteur = (unsigned short) myPointer->current_h;
    sdlJeu->profondeur = (unsigned char) myPointer->vfmt->BitsPerPixel;

    printf("Chargement d'une fenetre de resolution %d*%d profondeur %d bits\n",
           sdlJeu->largeur, sdlJeu->hauteur, sdlJeu->profondeur);

	if(TTF_Init() == -1)
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());

    SDL_WM_SetCaption("Somalia Simulator 2014", NULL);
	SDL_WM_SetIcon(icone, NULL);

	SDL_FreeSurface(icone);

	/* On enleve le curseur de souris */
    SDL_ShowCursor(0);

    /* Affichage de la fenetre de demarrage */

    sdlJeu->surface_ecran = SDL_SetVideoMode(1200, 675, 32, SDL_SWSURFACE | SDL_NOFRAME);
    assert(sdlJeu->surface_ecran);

    sdlJeu->surface_fond = SDL_load_image("data/SS14.bmp");
	if (sdlJeu->surface_fond == NULL)
		sdlJeu->surface_fond = SDL_load_image("../data/SS14.bmp");
	assert(sdlJeu->surface_fond != NULL);

	SDL_apply_surface(sdlJeu->surface_fond, sdlJeu->surface_ecran, 0, 0);

	SDL_Flip(sdlJeu->surface_ecran);

    SDL_FreeSurface(sdlJeu->surface_fond);

    sdlJeu->police1 = TTF_OpenFont("data/police/game_over.ttf", 78);
    sdlJeu->police2 = TTF_OpenFont("data/police/game_over.ttf", 48);

    sdlJeu->surface_joueur = (SDL_Surface **)malloc(NOMBRE_SPRITE_JOUEUR*sizeof(SDL_Surface *));
    assert(sdlJeu->surface_joueur);
    for(i = 0; i < NOMBRE_SPRITE_JOUEUR; ++i)
    {
        sprintf(nomFichier, "data/joueur/sprite0%d.bmp", i + 1);
        sprintf(nomFichierBis, "../data/joueur/sprite0%d.bmp", i + 1);
        printf("Chargement de %s\n", nomFichier);
        sdlJeu->surface_joueur[i] = SDL_load_image(nomFichier);
        if (sdlJeu->surface_joueur[i] == NULL)
            sdlJeu->surface_joueur[i] = SDL_load_image(nomFichierBis);
        assert(sdlJeu->surface_joueur[i]);
        SDL_SetColorKey(sdlJeu->surface_joueur[i], SDL_SRCCOLORKEY, SDL_MapRGB(sdlJeu->surface_joueur[i]->format, 195, 195, 195));
    }

    sdlJeu->surface_ennemi = (SDL_Surface **)malloc(NOMBRE_SPRITE_ENNEMI*sizeof(SDL_Surface *));
    assert(sdlJeu->surface_ennemi);
    for(i = 0; i < NOMBRE_SPRITE_ENNEMI; ++i)
    {
        sprintf(nomFichier, "data/ennemi/sprite0%d.bmp", i + 1);
        sprintf(nomFichierBis, "../data/ennemi/sprite0%d.bmp", i + 1);
        printf("Chargement de %s\n", nomFichier);
        sdlJeu->surface_ennemi[i] = SDL_load_image(nomFichier);
        if (sdlJeu->surface_ennemi[i] == NULL)
            sdlJeu->surface_ennemi[i] = SDL_load_image(nomFichierBis);
        assert(sdlJeu->surface_ennemi[i] != NULL);
        SDL_SetColorKey(sdlJeu->surface_ennemi[i], SDL_SRCCOLORKEY, SDL_MapRGB(sdlJeu->surface_ennemi[i]->format, 195, 195, 195));
    }

    sdlJeu->surface_tir = (SDL_Surface **)malloc(NOMBRE_SPRITE_TIR*sizeof(SDL_Surface *));
    assert(sdlJeu->surface_tir);
    for(i = 0; i < NOMBRE_SPRITE_TIR; ++i)
    {
        sprintf(nomFichier, "data/tir/sprite%d.bmp", i + 1);
        sprintf(nomFichierBis, "../data/tir/sprite%d.bmp", i + 1);
        printf("Chargement de %s\n", nomFichier);
        sdlJeu->surface_tir[i] = SDL_load_image(nomFichier);
        if (sdlJeu->surface_tir[i] == NULL)
            sdlJeu->surface_tir[i] = SDL_load_image(nomFichierBis);
        assert(sdlJeu->surface_tir[i] != NULL);
    }

    sdlJeu->surface_menu = (SDL_Surface **)malloc(10*sizeof(SDL_Surface *));
    assert(sdlJeu->surface_menu);
    for(i = 0; i < 10; ++i)
    {
        sprintf(nomFichier, "data/menu/Frame0%d.bmp", i);
        sprintf(nomFichierBis, "../data/menu/Frame0%d.bmp", i);
        printf("Chargement de %s\n", nomFichier);
        surface = SDL_load_image(nomFichier);
        if (surface == NULL)
            surface = SDL_load_image(nomFichierBis);
        assert(surface != NULL);

        sdlJeu->surface_menu[i] = SDLjeuRedimentionneImage(sdlJeu, surface);

        SDL_FreeSurface(surface);
    }

    sdlJeu->surface_dialogue = (SDL_Surface **)malloc(7*sizeof(SDL_Surface *));
    assert(sdlJeu->surface_dialogue);
    for(i = 0; i < 7; ++i)
    {
        sprintf(nomFichier, "data/dialogue/Frame%d.bmp", i);
        sprintf(nomFichierBis, "../data/dialogue/Frame%d.bmp", i);
        printf("Chargement de %s\n", nomFichier);
        sdlJeu->surface_dialogue[i] = SDL_load_image(nomFichier);
        if (sdlJeu->surface_dialogue[i] == NULL)
            sdlJeu->surface_dialogue[i] = SDL_load_image(nomFichierBis);
        assert(sdlJeu->surface_dialogue[i]);
    }

    sdlJeu->surface_micro = (SDL_Surface **)malloc(10*sizeof(SDL_Surface *));
    assert(sdlJeu->surface_micro);
    for(i = 0; i < 10; ++i)
    {
        sprintf(nomFichier, "data/bandeau/sprite%d.bmp", i);
        sprintf(nomFichierBis, "../data/bandeau/sprite%d.bmp", i);
        printf("Chargement de %s\n", nomFichier);
        sdlJeu->surface_micro[i] = SDL_load_image(nomFichier);
        if (sdlJeu->surface_micro[i] == NULL)
            sdlJeu->surface_micro[i] = SDL_load_image(nomFichierBis);
        assert(sdlJeu->surface_micro[i]);
    }

    printf("Chargement de data/map.bmp\n");
    sdlJeu->surface_fond = SDL_load_image("data/map.bmp");
	if (sdlJeu->surface_fond == NULL)
		sdlJeu->surface_fond = SDL_load_image("../data/map.bmp");
	assert(sdlJeu->surface_fond != NULL);

	printf("Chargement de data/bandeau/bandeau.bmp\n");
    sdlJeu->surface_bandeau = SDL_load_image("data/bandeau/bandeau.bmp");
	if (sdlJeu->surface_bandeau == NULL)
		sdlJeu->surface_bandeau = SDL_load_image("../data/bandeau/bandeau.bmp");
	assert(sdlJeu->surface_bandeau != NULL);
	SDL_SetColorKey(sdlJeu->surface_bandeau, SDL_SRCCOLORKEY, SDL_MapRGB(sdlJeu->surface_bandeau->format, 0, 0, 0));

    sdlJeu->fichier = fopen("data/data", "r+");

    if (sdlJeu->fichier == NULL) /* Si le jeu est lancé pour la première fois */
    {
        sdlJeu->fichier = fopen("data/data", "w"); /* On creer le fichier de donnees */

        /* Lancement du tutoriel */
        SDLjeuTuto(sdlJeu);
    }

	return sdlJeu;
}

void SDLjeuLibere(SDLjeu * sdlJeu)
{
    unsigned char i;

	SDL_FreeSurface(sdlJeu->surface_fond);
	SDL_FreeSurface(sdlJeu->surface_bandeau);

	for(i = 0; i < NOMBRE_SPRITE_ENNEMI; ++i)
        SDL_FreeSurface(sdlJeu->surface_ennemi[i]);
    for(i = 0; i < NOMBRE_SPRITE_JOUEUR; ++i)
        SDL_FreeSurface(sdlJeu->surface_joueur[i]);
	for(i = 0; i < NOMBRE_SPRITE_TIR; ++i)
        SDL_FreeSurface(sdlJeu->surface_tir[i]);
    for(i = 0; i < 10; ++i)
        SDL_FreeSurface(sdlJeu->surface_menu[i]);
    for(i = 0; i < 7; ++i)
        SDL_FreeSurface(sdlJeu->surface_dialogue[i]);
    for(i = 0; i < 10; ++i)
        SDL_FreeSurface(sdlJeu->surface_micro[i]);

    free(sdlJeu->surface_joueur);
    free(sdlJeu->surface_ennemi);
    free(sdlJeu->surface_tir);
    free(sdlJeu->surface_menu);
    free(sdlJeu->surface_dialogue);

    TTF_CloseFont(sdlJeu->police1);
    TTF_CloseFont(sdlJeu->police2);

    fclose(sdlJeu->fichier);

	JeuDestructeur(sdlJeu->jeu);

    free(sdlJeu);

	SDL_Quit();
	TTF_Quit();
}

void SDLjeuTuto(SDLjeu * sdlJeu)
{
    unsigned char i;
    char nomFichier[40] = "data/instructions/Frame01.bmp";
    char nomFichierBis[40] = "../data/instructions/Frame01.bmp";

    SDL_Surface* surface;
    SDL_Surface* images[9]; /* Il s'agit d'un tampon pour permettre un defilement fluide et sans interruptions */

    /* Configure le mode vidéo */
    sdlJeu->surface_ecran = SDL_SetVideoMode(sdlJeu->largeur, sdlJeu->hauteur, sdlJeu->profondeur, SDL_DOUBLEBUF | SDL_FULLSCREEN);

    surface = SDL_load_image(nomFichier);
    if (surface == NULL)
        surface = SDL_load_image(nomFichierBis);
    assert(surface != NULL);

    images[0] = SDLjeuRedimentionneImage(sdlJeu, surface);

    SDL_FillRect(sdlJeu->surface_ecran, &sdlJeu->surface_ecran->clip_rect, SDL_MapRGB(sdlJeu->surface_ecran->format, 0x00, 0x00, 0x00));
    SDL_apply_surface(images[0], sdlJeu->surface_ecran, 0, (sdlJeu->hauteur - images[0]->h)/2);
    SDL_Flip(sdlJeu->surface_ecran);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(images[0]);

    for(i = 2; i <= 9; ++i)
    {
        sprintf(nomFichier, "data/instructions/Frame0%d.bmp", i);
        sprintf(nomFichierBis, "../data/instructions/Frame0%d.bmp", i);

        surface = SDL_load_image(nomFichier);
        if (surface == NULL)
            surface = SDL_load_image(nomFichierBis);
        assert(surface != NULL);

        images[i - 1] = SDLjeuRedimentionneImage(sdlJeu, surface);

        SDL_FreeSurface(surface);
    }

    for(i = 1; i <= 8; ++i)
    {
        SDL_FillRect(sdlJeu->surface_ecran, &sdlJeu->surface_ecran->clip_rect, SDL_MapRGB(sdlJeu->surface_ecran->format, 0x00, 0x00, 0x00));
        SDL_apply_surface(images[i], sdlJeu->surface_ecran, 0, (sdlJeu->hauteur - images[i]->h)/2);
        SDL_Flip(sdlJeu->surface_ecran);
        SDL_FreeSurface(images[i]);
        SDLjeuPause(60);
    }
}

void SDLjeuCredit(SDLjeu * sdlJeu)
{
    int position = 0;

    /* Horloges (en secondes) */
    float horloge_courante, horloge_precedente;

    SDL_Surface* surface;

    MusiqueMusiqueChoix(JeuGetMusique(sdlJeu->jeu),6);

    /* Configure le mode vidéo */
    sdlJeu->surface_ecran = SDL_SetVideoMode(sdlJeu->largeur, sdlJeu->hauteur, sdlJeu->profondeur, SDL_DOUBLEBUF | SDL_FULLSCREEN);

    surface = SDL_load_image("data/credit/credit.bmp");
    if (surface == NULL)
        surface = SDL_load_image("../data/credit/credit.bmp");
    assert(surface != NULL);

    horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;

    SDL_FillRect(sdlJeu->surface_ecran, &sdlJeu->surface_ecran->clip_rect, SDL_MapRGB(sdlJeu->surface_ecran->format, 0x00, 0x00, 0x00));

    while(position > -8600)
    {
        /* Récupère l'horloge actuelle et la convertit en secondes */
        horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC;

        /* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge */
        if (horloge_courante-horloge_precedente >= 0.01f)
        {
            SDL_apply_surface(surface, sdlJeu->surface_ecran, (sdlJeu->largeur - surface->w)/2, position);
            SDL_Flip(sdlJeu->surface_ecran);
            --position;
            horloge_precedente = horloge_courante;
        }
    }
    SDL_FreeSurface(surface);

    SDLjeuPause(5);

    MusiqueStop(JeuGetMusique(sdlJeu->jeu));
}

void SDLjeuMenu(SDLjeu * sdlJeu)
{
    SDL_Event event;
    unsigned char continuer = 1, i = 0;

    /* Configure le mode vidéo */
    sdlJeu->surface_ecran = SDL_SetVideoMode(sdlJeu->largeur, sdlJeu->hauteur, sdlJeu->profondeur, SDL_DOUBLEBUF | SDL_FULLSCREEN);

    SDL_FillRect(sdlJeu->surface_ecran, &sdlJeu->surface_ecran->clip_rect, SDL_MapRGB(sdlJeu->surface_ecran->format, 0x00, 0x00, 0x00));
    SDL_apply_surface(sdlJeu->surface_menu[0], sdlJeu->surface_ecran, 0, (sdlJeu->hauteur - sdlJeu->surface_menu[0]->h)/2);

    SDL_Flip(sdlJeu->surface_ecran);

    MusiqueMusiqueChoix(JeuGetMusique(sdlJeu->jeu),3);

    while(continuer)
    {
        SDL_WaitEvent(&event);

        if(event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
				case SDLK_UP:
				    if (i != 0)
                        i--;
                    else
                        i = 4;
				    break;
                case SDLK_DOWN:
                    if (i != 4)
                        i++;
                    else
                        i = 0;
                    break;
                case SDLK_SPACE:
                    i = i + 5;
                    break;
                case SDLK_RETURN:
                    i = i + 5;
                    break;
                default:
                    break;
			}
            SDL_FillRect(sdlJeu->surface_ecran, &sdlJeu->surface_ecran->clip_rect, SDL_MapRGB(sdlJeu->surface_ecran->format, 0x00, 0x00, 0x00));
            SDL_apply_surface(sdlJeu->surface_menu[i], sdlJeu->surface_ecran, 0, (sdlJeu->hauteur - sdlJeu->surface_menu[i]->h)/2);

            SDL_Flip(sdlJeu->surface_ecran);
        }
        if(event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE))
        {
            MusiqueStop(JeuGetMusique(sdlJeu->jeu));

            switch(i)
            {
            case 5:
                SDLjeuBoucle(sdlJeu);
                SDLjeuGameOver(sdlJeu);
                continuer = 0;
                /* i = 0; */
                break;
            case 6:
                system("start http://youtu.be/ESHlzvMCG34");
                i = 1;
                break;
            case 7:
                SDLjeuTuto(sdlJeu);
                i = 0;
                break;
            case 8:
                SDLjeuCredit(sdlJeu);
                i= 0;
                break;
            case 9:
                continuer = 0;
                break;
            }
        }
    }
}

void SDLjeuGameOver(SDLjeu * sdlJeu)
{
    SDL_Surface * surface;
    MusiqueStop(JeuGetMusique(sdlJeu->jeu));
    MusiqueSonChoix(JeuGetMusique(sdlJeu->jeu),2);

    surface = SDL_load_image("data/gameover.bmp");
	if (surface == NULL)
		surface = SDL_load_image("../data/gameover.bmp");
	assert(surface != NULL);

	SDL_apply_surface(surface, sdlJeu->surface_ecran, 0, 0);
	SDL_Flip(sdlJeu->surface_ecran);

	SDL_FreeSurface(surface);

    SDLjeuPause(10);
    /*
    JeuDestructeur(sdlJeu->jeu);
    sdlJeu->jeu=JeuConstructeur();
    */
}

void SDLjeuAff(SDLjeu * sdlJeu)
{
	unsigned char x, y, i, aspect;
    SDL_Surface * texte = NULL;
    SDL_Surface * surface = NULL;
    Jeu * jeu = sdlJeu->jeu;
	Joueur * joueur = JeuGetJoueur(jeu);
	Bateau * bateau = JoueurGetBateau(joueur);
	Tir * tir = NULL;
	Position position;
    SDL_Color couleur = {135, 86, 63}, couleurRouge = {255, 0, 0};
    unsigned short vieMax = BateauGetVieMax(bateau), prix;
    unsigned char puissance = BateauGetPuissance(bateau);
    unsigned char portee = BateauGetPortee(bateau);
    unsigned char vitesse = BateauGetVitesse(bateau);
    char blabla[70] = "";

	/* Remplir l'écran de blanc */
	SDL_FillRect(sdlJeu->surface_ecran, &sdlJeu->surface_ecran->clip_rect, SDL_MapRGB(sdlJeu->surface_ecran->format, 0xFF, 0xFF, 0xFF));

	SDL_apply_surface(sdlJeu->surface_fond, sdlJeu->surface_ecran, 0, 0);

	/* Copier le sprite du joueur sur l'écran */
	position = BateauGetHitBoxInferieur(bateau);
	x = PositionGetX(&position);
	y = PositionGetY(&position);
	aspect = SpriteGetTexture(BateauGetAspect(bateau));
    surface = SDLorientation(sdlJeu->surface_joueur[aspect], BateauGetDirection(JoueurGetBateau(joueur)));
	SDL_apply_surface(surface, sdlJeu->surface_ecran, x*TAILLE_CASE, y*TAILLE_CASE);
	SDL_FreeSurface(surface);

    #ifdef DEBUG
	position = BateauGetPositionMilieu(bateau);
	x = PositionGetX(&position);
	y = PositionGetY(&position);
    SDL_apply_surface(sdlJeu->surface_tir[0], sdlJeu->surface_ecran, x*TAILLE_CASE, y*TAILLE_CASE);
    #endif

    for (i = 0; i < EnnemisGetTailleUtilisee(JeuGetEnnemis(jeu)); ++i)
    {
        bateau = EnnemisValeurIeme(JeuGetEnnemis(jeu), i);
        position = BateauGetHitBoxInferieur(bateau);
        x = PositionGetX(&position);
        y = PositionGetY(&position);
        aspect = SpriteGetTexture(BateauGetAspect(bateau));
        surface = SDLorientation(sdlJeu->surface_ennemi[aspect], BateauGetDirection(bateau));
        SDL_apply_surface(surface, sdlJeu->surface_ecran, x*TAILLE_CASE,  y*TAILLE_CASE);
        SDL_FreeSurface(surface);
    }

    for (i = 0; i < TirsGetTailleUtilisee(JeuGetTirs(jeu)); ++i)
    {
        tir = TirsValeurIeme(JeuGetTirs(jeu), i);
        x = PositionGetX(TirGetPosition(tir));
        y = PositionGetY(TirGetPosition(tir));
        aspect = SpriteGetTexture(TirGetAspect(tir));
        surface = SDLorientation(sdlJeu->surface_tir[aspect], TirGetDirection(tir));
        SDL_apply_surface(surface, sdlJeu->surface_ecran, x*TAILLE_CASE, y*TAILLE_CASE);
        SDL_FreeSurface(surface);
    }

    /* Mise en place du bandeau */
    SDL_apply_surface(sdlJeu->surface_bandeau, sdlJeu->surface_ecran, 0, 544);

    /* Application de la zone dynamique */
    switch(MancheGetNumero(JeuGetManche(sdlJeu->jeu)))
    {
    case 10:
        i = 5;
        break;
    case 20:
        i = 6;
        break;
    case 30:
        i = 7;
        break;
    case 40:
        i = 8;
        break;
    case 50:
        i = 9;
        break;
    default:
        i = SpriteGetTexture(BateauGetAspect(JoueurGetBateau(JeuGetJoueur(sdlJeu->jeu))));
        break;
    }
    SDL_apply_surface(sdlJeu->surface_micro[i], sdlJeu->surface_ecran, 1023, 600);

    /* Ecriture du texte */

    bateau = JoueurGetBateau(joueur);

    sprintf(blabla, "Manche %d", MancheGetNumero(JeuGetManche(sdlJeu->jeu)));
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(sdlJeu->police1, blabla, couleur);
    SDL_apply_surface(texte, sdlJeu->surface_ecran, 280, 610);
    SDL_FreeSurface(texte);

    sprintf(blabla, "Vie : %d/%d", BateauGetVie(bateau), vieMax);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    if(BateauGetVie(bateau) <= 50)
        texte = TTF_RenderText_Blended(sdlJeu->police2, blabla, couleurRouge);
    else
        texte = TTF_RenderText_Blended(sdlJeu->police2, blabla, couleur);
    SDL_apply_surface(texte, sdlJeu->surface_ecran, 280, 660);
    SDL_FreeSurface(texte);

    sprintf(blabla, "%d", JoueurGetArgent(joueur));
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(sdlJeu->police1, blabla, couleur);
    SDL_apply_surface(texte, sdlJeu->surface_ecran, 860, 630);
    SDL_FreeSurface(texte);

    prix = vieMax/10+(10*vieMax/100)*vieMax/100;
    sprintf(blabla, "Cout de l'augmentation de vie : %d", prix);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(sdlJeu->police2, blabla, couleur);
    SDL_apply_surface(texte, sdlJeu->surface_ecran, 470, 610);
    SDL_FreeSurface(texte);

    prix = puissance/10+(10*puissance/10)*puissance/10;
    sprintf(blabla, "Cout de l'augmentation de puissance : %d", prix);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(sdlJeu->police2, blabla, couleur);
    SDL_apply_surface(texte, sdlJeu->surface_ecran, 470, 630);
    SDL_FreeSurface(texte);

    prix = (portee%10)*100+portee*portee-20;
    sprintf(blabla, "Cout de l'augmentation de portee : %d", prix);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(sdlJeu->police2, blabla, couleur);
    SDL_apply_surface(texte, sdlJeu->surface_ecran, 470, 650);
    SDL_FreeSurface(texte);

    prix = vitesse*100;
    sprintf(blabla, "Cout de l'augmentation de vitesse : %d", prix);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(sdlJeu->police2, blabla, couleur);
    SDL_apply_surface(texte, sdlJeu->surface_ecran, 470, 670);
    SDL_FreeSurface(texte);
}

void SDLjeuBoucle(SDLjeu * sdlJeu)
{
    SDL_Event event;
	SDLMod mod;
	unsigned char continue_boucle = 1, pause_manche = 3, dephasage = 0, vitesse, dialogue, i;

    /* Horloges (en secondes) */
    float horloge_courante, horloge_precedente;
    float horloge_courante_manche, horloge_precedente_manche;
    float horloge_courante_joueur, horloge_precedente_joueur;

    /* Intervalle de temps (en secondes) entre deux évolutions du jeu */
    /* Changer la valeur pour ralentir ou accélérer le déplacement des fantomes */
    float intervalle_horloge = 0.04f;

    int rafraichissement;

    sdlJeu->surface_ecran = SDL_SetVideoMode(1200, 705, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	assert(sdlJeu->surface_ecran != NULL);

    SDL_EnableKeyRepeat(100,100);

    MusiqueMusiqueChoix(JeuGetMusique(sdlJeu->jeu),1);

	SDLjeuAff(sdlJeu);
	assert(SDL_Flip(sdlJeu->surface_ecran) != -1);

    /* Récupère l'horloge actuelle et la convertit en secondes */
    /* clock() retourne le nombre de tops horloge depuis le lancement du programme */
    horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;
    horloge_precedente_joueur = (float)clock()/(float)CLOCKS_PER_SEC;

	/* Tant que ce n'est pas la fin ... */
	while (continue_boucle == 1)
	{
	    /* Voyons si un dialogue doit s'afficher */
	    switch(MancheGetNumero(JeuGetManche(sdlJeu->jeu)))
	    {
        case 10:
            if(dialogue)
                i = 0;
            break;
        case 20:
            if(dialogue)
                i = 1;
            break;
        case 21:
            if(dialogue)
                i = 2;
            break;
        case 30:
            if(dialogue)
                i = 3;
            break;
        case 40:
            if(dialogue)
                i = 4;
            break;
        case 41:
            if(dialogue)
                i = 5;
            break;
        case 50:
            if(dialogue)
                i = 6;
            break;
        default:
            if(dialogue)
                dialogue = 0;
            break;
	    }
	    if(dialogue)
        {
            SDL_FillRect(sdlJeu->surface_ecran, &sdlJeu->surface_ecran->clip_rect, SDL_MapRGB(sdlJeu->surface_ecran->format, 0x00, 0x00, 0x00));
            SDL_apply_surface(sdlJeu->surface_dialogue[i], sdlJeu->surface_ecran, 200, 50);
            SDL_Flip(sdlJeu->surface_ecran);
            SDLjeuPause(10);
            dialogue = 0;
        }

	    rafraichissement = 0;

	     /* Récupère l'horloge actuelle et la convertit en secondes */
        horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC;

        /* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge */
        if (horloge_courante-horloge_precedente>=intervalle_horloge)
        {
            if(pause_manche == 1)
            {
                horloge_precedente_manche = (float)clock()/(float)CLOCKS_PER_SEC;
                pause_manche = 2;
            }
            if(pause_manche == 2)
            {
                horloge_courante_manche = (float)clock()/(float)CLOCKS_PER_SEC;
                if(MancheGetNumero(JeuGetManche(sdlJeu->jeu)) == 49)
                {
                    /* Temps de pause pour le boss final */
                    if(horloge_courante_manche - horloge_precedente_manche >= 15)
                    {
                        pause_manche = 3;
                        dialogue = 1;
                    }
                }
                else
                {
                    /* Temps de pause entre 2 manches */
                    if(horloge_courante_manche - horloge_precedente_manche >= 9)
                    {
                        pause_manche = 3;
                        dialogue = 1;
                    }
                }
            }
            JeuEvolution(sdlJeu->jeu, &continue_boucle, &pause_manche, &dephasage);
            rafraichissement = 1;
            horloge_precedente = horloge_courante;
        }

		/* tant qu'il y a des evenements à traiter : cette boucle n'est pas bloquante */
		while (SDL_PollEvent(&event))
		{
		    mod = SDL_GetModState();
			/* Si l'utilisateur a cliqué sur la croix de fermeture */
			if (event.type == SDL_QUIT)
				continue_boucle = 0;

			/* Si l'utilisateur a appuyé sur une touche */
			if (event.type == SDL_KEYDOWN)
			{
			    vitesse = BateauGetVitesse(JoueurGetBateau(JeuGetJoueur(sdlJeu->jeu)));
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					JeuActionClavier(sdlJeu->jeu, 'z');
					rafraichissement = 1;
					break;
				case SDLK_DOWN:
					JeuActionClavier(sdlJeu->jeu, 's');
					rafraichissement = 1;
					break;
				case SDLK_LEFT:
					JeuActionClavier(sdlJeu->jeu, 'q');
					rafraichissement = 1;
					break;
				case SDLK_RIGHT:
					JeuActionClavier(sdlJeu->jeu, 'd');
					rafraichissement = 1;
					break;
                case SDLK_SPACE:
                    horloge_courante_joueur = (float)clock()/(float)CLOCKS_PER_SEC;
                    if (horloge_courante_joueur-horloge_precedente_joueur >= (1 - vitesse*0.1))
                    {
                        JeuActionClavier(sdlJeu->jeu, ' ');
                        horloge_precedente_joueur = horloge_courante_joueur;
                        rafraichissement = 1;
                    }
                    break;
                case SDLK_w:
					JeuActionClavier(sdlJeu->jeu, 'z');
					rafraichissement = 1;
					break;
                case SDLK_z:
					JeuActionClavier(sdlJeu->jeu, 'z');
					rafraichissement = 1;
					break;
				case SDLK_s:
					JeuActionClavier(sdlJeu->jeu, 's');
					rafraichissement = 1;
					break;
				case SDLK_a:
                    #ifdef linux
                        JeuActionClavier(sdlJeu->jeu, 'a');
                    #endif
                    #ifdef __WIN32__
                        JeuActionClavier(sdlJeu->jeu, 'q');
                    #endif
					rafraichissement = 1;
					break;
				case SDLK_d:
					JeuActionClavier(sdlJeu->jeu, 'd');
					rafraichissement = 1;
					break;
                case SDLK_q:
					#ifdef linux
                        JeuActionClavier(sdlJeu->jeu, 'q');
                    #endif
                    #ifdef __WIN32__
                        JeuActionClavier(sdlJeu->jeu, 'a');
                    #endif
					rafraichissement = 1;
					break;
                case SDLK_e:
					JeuActionClavier(sdlJeu->jeu, 'e');
					rafraichissement = 1;
					break;
                case SDLK_r:
					JeuActionClavier(sdlJeu->jeu, 'r');
					rafraichissement = 1;
					break;
                case SDLK_t:
					JeuActionClavier(sdlJeu->jeu, 't');
					vitesse = 100 - (10 * vitesse);
                    SDL_EnableKeyRepeat(vitesse,vitesse);
					rafraichissement = 1;
					break;
                case SDLK_x:
                    if((mod & KMOD_CTRL) && (mod & KMOD_ALT))
                        continue_boucle = 0;
                    break;
                case SDLK_j:
                    if((mod & KMOD_CTRL) && (mod & KMOD_ALT))
                        JoueurSetArgent(JeuGetJoueur(sdlJeu->jeu), (unsigned int) -1);
                    break;
                case SDLK_k:
                    if((mod & KMOD_CTRL) && (mod & KMOD_ALT))
                    {
                        while(EnnemisGetTailleUtilisee(JeuGetEnnemis(sdlJeu->jeu)) != 0)
                        {
                            BateauDestructeur(EnnemisValeurIeme(JeuGetEnnemis(sdlJeu->jeu), 0));
                            EnnemisSupprimer(JeuGetEnnemis(sdlJeu->jeu), 0);
                        }
                    }
                    break;
                case SDLK_l:
                    if((mod & KMOD_CTRL) && (mod & KMOD_ALT))
                    {
                        BateauSetVieMax(JoueurGetBateau(JeuGetJoueur(sdlJeu->jeu)), (unsigned short) -1);
                        BateauSetVie(JoueurGetBateau(JeuGetJoueur(sdlJeu->jeu)), (unsigned short) -1);
                        BateauSetPuissance(JoueurGetBateau(JeuGetJoueur(sdlJeu->jeu)), 255);
                        BateauSetPortee(JoueurGetBateau(JeuGetJoueur(sdlJeu->jeu)), 255);
                        BateauSetVitesse(JoueurGetBateau(JeuGetJoueur(sdlJeu->jeu)), 7);
                    }
                    break;
				default: break;
				}
			}
		}

        if (rafraichissement==1)
        {
            /* on affiche le jeu sur le buffer caché */
            SDLjeuAff(sdlJeu);

            /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans a boucle) */
            SDL_Flip(sdlJeu->surface_ecran);
        }
	}
}

SDL_Surface * SDLjeuRedimentionneImage(SDLjeu * sdlJeu, SDL_Surface * surfaceOriginale)
{
    SDL_Surface * surface;
    float rapport;

    rapport = (float) sdlJeu->largeur/surfaceOriginale->w;
    surface = rotozoomSurfaceXY(surfaceOriginale, 0, rapport, rapport, 1);

    return surface;
}

SDL_Surface * SDLorientation(SDL_Surface * surfaceOrigine, unsigned char direction)
{
    int angle;
    SDL_Surface * surface;

    switch(direction)
    {
        case 1:
            angle = 315;
            break;
        case 2:
            angle = 270;
            break;
        case 3:
            angle = 225;
            break;
        case 4:
            angle = 180;
            break;
        case 5:
            angle = 135;
            break;
        case 6:
            angle = 90;
            break;
        case 7:
            angle = 45;
            break;
        default :
            angle = 0;
            break;
    }
    surface = rotozoomSurface(surfaceOrigine, angle, 1.0, 0);
    if(surface != NULL)
    {
        #ifdef linux
            SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 0, 0, 0));
        #endif
        #ifdef __WIN32__
            SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 0, 0, 0));
        #endif
        return surface;
    }
    else return surfaceOrigine;
}

void SDLjeuPause(unsigned char temps)
{
    float horloge_courante, horloge_precedente;
    unsigned char continuer = 1;
    SDL_Event event;

	horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;

    while(continuer)
    {
        horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC;
        SDL_WaitEvent(&event);

        if(event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONUP
           || (horloge_courante - horloge_precedente >= temps))
            continuer = 0;
    }
}

SDL_Surface * SDL_load_image(const char* filename)
{
	/* Temporary storage for the image that's loaded */
	SDL_Surface* loadedImage = NULL;

	/* The optimized image that will be used */
	SDL_Surface* optimizedImage = NULL;

	/* Load the image */
	loadedImage = SDL_LoadBMP( filename );

	/* If nothing went wrong in loading the image */
	if ( loadedImage != NULL )
	{
		/* Create an optimized image */
		optimizedImage = SDL_DisplayFormat( loadedImage );

		/* Free the old image */
		SDL_FreeSurface( loadedImage );
	}

	/* Return the optimized image */
	return optimizedImage;
}

void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y)
{
	/* Make a temporary rectangle to hold the offsets */
	SDL_Rect offset;

	/* Give the offsets to the rectangle */
	offset.x = x;
	offset.y = y;

	/* Blit the surface */
	SDL_BlitSurface(source, NULL, destination, &offset);
}
