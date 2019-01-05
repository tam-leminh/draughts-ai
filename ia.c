#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "fonctions.h"
#include "ia.h"



void ajuster(CONT h[10][10], int player, int *nbcoups, COUP liste[100]){
	
	int i,j,k,x,y;
	if (!(*nbcoups)){
		for (i=0;i<10;i++){
			for (j=0;j<10;j++){
				if (h[i][j].couleur == player){
					
					if (h[i][j].dame){
						for(k=0;k<4;k++){
							x=calculdirx(k,i,1);
							y=calculdiry(k,j,1);
							while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
								liste[*nbcoups].posini.x = i;
								liste[*nbcoups].posini.y = j;
								liste[*nbcoups].posfin.x = x;
								liste[*nbcoups].posfin.y = y;
								liste[*nbcoups].nbprises = 0;
								*nbcoups = *nbcoups +1;
								x=calculdirx(k,x,1);
								y=calculdiry(k,y,1);
							}
						}
					}
					else{
						if (player == 1){
							if (i==0){
								if (!h[1][j-1].couleur){
									liste[*nbcoups].posini.x = 0;
									liste[*nbcoups].posini.y = j;
									liste[*nbcoups].posfin.x = 1;
									liste[*nbcoups].posfin.y = j-1;
									liste[*nbcoups].nbprises = 0;
									*nbcoups = *nbcoups +1;
								}
							}
							else if (i==9){
								if (!h[8][j-1].couleur){
									liste[*nbcoups].posini.x = 9;
									liste[*nbcoups].posini.y = j;
									liste[*nbcoups].posfin.x = 8;
									liste[*nbcoups].posfin.y = j-1;
									liste[*nbcoups].nbprises = 0;
									*nbcoups = *nbcoups +1;
								}
							}
							else{
								if (!h[i-1][j-1].couleur){
									liste[*nbcoups].posini.x = i;
									liste[*nbcoups].posini.y = j;
									liste[*nbcoups].posfin.x = i-1;
									liste[*nbcoups].posfin.y = j-1;
									liste[*nbcoups].nbprises = 0;
									*nbcoups = *nbcoups +1;
								}
								if (!h[i+1][j-1].couleur){
									liste[*nbcoups].posini.x = i;
									liste[*nbcoups].posini.y = j;
									liste[*nbcoups].posfin.x = i+1;
									liste[*nbcoups].posfin.y = j-1;
									liste[*nbcoups].nbprises = 0;
									*nbcoups = *nbcoups +1;
								}
							}
						}
						else{
							if (i==0){	
								if (!h[1][j+1].couleur){
									liste[*nbcoups].posini.x = 0;
									liste[*nbcoups].posini.y = j;
									liste[*nbcoups].posfin.x = 1;
									liste[*nbcoups].posfin.y = j+1;
									liste[*nbcoups].nbprises = 0;
									*nbcoups = *nbcoups +1;
								}
							}
							else if (i==9){
								
								if (!h[8][j+1].couleur){
									liste[*nbcoups].posini.x = 9;
									liste[*nbcoups].posini.y = j;
									liste[*nbcoups].posfin.x = 8;
									liste[*nbcoups].posfin.y = j+1;
									liste[*nbcoups].nbprises = 0;
									*nbcoups = *nbcoups +1;
								}
							}
							else{
								
								if (!h[i-1][j+1].couleur){
									liste[*nbcoups].posini.x = i;
									liste[*nbcoups].posini.y = j;
									liste[*nbcoups].posfin.x = i-1;
									liste[*nbcoups].posfin.y = j+1;
									liste[*nbcoups].nbprises = 0;
									*nbcoups = *nbcoups +1;
								}
								if (!h[i+1][j+1].couleur){
									liste[*nbcoups].posini.x = i;
									liste[*nbcoups].posini.y = j;
									liste[*nbcoups].posfin.x = i+1;
									liste[*nbcoups].posfin.y = j+1;
									liste[*nbcoups].nbprises = 0;
									*nbcoups = *nbcoups +1;
								}
							}
						}
					}
				}
			}
		}
	}
	return;
}
						
