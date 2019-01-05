#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "fonctions.h"
#include "ia.h"

int main(void) {
	
	int Quitter;
	int x;
	int y;
	int i;
	int j;	
	CONT h[10][10];
	int info[10][10];
	int player,eval;
	int nbcoups = 0;
	AFFICHAGE affich;
	COUP coupspossibles[100];
	COUP coupia;
	initSDL();
	Quitter = 0;
	player = 1;
	affich = initialisation(h,info);
	/*cons(h);*/
	reactualisation(h,&affich,info);
	x = 0;
	y = 0;
	while (!Quitter){
		if(player ==1){
			for (i=0;i<10;i++){
				for (j=0;j<10;j++){
					info[i][j] = 0;
				}
			}
			reactualisation(h,&affich,info);
			coupossible (h,player,&nbcoups,coupspossibles);
			Quitter = findujeu(h,nbcoups,player);
			if (Quitter){
				printf("noir gagne\n");
			}
			else{
				eval = /*minimax(h,PROFONDEURMAX,0,player,&coupia,player) ou*/ alphabeta(h,PROFONDEURMAX,0,player,&coupia,player,INFININEG,INFINIPOS);
				printf("evaluation de l'ia : %d\n",eval);
				info[coupia.posini.x][coupia.posini.y] = 2;
				info[coupia.posfin.x][coupia.posfin.y] = 1;
				for(i=0;i<coupia.nbprises;i++){
					info[coupia.prises[i].x][coupia.prises[i].y]=3;
				}
				reactualisation(h,&affich,info);
				SDL_Delay(100);
				constr(h,coupia,h,2);
				for (i=0;i<10;i++){
					for (j=0;j<10;j++){
						info[i][j] = 0;
					}
				}
				reactualisation(h,&affich,info);
				player = 2;
			}
		}
		if(!Quitter && player == 2){
			for (i=0;i<10;i++){
				for (j=0;j<10;j++){
					info[i][j] = 0;
				}
			}
			reactualisation(h,&affich,info);
			coupossible (h,player,&nbcoups,coupspossibles);
			Quitter = findujeu(h,nbcoups,player);
			if (Quitter){
				printf("blanc gagne\n");
			}
			else{
				eval = /*minimax(h,PROFONDEURMAX,0,player,&coupia,player)*/alphabeta(h,PROFONDEURMAX,0,player,&coupia,player,INFININEG,INFINIPOS);
				printf("evaluation de l'ia : %d\n",eval);
				info[coupia.posini.x][coupia.posini.y] = 2;
				info[coupia.posfin.x][coupia.posfin.y] = 1;
				for(i=0;i<coupia.nbprises;i++){
					info[coupia.prises[i].x][coupia.prises[i].y]=3;
				}
				reactualisation(h,&affich,info);
				SDL_Delay(100);
				constr(h,coupia,h,2);
				for (i=0;i<10;i++){
					for (j=0;j<10;j++){
						info[i][j] = 0;
					}
				}
				reactualisation(h,&affich,info);
				player = 1;
			}
		}		
	}	
	return EXIT_SUCCESS;
}


/**
 * Fonction qui initialise la SDL et tous les objets SDL qui pourront être utiles
 */
void initSDL(void){

    /**************** Préparation de la fenêtre **************/
	/* Démarrage de la SDL (ici : chargement de tous les sous systèmes installés) */
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",
				SDL_GetError()); /* Ecriture de l'erreur */
		exit(EXIT_FAILURE); /* On quitte le programme */
	}

	/* Création de la fenêtre de jeu*/
	ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE
			| SDL_DOUBLEBUF); /* Ouverture de la fenêtre LARGEURxHAUTEUR/32bits en mémoire vidéo, double buffering activé */
	if (!ecran) {
		fprintf(stderr, "Impossible de charger le mode vidéo : %s\n",
				SDL_GetError());
		exit(EXIT_FAILURE);
	}

	/* Ajout d'un titre à la fenêtre */
	SDL_WM_SetCaption("Jeu de Dames by Drouard & Le Minh", NULL);

	/* Chargement des images du jeu */
	f = IMG_Load("images/damier.png");
	pb = IMG_Load("images/pionblanc.png");
	pn = IMG_Load("images/pionnoir.png");
	db = IMG_Load("images/dameblanc.png");
	dn = IMG_Load("images/damenoir.png");
	cb = IMG_Load("images/cadrebleu.png");
	cr = IMG_Load("images/cadrerouge.png");
	cv = IMG_Load("images/cadrevert.png");
	
	return;
}

