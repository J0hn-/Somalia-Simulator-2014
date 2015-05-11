CC=gcc
CFLAGS=-Wall -ggdb -pedantic -m64
EXEC_NAME= ./bin/jeu
LIBS= -L./lib/FMOD/lib/ -L/usr/local/lib -lSDL -lSDL_ttf -lSDL_gfx -lm -lfmodex64 -m64

OBJDIR=obj
SRCDIR=src

OBJ_FILES= $(OBJDIR)/SDLmain.o $(OBJDIR)/SDLjeu.o $(OBJDIR)/Jeu.o $(OBJDIR)/Joueur.o $(OBJDIR)/Terrain.o $(OBJDIR)/Sprite.o $(OBJDIR)/Bateau.o $(OBJDIR)/Position.o $(OBJDIR)/Musique.o $(OBJDIR)/Manche.o $(OBJDIR)/TableauDynamiqueTir.o $(OBJDIR)/TableauDynamiqueEnnemi.o  $(OBJDIR)/Tir.o

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME)  $(LIBS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
clean:
	rm $(OBJ_FILES)