void constr (CONT base[10][10], COUP modif, CONT result[10][10], int player){

	int i,j,dame;
	for (i=0;i<10;i++){
		for (j=0;j<10;j++){
			result[i][j].couleur = base[i][j].couleur;
			result[i][j].dame = base[i][j].dame;
		}
	}
	result[modif.posfin.x][modif.posfin.y].couleur  = result[modif.posini.x][modif.posini.y].couleur;
	if (player == 1){
		dame = (modif.posfin.y == 0);
	}
	else{
		dame = (modif.posfin.y == 9);
	}
	result[modif.posfin.x][modif.posfin.y].dame  = (result[modif.posini.x][modif.posini.y].dame || dame);
	result[modif.posini.x][modif.posini.y].couleur = 0;
	result[modif.posini.x][modif.posini.y].dame = 0;
	for (i=0;i<modif.nbprises;i++){
		result[modif.prises[i].x][modif.prises[i].y].couleur = 0;
		result[modif.prises[i].x][modif.prises[i].y].dame = 0;	
	}
	return;
}

int evaluation(CONT h[10][10], int player){
	
	int eval=0;
	int i,j,x,y,k,adv;
	if (player == 1){
		adv = 2;
	}
	else{
		adv=1;
	}
	for (i=1;i<9;i++){
		for (j=1;j<9;j++){
			if(h[i][j].couleur == player){
				if (h[i][j].dame){
					eval = eval + VALDAME;
					for(k=0;k<4;k++){
						x=calculdirx(k,i,1);
						y=calculdiry(k,j,1);
						while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
							eval = eval + MOB;
							x=calculdirx(k,x,1);
							y=calculdiry(k,y,1);
						}
					}
					if (!h[i-1][j-1].couleur){
						eval = eval - COMP;
					}
					if (!h[i-1][j+1].couleur){
						eval = eval - COMP;
					}
					if (!h[i+1][j-1].couleur){
						eval = eval - COMP;
					}
					if (!h[i+1][j+1].couleur){
						eval = eval - COMP;
					}
				}
				else{
					eval = eval + VALPION;
					if (player == 1){
						if (!h[i-1][j-1].couleur){
							eval = eval - COMP + MOB;
						}
						if (!h[i-1][j+1].couleur){
							eval = eval - COMP;
						}
						if (!h[i+1][j-1].couleur){
							eval = eval - COMP + MOB;
						}
						if (!h[i+1][j+1].couleur){
							eval = eval - COMP;
						}
					}
					else{
						if (!h[i-1][j-1].couleur){
							eval = eval - COMP;
						}
						if (!h[i-1][j+1].couleur){
							eval = eval - COMP + MOB;
						}
						if (!h[i+1][j-1].couleur){
							eval = eval - COMP;
						}
						if (!h[i+1][j+1].couleur){
							eval = eval - COMP + MOB;
						}
					}
				}
			}
			else if (h[i][j].couleur){
				if (h[i][j].dame){
					eval = eval - VALDAME;
					for(k=0;k<4;k++){
						x=calculdirx(k,i,1);
						y=calculdiry(k,j,1);
						while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
							eval = eval - MOB;
							x=calculdirx(k,x,1);
							y=calculdiry(k,y,1);
						}
					}
					if (!h[i-1][j-1].couleur){
						eval = eval + COMP;
					}
					if (!h[i-1][j+1].couleur){
						eval = eval + COMP;
					}
					if (!h[i+1][j-1].couleur){
						eval = eval + COMP;
					}
					if (!h[i+1][j+1].couleur){
						eval = eval + COMP;
					}
				}
				else{
					eval = eval - VALPION;
					if (player == 2){
						if (!h[i-1][j-1].couleur){
							eval = eval + COMP - MOB;
						}
						if (!h[i-1][j+1].couleur){
							eval = eval + COMP;
						}
						if (!h[i+1][j-1].couleur){
							eval = eval + COMP - MOB;
						}
						if (!h[i+1][j+1].couleur){
							eval = eval + COMP;
						}
					}
					else{
						if (!h[i-1][j-1].couleur){
							eval = eval + COMP;
						}
						if (!h[i-1][j+1].couleur){
							eval = eval + COMP - MOB;
						}
						if (!h[i+1][j-1].couleur){
							eval = eval + COMP;
						}
						if (!h[i+1][j+1].couleur){
							eval = eval + COMP - MOB;
						}
					}
				}
			}
		}
	}
	for (j=1;j<9;j++){
		if(h[0][j].couleur == player){
			if (h[0][j].dame){
				eval = eval + VALDAME;
				x=calculdirx(1,0,1);
				y=calculdiry(1,j,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval + MOB;
					x=calculdirx(1,x,1);
					y=calculdiry(1,y,1);
				}
				x=calculdirx(2,0,1);
				y=calculdiry(2,j,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval + MOB;
					x=calculdirx(2,x,1);
					y=calculdiry(2,y,1);
				}
				if (!h[1][j-1].couleur){
					eval = eval - COMP;
				}
				if (!h[1][j+1].couleur){
					eval = eval - COMP;
				}
			}
			else{
				eval = eval + VALPION;
				if (player == 1){
					if (!h[1][j-1].couleur){
						eval = eval - COMP + MOB;
					}
					if (!h[1][j+1].couleur){
						eval = eval - COMP;
					}
				}
				else{
					if (!h[1][j-1].couleur){
						eval = eval - COMP;
					}
					if (!h[1][j+1].couleur){
						eval = eval - COMP + MOB;
					}
				}
			}
		}
		else if(h[0][j].couleur){
			if (h[0][j].dame){
				eval = eval - VALDAME;
				x=calculdirx(1,0,1);
				y=calculdiry(1,j,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval - MOB;
					x=calculdirx(1,x,1);
					y=calculdiry(1,y,1);
				}
				x=calculdirx(2,0,1);
				y=calculdiry(2,j,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval - MOB;
					x=calculdirx(2,x,1);
					y=calculdiry(2,y,1);
				}
				if (!h[1][j-1].couleur){
					eval = eval + COMP;
				}
				if (!h[1][j+1].couleur){
					eval = eval + COMP;
				}
			}
			else{
				eval = eval - VALPION;
				if (player == 2){
					if (!h[1][j-1].couleur){
						eval = eval + COMP - MOB;
					}
					if (!h[1][j+1].couleur){
						eval = eval + COMP;
					}
				}
				else{
					if (!h[1][j-1].couleur){
						eval = eval + COMP;
					}
					if (!h[1][j+1].couleur){
						eval = eval + COMP - MOB;
					}
				}
			}
		}
		if(h[9][j].couleur == player){
			if (h[9][j].dame){
				eval = eval + VALDAME;
				x=calculdirx(0,9,1);
				y=calculdiry(0,j,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval + MOB;
					x=calculdirx(0,x,1);
					y=calculdiry(0,y,1);
				}
				x=calculdirx(3,9,1);
				y=calculdiry(3,j,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval + MOB;
					x=calculdirx(3,x,1);
					y=calculdiry(3,y,1);
				}
				if (!h[8][j-1].couleur){
					eval = eval - COMP;
				}
				if (!h[8][j+1].couleur){
					eval = eval - COMP;
				}
			}
			else{
				eval = eval + VALPION;
				if (player == 1){
					if (!h[8][j-1].couleur){
						eval = eval - COMP + MOB;
					}
					if (!h[8][j+1].couleur){
						eval = eval - COMP;
					}
				}
				else{
					if (!h[8][j-1].couleur){
						eval = eval - COMP;
					}
					if (!h[8][j+1].couleur){
						eval = eval - COMP + MOB;
					}
				}
			}
		}
		else if(h[9][j].couleur){
			if (h[9][j].dame){
				eval = eval - VALDAME;
				x=calculdirx(0,9,1);
				y=calculdiry(0,j,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval - MOB;
					x=calculdirx(0,x,1);
					y=calculdiry(0,y,1);
				}
				x=calculdirx(3,9,1);
				y=calculdiry(3,j,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval - MOB;
					x=calculdirx(3,x,1);
					y=calculdiry(3,y,1);
				}
				if (!h[8][j-1].couleur){
					eval = eval + COMP;
				}
				if (!h[8][j+1].couleur){
					eval = eval + COMP;
				}
			}
			else{
				eval = eval - VALPION;
				if (player == 2){
					if (!h[8][j-1].couleur){
						eval = eval + COMP - MOB;
					}
					if (!h[8][j+1].couleur){
						eval = eval + COMP;
					}
				}
				else{
					if (!h[8][j-1].couleur){
						eval = eval + COMP;
					}
					if (!h[8][j+1].couleur){
						eval = eval + COMP - MOB;
					}
				}
			}
		}
	}
	for (i=1;i<9;i++){
		if(h[i][0].couleur == player){
			if (h[i][0].dame){
				eval = eval + VALDAME;
				x=calculdirx(2,i,1);
				y=calculdiry(2,0,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval + MOB;
					x=calculdirx(2,x,1);
					y=calculdiry(2,y,1);
				}
				x=calculdirx(3,i,1);
				y=calculdiry(3,0,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval + MOB;
					x=calculdirx(3,x,1);
					y=calculdiry(3,y,1);
				}
				if (!h[i-1][1].couleur){
					eval = eval - COMP;
				}
				if (!h[i+1][1].couleur){
					eval = eval - COMP;
				}
			}
			else{
				eval = eval + VALPION;
				if (!h[i-1][1].couleur){
					eval = eval - COMP + MOB;
				}
				if (!h[i+1][1].couleur){
					eval = eval - COMP + MOB;
				}
			}
		}
		else if(h[i][0].couleur){
			if (h[i][0].dame){
				eval = eval - VALDAME;
				x=calculdirx(2,i,1);
				y=calculdiry(2,0,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval - MOB;
					x=calculdirx(2,x,1);
					y=calculdiry(2,y,1);
				}
				x=calculdirx(3,i,1);
				y=calculdiry(3,0,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval - MOB;
					x=calculdirx(3,x,1);
					y=calculdiry(3,y,1);
				}
				if (!h[i-1][1].couleur){
					eval = eval + COMP;
				}
				if (!h[i+1][1].couleur){
					eval = eval + COMP;
				}
			}
			else{
				eval = eval - VALPION;
				if (!h[i-1][1].couleur){
					eval = eval + COMP - MOB;
				}
				if (!h[i+1][1].couleur){
					eval = eval + COMP - MOB;
				}
			}
		}
		if(h[i][9].couleur == player){
			if (h[i][9].dame){
				eval = eval + VALDAME;
				x=calculdirx(1,i,1);
				y=calculdiry(1,9,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval + MOB;
					x=calculdirx(1,x,1);
					y=calculdiry(1,y,1);
				}
				x=calculdirx(0,i,1);
				y=calculdiry(0,9,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval + MOB;
					x=calculdirx(0,x,1);
					y=calculdiry(0,y,1);
				}
				if (!h[i-1][8].couleur){
					eval = eval - COMP;
				}
				if (!h[i+1][8].couleur){
					eval = eval - COMP;
				}
			}
			else{
				eval = eval + VALPION;
				if (!h[i-1][8].couleur){
					eval = eval - COMP + MOB;
				}
				if (!h[i+1][8].couleur){
					eval = eval - COMP + MOB;
				}
			}
		}
		else if(h[i][9].couleur){
			if (h[i][9].dame){
				eval = eval - VALDAME;
				x=calculdirx(1,i,1);
				y=calculdiry(1,9,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval - MOB;
					x=calculdirx(1,x,1);
					y=calculdiry(1,y,1);
				}
				x=calculdirx(0,i,1);
				y=calculdiry(0,9,1);
				while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
					eval = eval - MOB;
					x=calculdirx(0,x,1);
					y=calculdiry(0,y,1);
				}
				if (!h[i-1][8].couleur){
					eval = eval + COMP;
				}
				if (!h[i+1][8].couleur){
					eval = eval + COMP;
				}
			}
			else{
				eval = eval - VALPION;
				if (!h[i-1][8].couleur){
					eval = eval + COMP - MOB;
				}
				if (!h[i+1][8].couleur){
					eval = eval + COMP - MOB;
				}
			}
		}
	}
	if(h[0][9].couleur == player){
		if (h[0][9].dame){
			eval = eval + VALDAME;
			x=calculdirx(1,0,1);
			y=calculdiry(1,9,1);
			while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
				eval = eval + MOB;
				x=calculdirx(1,x,1);
				y=calculdiry(1,y,1);
			}
			if (!h[1][8].couleur){
				eval = eval - COMP;
			}
		}
		else{
			eval = eval + VALPION;
			if (!h[1][8].couleur){
				eval = eval - COMP + MOB;
			}
		}	
	}
	else if(h[0][9].couleur){
		if (h[0][9].dame){
			eval = eval - VALDAME;
			x=calculdirx(1,0,1);
			y=calculdiry(1,9,1);
			while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
				eval = eval - MOB;
				x=calculdirx(1,x,1);
				y=calculdiry(1,y,1);
			}
			if (!h[1][8].couleur){
				eval = eval + COMP;
			}
		}
		else{
			eval = eval - VALPION;
			if (!h[1][8].couleur){
				eval = eval + COMP - MOB;
			}
		}	
	}
	if(h[9][0].couleur == player){
		if (h[9][0].dame){
			eval = eval + VALDAME;
			x=calculdirx(3,9,1);
			y=calculdiry(3,0,1);
			while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
				eval = eval + MOB;
				x=calculdirx(3,x,1);
				y=calculdiry(3,y,1);
			}
			if (!h[8][1].couleur){
				eval = eval - COMP;
			}
		}
		else{
			eval = eval + VALPION;
			if (!h[8][1].couleur){
				eval = eval - COMP + MOB;
			}
		}	
	}
	else if(h[9][0].couleur){
		if (h[9][0].dame){
			eval = eval - VALDAME;
			x=calculdirx(3,9,1);
			y=calculdiry(3,0,1);
			while (x<10 && y<10 && x>=0 && y>=0 && !h[x][y].couleur){
				eval = eval - MOB;
				x=calculdirx(3,x,1);
				y=calculdiry(3,y,1);
			}
			if (!h[8][1].couleur){
				eval = eval + COMP;
			}
		}
		else{
			eval = eval - VALPION;
			if (!h[8][1].couleur){
				eval = eval + COMP - MOB;
			}
		}	
	}
	return eval;
}




