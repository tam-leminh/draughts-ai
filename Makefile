# Donner le nom du compilateur C
CC=gcc

# Options de chemin de headers
HPATH=-I/usr/include/SDL

# Options compilation
#  1) pour debugger laisser la ligne suivante
#  2) pour optimiser commenter la ligne suivante
#     et "decommenter celle d'apres".
CFLAGS=-g -Wall -pedantic -ansi $(HPATH)
#CFLAGS=-O3 -Wall -pedantic -ansi $(HPATH)

# Les librairies nécessaires à l'édition de lien
# avec les librairies SDL (cf http://www.libsdl.org/)
# SDL        --> fonctionnalites de base
# SDL_mixer  --> pour la gestion du son
# SDL_ttf    --> pour la gestion du texte (polices True Type)
# SDL_image  --> pour la gestion des images
LIBS=-lSDL -lSDL_mixer -lSDL_ttf -lSDL_image

NOM_EXECUTABLE=PIR

# Les règles de compilations
all: $(NOM_EXECUTABLE)

$(NOM_EXECUTABLE) : base.o fonctions.o ia.o
	$(CC) $(CFLAGS) -o $(NOM_EXECUTABLE) base.o fonctions.o ia.o $(LIBS)

base.o: base.c fonctions.c fonctions.h ia.h ia.c
	$(CC) $(CFLAGS) -c base.c

fonctions.o : fonctions.c fonctions.h
	$(CC) $(CFLAGS) -c fonctions.c

ia.o : ia.c fonctions.h ia.h
	$(CC) $(CFLAGS) -c ia.c

baseia.o : baseia.c fonctions.h ia.h
	$(CC) $(CFLAGS) -c baseia.c

clean:
	\rm -f *.o BE

ia : baseia.o fonctions.o ia.o
	$(CC) $(CFLAGS) -o PIRIA baseia.o fonctions.o ia.o $(LIBS)