void closeSDL(void){

	/* Libération des surfaces */
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(f);
	SDL_FreeSurface(pn);
	SDL_FreeSurface(pb);
	
	/* Arrêt de la SDL (libération de la mémoire) */
	SDL_Quit(); 
}

/**
 * Fonction qui attend un événement clavier ou souris et effectue les opérations conséquentes
 * Change la valeur de x et y (coordonnees d'un clic dans la matrice), fait passer retour a 1 si on appuie sur la touche echap
 * @return code de retour suivant :
 * 0 : un événement à été traité, on continue (réaffichage et retour ici)
 * 1 : une demande d'interruption à été reçue, on doit arrêter le programme
 */
int ecouteUtilisateur(int *px, int *py) {

	SDL_Event event; /* Structure de la SDL qui recevra l'événement */

	while (1) {

		/* Gestion des événements souris */
		if (SDL_PollEvent(&event)) { /* un événement clavier ou souris a-t'il eu lieu ? */
			switch (event.type) {
                case SDL_QUIT: /* un clic souris sur le bouton de fermeture de la fenêtre a eu lieu -> on quitte le programme */
                    return 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:/*C'est un clic souris*/
                    if (event.button.button == SDL_BUTTON_LEFT){
						
                        if ((event.button.x>=0)&&(event.button.x<50)){
                            *px=0;
                        }
                        else if ((event.button.x>=50)&&(event.button.x<100)){
                            *px=1;
                        }
                        else if ((event.button.x>=100)&&(event.button.x<150)){
                            *px=2;
                        }
                        else if ((event.button.x>=150)&&(event.button.x<200)){
                            *px=3;
                        }
                        else if ((event.button.x>=200)&&(event.button.x<250)){
                            *px=4;
                        }
                        else if ((event.button.x>=250)&&(event.button.x<300)){
                            *px=5;
                        }
                        else if ((event.button.x>=300)&&(event.button.x<350)){
                            *px=6;
                        }
                        else if ((event.button.x>=350)&&(event.button.x<400)){
                            *px=7;
                        }
                        else if ((event.button.x>=400)&&(event.button.x<450)){
                            *px=8;
                        }
                        else if ((event.button.x>=450)&&(event.button.x<500)){
                            *px=9;
                        }
                        
                        if ((event.button.y>=0)&&(event.button.y<50)){
                            *py=0;
                        }
                        else if ((event.button.y>=50)&&(event.button.y<100)){
                            *py=1;
                        }
                        else if ((event.button.y>=100)&&(event.button.y<150)){
                            *py=2;
                        }
                        else if ((event.button.y>=150)&&(event.button.y<200)){
                            *py=3;
                        }
                        else if ((event.button.y>=200)&&(event.button.y<250)){
                            *py=4;
                        }
                        else if ((event.button.y>=250)&&(event.button.y<300)){
                            *py=5;
                        }
                        else if ((event.button.y>=300)&&(event.button.y<350)){
                            *py=6;
                        }
                        else if ((event.button.y>=350)&&(event.button.y<400)){
                            *py=7;
                        }
                        else if ((event.button.y>=400)&&(event.button.y<450)){
                            *py=8;
                        }
                        else if ((event.button.y>=450)&&(event.button.y<500)){
                            *py=9;
                        }
                        
                        return 0;
                    }
                    break;
                default:
                    ;
		    }
	    }
	}
	return 0; /* Cette ligne n'est jamais atteinte */
}