int minimax (CONT h[10][10], int profondeurmax, int profondeur, int player, PCOUP soluse, int joueur){
	int eval,adv;
	int evalb;
	int nbcoups,k;
	CONT hbis[10][10];
	COUP coupos[100];
	if(player == 1){
		adv = 2;
	}
	else{
		adv = 1;
	}
	if (!profondeur){
		coupossible(h,player,&nbcoups,coupos);
		ajuster(h,player,&nbcoups,coupos);
		if (nbcoups != 1){
			eval = INFININEG;
			for(k=0;k<nbcoups;k++){
				constr(h,coupos[k],hbis,player);
				evalb = minimax(hbis,profondeurmax,profondeur + 1,adv,soluse,joueur);
				if (evalb > eval){
					soluse->posini.x = coupos[k].posini.x;
					soluse->posini.y = coupos[k].posini.y;
					soluse->posfin.x = coupos[k].posfin.x;
					soluse->posfin.y = coupos[k].posfin.y;
					soluse->nbprises = coupos[k].nbprises;
					copiecase(coupos[k].nbprises,coupos[k].prises,soluse->prises);
					eval = evalb;
				}
			}
			return(eval);
		}
		else{
			soluse->posini.x = coupos[0].posini.x;
			soluse->posini.y = coupos[0].posini.y;
			soluse->posfin.x = coupos[0].posfin.x;
			soluse->posfin.y = coupos[0].posfin.y;
			soluse->nbprises = coupos[0].nbprises;
			copiecase(coupos[0].nbprises,coupos[0].prises,soluse->prises);
			return (-10000);
		}
	}
	else if (profondeur == profondeurmax){
		return(horizon(h,player,joueur));
	}
	else{
		coupossible(h,player,&nbcoups,coupos);
		ajuster(h,player,&nbcoups,coupos);
		if (!nbcoups){
			if (player == joueur){
				return(INFININEG+1);
			}
			else{
				return(INFINIPOS);
			}
		}	
		else{
			if (player == joueur){
				eval = INFININEG;
				for (k=0;k<nbcoups;k++){
					constr(h,coupos[k],hbis,player);
					evalb = minimax(hbis,profondeurmax,profondeur + 1,adv,soluse,joueur);
					if (evalb > eval){
						eval = evalb;
					}
				}
				return(eval);
			}
			else{
				eval = INFINIPOS;
				for (k=0;k<nbcoups;k++){
					constr(h,coupos[k],hbis,player);
					evalb = minimax(hbis,profondeurmax,profondeur + 1,adv,soluse,joueur);
					if (evalb < eval){
						eval = evalb;
					}
				}
				return(eval);
			}	
		}
	}
}		
		
