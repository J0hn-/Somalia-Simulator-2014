#ifdef WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "testnCurses.h"
#include "Jeu.h"

void nCursesAffichage(WINDOW* win, Jeu * jeu)
{
    unsigned char x, y, pirate, i;
    unsigned short tir;
    Terrain * terrain = JeuGetTerrain(jeu);
    Joueur * joueur = JeuGetJoueur(jeu);
    Bateau * bateau = JoueurGetBateau(joueur);
    Position * position = BateauGetPosition(bateau);
    Position positionSuivante;
    unsigned char texture;
    wclear(win);
    /*
    Place le Terrain
    */

    for(x=0;x<TerrainGetY(terrain);++x)
    {
        for(y=0; y<TerrainGetY(terrain);++y)
        {
            mvwprintw(win, y, x, "%c", TerrainGetCase(terrain,x,y));
        }
    }

    /*
    Place les pirates
    */
    for(pirate = 0; pirate < EnnemisGetTailleUtilisee(JeuGetEnnemis(jeu)); ++pirate)
    {
        x = PositionGetX(BateauGetPosition(EnnemisValeurIeme(JeuGetEnnemis(jeu), pirate)));
        y = PositionGetY(BateauGetPosition(EnnemisValeurIeme(JeuGetEnnemis(jeu), pirate)));
        texture = SpriteGetTexture(BateauGetAspect(EnnemisValeurIeme(JeuGetEnnemis(jeu), pirate)));
        mvwprintw(win, y, x, "%d", texture);
    }
    /*
    Place les tirs
    */

    for(tir=0; tir<(TirsGetTailleUtilisee(JeuGetTirs(jeu))); ++tir)
    {
        y = PositionGetY(TirGetPosition(TirsValeurIeme(JeuGetTirs(jeu),tir)));
        x = PositionGetX(TirGetPosition(TirsValeurIeme(JeuGetTirs(jeu),tir)));
        texture = SpriteGetTexture(TirGetAspect(TirsValeurIeme(JeuGetTirs(jeu),tir)));
        mvwprintw(win, y, x, "%d", texture);
    }
    /*
    Place le joueur
    */

    x = PositionGetX(position);
    y = PositionGetY(position);
    mvwprintw(win, y, x, "o");
    for(i = 1; i < BateauGetTaille(JoueurGetBateau(joueur)); ++i)
    {
        positionSuivante = PositionDirectionSuivante(position, BateauGetDirection(bateau));
        position = &positionSuivante;
        x = PositionGetX(position);
        y = PositionGetY(position);
        mvwprintw(win, y, x, "-");
    }

    wmove(win,0 ,0);

wrefresh(win);
}

void nCursesBoucle(Jeu * jeu)
{
    WINDOW *win;
    float horloge_courante, horloge_precedente;
    float horlogeDebutDeManche, horlogeFinDeManche;
    float intervalle_horloge = 0.1f;
    unsigned char boucle = 1, pauseManche = 3, dephasage = 0;
    char c;
    initscr();
    clear();		/* efface l'écran */
	noecho();
	  	/* Lorsqu'une touche est préssée au clavier, elle n'apparait pas à l'écran */
	cbreak();


    int y = (int) TerrainGetY(JeuGetTerrain(jeu));
    int x = (int) TerrainGetX(JeuGetTerrain(jeu));
    /* Place une fenetre de dimension de celle du terrain */
    win = newwin(y+2, x+2, 5, 5);
    assert(win);
    nodelay(win,1);
    horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;
    nCursesAffichage(win, jeu);

    do
    {
        horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC;

        if (horloge_courante-horloge_precedente>=intervalle_horloge)
        {
            if(pauseManche == 1)
            {
                horlogeFinDeManche = (float)clock()/(float)CLOCKS_PER_SEC;
                pauseManche = 2;
            }
            if(pauseManche == 2)
            {
                horlogeDebutDeManche = (float)clock()/(float)CLOCKS_PER_SEC;
                if(horlogeDebutDeManche-horlogeFinDeManche >= 8)
                    pauseManche = 3;
            }
            JeuEvolution(jeu, &boucle, &pauseManche, &dephasage);
            nCursesAffichage(win, jeu);
            horloge_precedente = horloge_courante;
        }
        c = wgetch(win);
        JeuActionClavier(jeu,c);
        if(c == 'x')
            boucle = 0;
    }while (boucle==1);
    assert(delwin(win)!=ERR);

	endwin();
}

void nCursesTest()
{
initscr();   /* Start curses mode     */
start_color();
        init_pair(1,COLOR_YELLOW,COLOR_BLUE);
        init_pair(2,COLOR_BLUE,COLOR_YELLOW);
        init_pair(3,COLOR_BLUE,COLOR_WHITE);
WINDOW* test = newwin(25, 25, 0, 0);
  if (!test) {
    printw("ERROR with newwin\n." );
    wrefresh(test);
    getch();
  }

	clear();		/* efface l'écran */
	noecho();    	/* Lorsqu'une touche est préssée au clavier, elle n'apparait pasa à l'écran */
	cbreak();		/* un caractère est directement affiché, il ne passe pas dans un buffer */


    wbkgd(test,COLOR_PAIR(1));
    mvwprintw(test,1,1, "Hello World !! (on test window.)\n" );
    wrefresh(test);
    getch();
    delwin(test);
    endwin();





getch();
endwin();

}
