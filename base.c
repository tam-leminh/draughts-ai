#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "fonctions.h"
#include "ia.h"

int main(void) {
	
	int Quitter = 0;
	int x = 0;
	int y = 0;
	int i;
	int j;
	int coup,eval;	
	CONT h[10][10];
	int info[10][10];
	int nbplayer = 0;
	int couleur = 0;
	/* player=1 : tour des blancs
	 * player=2 : tour des noirs */
	int player = 1;
	int nbcoups = 0;
	AFFICHAGE affich;
	COUP coupspossibles[100];
	COUP coupia;
	initSDL();
	affich.ecran = ecran;
	affich.posFond.x = 0;
	affich.posFond.y = 0;
	SDL_BlitSurface(menunb, NULL, affich.ecran, &(affich.posFond));
	SDL_Flip(affich.ecran);
	while (!Quitter && !nbplayer){
		Quitter = ecouteUtilisateur(&x, &y);
		if (x<8 && x>1 && y>2 && y<5){
			nbplayer = 1;
		}
		else if (x<8 && x>1 && y>4 && y<7){
			nbplayer = 2;
		}
	}
	if (nbplayer == 1){
		SDL_BlitSurface(menucoul, NULL, affich.ecran, &(affich.posFond));
		SDL_Flip(affich.ecran);
		while (!Quitter && !couleur){
			Quitter = ecouteUtilisateur(&x, &y);
			if (x<8 && x>1 && y>2 && y<5){
				couleur = 1;
			}
			else if (x<8 && x>1 && y>4 && y<7){
				couleur = 2;
			}
		}
	}	
	player = 1;
	affich = initialisation(h,info);
	/*cons(h);*/
	reactualisation(h,&affich,info);
	x = 0;
	y = 0;
	if (nbplayer == 2){
		while (!Quitter){
			coupossible (h,player,&nbcoups,coupspossibles);
			Quitter = findujeu(h,nbcoups,player);
			coup = 0;
			while (!coup && !Quitter){
				for (i=0;i<10;i++){
					for (j=0;j<10;j++){
						info[i][j] = 0;
					}
				}
				reactualisation(h,&affich,info);
				Quitter = ecouteUtilisateur(&x, &y);
				info[x][y] = 2;
				reactualisation(h,&affich,info);
				if (!Quitter && departpos(x,y,nbcoups,coupspossibles,h,player)){
					coup = ouipion(h,&player,x,y,&Quitter,&affich,&nbcoups,coupspossibles,info);
				}
			}
		}
	}
	else if (nbplayer == 1 && couleur == 1){
		while (!Quitter){
			if(player ==1){
				coupossible (h,player,&nbcoups,coupspossibles);
				Quitter = findujeu(h,nbcoups,player);
				if (Quitter){
					printf("l'ordi a gagne\n");
				}
				coup = 0;
				while (!coup && !Quitter){
					Quitter = ecouteUtilisateur(&x, &y);
					for (i=0;i<10;i++){
						for (j=0;j<10;j++){
							info[i][j] = 0;
						}
					}	
					info[x][y] = 2;
					reactualisation(h,&affich,info);
					if (!Quitter && departpos(x,y,nbcoups,coupspossibles,h,player)){
						coup = ouipion(h,&player,x,y,&Quitter,&affich,&nbcoups,coupspossibles,info);
					}
					for (i=0;i<10;i++){
						for (j=0;j<10;j++){
							info[i][j] = 0;
						}
					}
					reactualisation(h,&affich,info);				
				}
			}
			if(!Quitter && player == 2){
				coupossible (h,player,&nbcoups,coupspossibles);
				Quitter = findujeu(h,nbcoups,player);
				if (Quitter){
					printf("tu as gagne\n");
				}
				else{
					eval = /*minimax(h,PROFONDEURMAX,0,player,&coupia,player)*/alphabeta(h,PROFONDEURMAX,0,player,&coupia,player,INFININEG,INFINIPOS);
					printf("evaluation de l'ia : %d\n",eval);
					info[coupia.posini.x][coupia.posini.y] = 2;
					info[coupia.posfin.x][coupia.posfin.y] = 1;
					for(i=0;i<coupia.nbprises;i++){
						info[coupia.prises[i].x][coupia.prises[i].y]=3;
					}
					constr(h,coupia,h,player);
					reactualisation(h,&affich,info);
					player = 1;
				}
			}		
		}
	}
	else if (nbplayer == 1 && couleur == 2){		
		while (!Quitter){
			if(player ==2){
				coupossible (h,player,&nbcoups,coupspossibles);
				Quitter = findujeu(h,nbcoups,player);
				if (Quitter){
					printf("l'ordi a gagne\n");
				}
				coup = 0;
				while (!coup && !Quitter){
					Quitter = ecouteUtilisateur(&x, &y);
					for (i=0;i<10;i++){
						for (j=0;j<10;j++){
							info[i][j] = 0;
						}
					}	
					info[x][y] = 2;
					reactualisation(h,&affich,info);
					if (!Quitter && departpos(x,y,nbcoups,coupspossibles,h,player)){
						coup = ouipion(h,&player,x,y,&Quitter,&affich,&nbcoups,coupspossibles,info);
					}
					for (i=0;i<10;i++){
						for (j=0;j<10;j++){
							info[i][j] = 0;
						}
					}	
					reactualisation(h,&affich,info);			
				}
			}
			if(!Quitter && player == 1){
				coupossible (h,player,&nbcoups,coupspossibles);
				Quitter = findujeu(h,nbcoups,player);
				if (Quitter){
					printf("tu as gagne\n");
				}
				else{
					eval = /*minimax(h,PROFONDEURMAX,0,player,&coupia,player)*/alphabeta(h,PROFONDEURMAX,0,player,&coupia,player,INFININEG,INFINIPOS);
					printf("evaluation de l'ia : %d\n",eval);
					info[coupia.posini.x][coupia.posini.y] = 2;
					info[coupia.posfin.x][coupia.posfin.y] = 1;
					for(i=0;i<coupia.nbprises;i++){
						info[coupia.prises[i].x][coupia.prises[i].y]=3;
					}
					constr(h,coupia,h,player);
					reactualisation(h,&affich,info);
					player = 2;
				}
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
	menunb = IMG_Load("images/menu_principal.jpg");
	menucoul = IMG_Load("images/menu_1j.jpg");
	
	return;
}

void closeSDL(void){

	/* Libération des surfaces */
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(f);
	SDL_FreeSurface(pn);
	SDL_FreeSurface(pb);
	SDL_FreeSurface(db);
	SDL_FreeSurface(dn);
	SDL_FreeSurface(cb);
	SDL_FreeSurface(cr);
	SDL_FreeSurface(cv);
	SDL_FreeSurface(menunb);
	SDL_FreeSurface(menucoul);
	
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