int horizon (CONT h[10][10], int player, int joueur){

	int eval,adv,evalb,nbcoups,k;
	CONT hbis[10][10];
	COUP coupos[100];
	if(player == 1){
		adv = 2;
	}
	else{
		adv = 1;
	}
	coupossible(h,player,&nbcoups,coupos);
	if (!nbcoups){
		if (!findujeu(h,0,player)){
			return(evaluation(h,joueur));
		}
		else if (player == joueur){
			return (INFININEG +1);
		}
		else{
			return (INFINIPOS);
		}
	}
	else{
		if (player == joueur){
			eval = INFININEG;
			for (k=0;k<nbcoups;k++){
				constr(h,coupos[k],hbis,player);
				evalb = horizon(hbis,adv,joueur);
				if (evalb > eval){
					eval = evalb;
				}
			}
			return(eval);
		}
		else{
			eval = INFINIPOS;
			for (k=0;k<nbcoups;k++){
				constr(h,coupos[k],hbis,player);
				evalb = horizon(hbis,adv,joueur);
				if (evalb < eval){
					eval = evalb;
				}
			}
			return(eval);
		}
	}
}	


int alphabeta (CONT h[10][10], int profondeurmax, int profondeur, int player, PCOUP soluse, int joueur, int alpha, int beta){
	int eval,adv,nbcoups;
	int alphab = alpha;
	int betab = beta;
	int k=0;
	CONT hbis[10][10];
	COUP coupos[100];
	if(player == 1){
		adv = 2;
	}
	else{
		adv = 1;
	}
	if (!profondeur){
		coupossible(h,player,&nbcoups,coupos);
		ajuster(h,player,&nbcoups,coupos);
		if (nbcoups != 1){
			while (alphab < betab && k<nbcoups){
				constr(h,coupos[k],hbis,player);
				eval = alphabeta(hbis,profondeurmax,profondeur + 1,adv,soluse,joueur,alphab,betab);
				if (eval > alphab){
					soluse->posini.x = coupos[k].posini.x;
					soluse->posini.y = coupos[k].posini.y;
					soluse->posfin.x = coupos[k].posfin.x;
					soluse->posfin.y = coupos[k].posfin.y;
					soluse->nbprises = coupos[k].nbprises;
					copiecase(coupos[k].nbprises,coupos[k].prises,soluse->prises);
					alphab = eval;
				}
				k++;
			}
			return(alphab);
		}
		else{
			soluse->posini.x = coupos[0].posini.x;
			soluse->posini.y = coupos[0].posini.y;
			soluse->posfin.x = coupos[0].posfin.x;
			soluse->posfin.y = coupos[0].posfin.y;
			soluse->nbprises = coupos[0].nbprises;
			copiecase(coupos[0].nbprises,coupos[0].prises,soluse->prises);
			return (-10000);
		}
	}
	else if (profondeur == profondeurmax){
		return(horizon(h,player,joueur));
	}
	else{
		coupossible(h,player,&nbcoups,coupos);
		ajuster(h,player,&nbcoups,coupos);
		if (!nbcoups){
			if (player == joueur){
				return(INFININEG+1);
			}
			else{
				return(INFINIPOS);
			}
		}	
		else{
			if (player == joueur){
				while (alphab < betab && k < nbcoups){
					constr(h,coupos[k],hbis,player);
					eval = alphabeta(hbis,profondeurmax,profondeur + 1,adv,soluse,joueur,alphab,betab);
					if (eval > alphab){
						alphab = eval;
					}
					k++;
				}
				return(alphab);
			}
			else{
				
				while (alphab < betab && k < nbcoups){
					constr(h,coupos[k],hbis,player);
					eval = alphabeta(hbis,profondeurmax,profondeur + 1,adv,soluse,joueur,alphab,betab);
					if (eval < betab){
						betab = eval;
					}
					k++;
				}
				return(betab);
			}	
		}
	}
}		




		
