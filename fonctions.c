#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "fonctions.h"

AFFICHAGE initialisation(CONT h[10][10], int info[10][10]){
	
	AFFICHAGE affich;
	
	int i,j;
	
	affich.ecran = ecran;
	affich.fond = f;
	affich.posFond.x = 0;
	affich.posFond.y = 0;
	
	for (i=0;i<10;i++){
		for (j=0;j<10;j++){
			(h[i][j]).couleur = 0;
			(h[i][j]).dame = 0;
			((affich.posPion)[i][j]).x = (i+1/2)*50;
            ((affich.posPion)[i][j]).y = (j+1/2)*50;
            ((affich.posCadre)[i][j]).x = (i+1/2)*50;
            ((affich.posCadre)[i][j]).y = (j+1/2)*50;
            info[i][j] = 0;

		}
	}
	
	for (i=0;i<5;i++){
		for (j=0;j<2;j++){
			(h[2*i+1][2*j]).couleur = 2;
			(h[2*i][2*j+1]).couleur = 2;
		}
		for (j=3;j<5;j++){
			(h[2*i+1][2*j]).couleur = 1;
			(h[2*i][2*j+1]).couleur = 1;
		}
	}
	
	reactualisation(h,&affich,info);
	
	return affich;
}

void reactualisation(CONT h[10][10],AFFICHAGE *aff,int info[10][10]){
	
	int i,j;
	
	SDL_BlitSurface(aff->fond, NULL, aff->ecran, &(aff->posFond));
	
	for (i=0;i<10;i++){
		for (j=0;j<10;j++){
			
			if ((h[i][j]).couleur == 0){
				(aff->pion)[i][j] = NULL;
			}
			
			if ((h[i][j]).couleur == 1){
				if (j==0){
					h[i][j].dame =1;
				}
				if ((h[i][j]).dame == 0){
					(aff->pion)[i][j] = pb;
				}
				else {
					(aff->pion)[i][j] = db;
				}
				SDL_BlitSurface((aff->pion)[i][j], NULL, aff->ecran, &((aff->posPion)[i][j]));	
            }
            
            if ((h[i][j]).couleur == 2){
				if (j==9){
					h[i][j].dame =1;
				}
				if ((h[i][j]).dame == 0){
					(aff->pion)[i][j] = pn;
				}
				else {
					(aff->pion)[i][j] = dn;
				}
				SDL_BlitSurface((aff->pion)[i][j], NULL, aff->ecran, &((aff->posPion)[i][j]));	
            }
            
			if (info[i][j]==0){
				(aff->cadre)[i][j] = NULL;
			}
            if (info[i][j]==1){
				(aff->cadre)[i][j] = cb;
			}
			if (info[i][j]==2){
				(aff->cadre)[i][j] = cr;
			}
			if (info[i][j]==3){
				(aff->cadre)[i][j] = cv;
			}
			SDL_BlitSurface((aff->cadre)[i][j], NULL, aff->ecran, &((aff->posCadre)[i][j]));	
        }
    }
    
    SDL_Flip(aff->ecran);
    return;
   
}

int ouipion(CONT h[10][10], int *pplayer, int x, int y, int *pQuitter, AFFICHAGE *aff, int *nbcoups, COUP coupspossibles[100], int info[10][10]){
	
	int xx,yy,i,j;
	int nbprises = 0;
	CASE prises[20];
	if (!(*nbcoups)){
		if(!h[x][y].dame){
			majdepion(x,y,*pplayer,info,h);
		}
		else{
			majdepdame(x,y,info,h);
		}
		reactualisation(h,aff,info);
		*pQuitter = ecouteUtilisateur(&xx, &yy);
		if(!*pQuitter){	
			if (*pplayer == 1){	
				if (((h[xx][yy]).couleur==0)&&(yy==y-1)&&(abs(xx-x)==1)){
					deplacement(h,x,y,xx,yy,aff,*pplayer,info);
					*pplayer = 2;
					return(1);
				}
				else if (((h[xx][yy]).couleur==0)&&((h[x][y]).dame==1)&&(abs(xx-x)==abs(yy-y)) && deplacedame(h,x,y,xx,yy) ){
					deplacement(h,x,y,xx,yy,aff,*pplayer,info);
					*pplayer = 2;
					return(1);
				}
				else{
					return(0);
				}
			}
			else{
				if (((h[xx][yy]).couleur==0)&&(yy==y+1)&&(abs(xx-x)==1)){
					deplacement(h,x,y,xx,yy,aff,*pplayer,info);
					*pplayer = 1;
					return(1);
				}
				else if (((h[xx][yy]).couleur==0)&&((h[x][y]).dame==1)&&(abs(xx-x)==abs(yy-y)) && deplacedame(h,x,y,xx,yy) ){
					deplacement(h,x,y,xx,yy,aff,*pplayer,info);
					*pplayer = 1;
					return(1);
				}
				else{
					return(0);
				}	
			}
			info[x][y] = 0;
		}
		else{
			return(1);
		}
	}
	else{
		gardercoups(x,y,nbcoups,coupspossibles);
		while (!(*pQuitter) && !prisesfinies(coupspossibles)){
			xx = 0;
			yy = 0;
			while (!(*pQuitter) && !priseval(xx,yy,*nbcoups,coupspossibles,info)){
				reactualisation(h,aff,info);
				*pQuitter = ecouteUtilisateur(&xx,&yy);
			}
			if(!(*pQuitter)){
				for (i=0;i<10;i++){
					for (j=0;j<10;j++){
						if (info[i][j] == 1){
							info[i][j] = 0;
						}
					}
				}
				prises[nbprises].x = xx;
				prises[nbprises].y = yy;
				nbprises ++;
				info[xx][yy] = 3;
				reactualisation(h,aff,info);
				maj(xx,yy,nbcoups,coupspossibles);
			}
		}
		while (!(*pQuitter) && !posfinpos(xx,yy,*nbcoups,coupspossibles,info)){
			reactualisation(h,aff,info);
			*pQuitter = ecouteUtilisateur(&xx,&yy);
		}
		if(!(*pQuitter)){
			h[xx][yy].couleur = *pplayer;
			h[xx][yy].dame = h[x][y].dame;
			h[x][y].couleur = 0;
			h[x][y].dame = 0;
			for(i=0;i<nbprises;i++){
				h[prises[i].x][prises[i].y].couleur = 0;
				h[prises[i].x][prises[i].y].dame = 0;
			}
			reactualisation(h,aff,info);
		}
		if (*pplayer == 1){
			*pplayer = 2;
		}
		else{
			*pplayer = 1;
		}
		return(1);
	}	
}

void deplacement(CONT h[10][10], int x, int y, int xx, int yy, AFFICHAGE *aff, int player, int  info[10][10]){
	
	(h[xx][yy]).couleur = player;
	(h[x][y]).couleur = 0;
	(h[xx][yy]).dame = (h[x][y]).dame;
	(h[x][y]).dame = 0;
	
	reactualisation(h,aff,info);
	
	return;
}

int presentcase (int x, int y, int nbprises, CASE prises[20]){

	int flag = 0;
	int k = 0;
	while ( k <nbprises && !flag ){
		if ( (prises[k].x==x) && (prises[k].y==y) ){
			flag = 1;
		}
		k++;
	}
	return(flag);
}

void ajoutercoups (int nbajout, int nbbase, COUP ajout[100], COUP base[100]){

	int k;
	for (k=0;k<nbajout;k++){
		base[k+nbbase].posini.x = ajout[k].posini.x;
		base[k+nbbase].posini.y = ajout[k].posini.y;
		base[k+nbbase].posfin.x = ajout[k].posfin.x;
		base[k+nbbase].posfin.y = ajout[k].posfin.y;
		base[k+nbbase].nbprises = ajout[k].nbprises;
		copiecase(ajout[k].nbprises,ajout[k].prises,base[k+nbbase].prises);
	}
	return;
	
}
		
					

void coupossible (CONT h[10][10], int player, int *nbcoups, COUP l[100]){

	int max,i,j;
	max=0;
	*nbcoups = 0;
	for (i=0;i<5;i++){
		for (j=0;j<5;j++){

			if ( (h[2*i+1][2*j]).couleur == player ){
				if ( (h[2*i+1][2*j]).dame ){
					cherchecoupdame (&max,h,2*i+1,2*j,player,nbcoups,l);
				}
				else{
					cherchecoupion (&max,h,2*i+1,2*j,player,nbcoups,l);
				}
			}


			if ( (h[2*i][2*j+1]).couleur == player ){
				if ( (h[2*i][2*j+1]).dame ){
					cherchecoupdame (&max,h,2*i,2*j+1,player,nbcoups,l);
				}
				else{
					cherchecoupion (&max,h,2*i,2*j+1,player,nbcoups,l);
				}
			}
		}
	}
	return;
}

void copiecase (int nbcase, CASE base[20], CASE copie[20]){

	int k;
	for (k=0;k<nbcase;k++){
		copie[k].x = base[k].x;
		copie[k].y = base[k].y;
	}
	return;
}


void copiecoups (int nbcoup, COUP base[100], COUP copie[100]){

	int k;
	for (k=0;k<nbcoup;k++){
		copie[k].posini.x = base[k].posini.x;
		copie[k].posini.y = base[k].posini.y;
		copie[k].posfin.x = base[k].posfin.x;
		copie[k].posfin.y = base[k].posfin.y;
		copie[k].nbprises = base[k].nbprises;
		copiecase(base[k].nbprises,base[k].prises,copie[k].prises);
	}
	return;
}
					
void cherchecoupion (int *max, CONT h[10][10], int i, int j, int player, int *nbcoups, COUP l[100]){

	int maxbis = 0;
	int nbcoupsbis =0;
	COUP lbis[100];
	CASE prises[20];
	consarbrepion(player,h,0,&maxbis,&nbcoupsbis,lbis,i,j,i,j,prises);
	if (maxbis > *max){
		*nbcoups = nbcoupsbis;
		copiecoups(nbcoupsbis,lbis,l);
		*max = maxbis;
	}
	else if (maxbis == *max){
		ajoutercoups(nbcoupsbis,*nbcoups,lbis,l);
		*nbcoups = *nbcoups + nbcoupsbis;
	} 
	return;
}

void consarbrepion (int player, CONT h[10][10], int profondeur, int *maxbis, int *nbcoupsbis, COUP lbis[100], int i, int j, int x, int y, CASE prises[20]){

	int adv,k;
	if ( profondeur > 0 && profondeur >= *maxbis){
		if ( profondeur > *maxbis){
			*nbcoupsbis = 1;
			lbis[0].posini.x = i;
			lbis[0].posini.y = j;
			lbis[0].posfin.x = x;
			lbis[0].posfin.y = y;
			lbis[0].nbprises=profondeur;
			copiecase(profondeur,prises,lbis[0].prises);
			*maxbis = profondeur;
		}
		else{
			lbis[*nbcoupsbis].posini.x = i;			
			lbis[*nbcoupsbis].posini.y = j;
			lbis[*nbcoupsbis].posfin.x = x;
			lbis[*nbcoupsbis].posfin.y = y;
			lbis[*nbcoupsbis].nbprises=profondeur;
			copiecase(profondeur,prises,lbis[*nbcoupsbis].prises);
			*nbcoupsbis = *nbcoupsbis + 1;
		}
	}
	if (player==1){
		adv=2;
	}
	else{
		adv=1;
	}
	for(k=0;k<4;k++){
		if (condirx(k,x) && condiry(k,y) && h[calculdirx(k,x,1)][calculdiry(k,y,1)].couleur == adv && (!(h[calculdirx(k,x,2)][calculdiry(k,y,2)].couleur) || (calculdirx(k,x,2)==i && calculdiry(k,y,2)==j)) && !(presentcase(calculdirx(k,x,1),calculdiry(k,y,1),profondeur,prises))){
			prises[profondeur].x = calculdirx(k,x,1);
			prises[profondeur].y = calculdiry(k,y,1);
			consarbrepion(player,h,profondeur+1,maxbis,nbcoupsbis,lbis,i,j,calculdirx(k,x,2),calculdiry(k,y,2),prises);	
						
						   
		}
	}
	return;
}


void cherchecoupdame (int *max, CONT h[10][10], int i, int j, int player, int *nbcoups, COUP l[100]){
	
	int maxbis = 0;
	int nbcoupsbis =0;
	COUP lbis[100];
	CASE prises[20];
	consarbredame(player,h,0,&maxbis,&nbcoupsbis,lbis,i,j,i,j,prises);
	enleverecur(&nbcoupsbis,lbis);
	if (maxbis > *max){
		*nbcoups = nbcoupsbis;
		copiecoups(nbcoupsbis,lbis,l);
		*max = maxbis;
	}
	else if (maxbis == *max){
		ajoutercoups(nbcoupsbis,*nbcoups,lbis,l);
		*nbcoups = *nbcoups + nbcoupsbis;
	} 
	return;
}

void consarbredame (int player, CONT h[10][10], int profondeur, int *maxbis, int *nbcoupsbis, COUP lbis[100], int i, int j, int x, int y, CASE prises[20]){

	int adv,k,n;
	CASE nouvprise[4];
	int portee[4];
	if ( profondeur > 0 && profondeur >= *maxbis){
		if ( profondeur > *maxbis){
			*nbcoupsbis = 1;
			lbis[0].posini.x = i;
			lbis[0].posini.y = j;
			lbis[0].posfin.x = x;
			lbis[0].posfin.y = y;
			lbis[0].nbprises=profondeur;
			copiecase(profondeur,prises,lbis[0].prises);
			*maxbis = profondeur;
		}
		else{
			lbis[*nbcoupsbis].posini.x = i;			
			lbis[*nbcoupsbis].posini.y = j;
			lbis[*nbcoupsbis].posfin.x = x;
			lbis[*nbcoupsbis].posfin.y = y;
			lbis[*nbcoupsbis].nbprises=profondeur;
			copiecase(profondeur,prises,lbis[*nbcoupsbis].prises);
			*nbcoupsbis = *nbcoupsbis + 1;
		}
	}
	if (player==1){
		adv=2;
	}
	else{
		adv=1;
	}
	for (k=0;k<4;k++){
		if (prisedame(k,x,y,h,&(portee[k]),&(nouvprise[k]),player,i,j) && !(presentcase(nouvprise[k].x,nouvprise[k].y,profondeur,prises))){
			for (n=0;n<(portee[k]);n++){			
				prises[profondeur].x = nouvprise[k].x;
				prises[profondeur].y = nouvprise[k].y;
				consarbredame(player,h,profondeur+1,maxbis,nbcoupsbis,lbis,i,j,calculdirx(k,nouvprise[k].x,n+1),calculdiry(k,nouvprise[k].y,n+1),prises);
			}
	
		}
	}
	return;
}

int condirx (int k,int x){
	if (k==0 || k==3){
		return(x>1);
	}
	else{
		return(x<8);
	}
}

int condiry (int k,int y){
	if (k==0 || k==1){
		return(y>1);
	}
	else{
		return(y<8);
	}
}

int calculdirx (int k, int x, int y){
	if (k==0 || k==3){
		return(x-y);
	}
	else{
		return(x+y);
	}
}

int calculdiry (int k, int x, int y){
	if (k==0 || k==1){
		return(x-y);
	}
	else{
		return(x+y);
	}
}


int prisedame (int k, int x, int y, CONT h[10][10], int *portee, PCASE prise, int player, int xini, int yini){

	int i,j;
	*portee = 0;
	i= calculdirx(k,x,1);
	j= calculdiry(k,y,1);
	while ( i<9 && j<9 && i>0 && j>0 && (!(h[i][j].couleur) || (i==xini && j==yini))){
		i= calculdirx(k,i,1);
		j= calculdiry(k,j,1);
	}
	if (i<=0 || j <= 0 || i>=9 || j>=9 || h[i][j].couleur == player || (h[calculdirx(k,i,1)][calculdiry(k,j,1)].couleur && !(calculdirx(k,i,1)==xini && calculdiry(k,j,1)==yini))){
		return(0);
	}
	else{
		prise->x = i;
		prise->y = j;
		i= calculdirx(k,i,2);
		j= calculdiry(k,j,2);
		*portee = 1;
		while ( i<10 && j<10 && i>=0 && j>=0 && (!(h[i][j].couleur) || (i==xini && j==yini))){
			i= calculdirx(k,i,1);
			j= calculdiry(k,j,1);
			*portee = *portee + 1;
			
		}
		return(1);
	}
}
		

int deplacedame (CONT h[10][10], int x, int y, int xx, int yy){

	int i,j,k,flag;
	flag=1;
	if (xx-x < 0){
		if (yy-y<0){
			k=0;
		}
		else{
			k=3;
		}
	}
	else{
		if (yy-y<0){
			k=1;
		}
		else{
			k=2;
		}
	}
	i=calculdirx(k,x,1);
	j=calculdiry(k,y,1);
	while (i!=xx && flag){
		if (h[i][j].couleur){
			flag=0;
		}
		i=calculdirx(k,i,1);
		j=calculdiry(k,j,1);
	}
	return(flag);
}
		
int departpos(int x, int y, int nbcoups, COUP liste[100], CONT h[10][10], int player){

	int flag = 0;
	int k = 0;
	if (!nbcoups){
		return(h[x][y].couleur == player);
	}
	else{
		while ( k<nbcoups && !flag){
			if (liste[k].posini.x==x && liste[k].posini.y==y){
				flag = 1;
			}
			k++;
		}
	return(flag);
	}
}		
		

void enleverecur (int *nbcoup, COUP l[100]){

	int k;
	COUP copie[100];
	int nbcoupcop=0;
	for (k=0;k<*nbcoup;k++){
		if (!presentcoup(nbcoupcop,l[k],copie)){
			copie[nbcoupcop].posini.x = l[k].posini.x;			
			copie[nbcoupcop].posini.y = l[k].posini.y;
			copie[nbcoupcop].posfin.x = l[k].posfin.x;
			copie[nbcoupcop].posfin.y = l[k].posfin.y;
			copie[nbcoupcop].nbprises = l[k].nbprises;
			copiecase(l[k].nbprises,l[k].prises,copie[nbcoupcop].prises);
			nbcoupcop = nbcoupcop + 1;
		}
	}
	*nbcoup = nbcoupcop;
	copiecoups(nbcoupcop,copie,l);
	return;
}


int presentcoup (int nbcoups, COUP c, COUP l[100]){

	int flag = 0;
	int k = 0;
	while ( k<nbcoups && !flag ){
		if (egalcoup(l[k],c)){
			flag = 1;
		}
		k++;
	}
	return(flag);
}

int egalcoup(COUP c1, COUP c2){
	
	return(c1.posini.x == c2.posini.x &&
	c1.posini.y == c2.posini.y &&
	c1.posfin.x == c2.posfin.x &&
	c1.posfin.y == c2.posfin.y &&
	c1.nbprises == c2.nbprises &&
	egalistcase(c1.nbprises,c1.prises,c2.prises));
}

int egalistcase(int nbcase, CASE l1[20], CASE l2[20]){

	int flag = 1;
	int k = 0;
	while (k<nbcase && flag){	
		if (l1[k].x != l2[k].x || l1[k].y != l2[k].y){
			flag = 0;
		}
		k++;
	}
	return(flag);
}
	
void gardercoups(int x,int y, int *nbcoups, COUP l[100]){	

	int k;
	int nbcoupcop = 0;
	COUP copie[100]; 
	for (k=0;k<*nbcoups;k++){
		if(l[k].posini.x == x && l[k].posini.y == y){
			copie[nbcoupcop].posini.x = l[k].posini.x;			
			copie[nbcoupcop].posini.y = l[k].posini.y;
			copie[nbcoupcop].posfin.x = l[k].posfin.x;
			copie[nbcoupcop].posfin.y = l[k].posfin.y;
			copie[nbcoupcop].nbprises = l[k].nbprises;
			copiecase(l[k].nbprises,l[k].prises,copie[nbcoupcop].prises);
			nbcoupcop = nbcoupcop + 1;
		}
	}
	*nbcoups = nbcoupcop;
	copiecoups(nbcoupcop,copie,l);
	return;
}	


int priseval(int x, int y, int nbcoups, COUP l[100], int info[10][10]){

	int flag = 0;
	int k = 0;
	while (k<nbcoups && !flag){
		if (l[k].prises[0].x==x && l[k].prises[0].y==y){
			flag = 1;
		}
		info[l[k].prises[0].x][l[k].prises[0].y] = 1;
		k++;
	}
	return (flag);
}

int prisesfinies(COUP l[100]){

	return (!(l[0].nbprises));
}

void maj(int x, int y, int *nbcoups, COUP l[100]){
	
	COUP copie[100];
	int nbcoupscop = 0;
	int k,kb;
	for (k=0;k<*nbcoups;k++){
		if (l[k].prises[0].x==x && l[k].prises[0].y==y){
			copie[nbcoupscop].posfin.x = l[k].posfin.x;
			copie[nbcoupscop].posfin.y = l[k].posfin.y;
			copie[nbcoupscop].nbprises = l[k].nbprises - 1;
			for (kb=0;kb<copie[nbcoupscop].nbprises;kb++){
				copie[nbcoupscop].prises[kb].x=l[k].prises[kb+1].x;
				copie[nbcoupscop].prises[kb].y=l[k].prises[kb+1].y;
			}
			nbcoupscop ++;
		}
	}
	*nbcoups = nbcoupscop;
	copiecoups(nbcoupscop,copie,l);
	return;
}

int posfinpos(int x, int y, int nbcoups, COUP l[100], int info[10][10]){

	int flag = 0;
	int k = 0;
	while (k<nbcoups && !flag){
		if (l[k].posfin.x==x && l[k].posfin.y==y){
			flag = 1;
		}
		info[l[k].posfin.x][l[k].posfin.y] = 1;
		k++;
	}
	return(flag);
}

void cons (CONT h[10][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			h[i][j].couleur =0;
			h[i][j].dame =0;
		}
	}
	h[2][9].couleur =1;
	h[2][9].dame =0;
	h[3][6].couleur =2;
	h[3][6].dame =0;
	/*h[3][4].couleur =2;
	h[3][4].dame =0;
	h[1][4].couleur =2;
	h[1][4].dame =0;
	h[1][6].couleur =2;
	h[1][6].dame =0;
	h[0][5].couleur =1;
	h[0][5].dame =0;
	h[2][7].couleur =2;
	h[2][7].dame =0;
	h[5][6].couleur =2;
	h[5][6].dame =0;*/
	return;
}

void majdepion (int x, int y, int player, int info[10][10],CONT h[10][10]){
	
	if (player == 1){
		if (x!=0 && !h[x-1][y-1].couleur){
			info[x-1][y-1] = 1;
		}
		if (x!=9 && !h[x+1][y-1].couleur){
			info[x+1][y-1] = 1;
		}
	}
	if (player == 2){
		if (x!=0 && !h[x-1][y+1].couleur){
			info[x-1][y+1] = 1;
		}
		if (x!=9 && !h[x+1][y+1].couleur){
			info[x+1][y+1] = 1;
		}
	}
}

void majdepdame(int x, int y, int info[10][10], CONT h[10][10]){
	int i,j,k;
	for(k=0;k<4;k++){
		i=calculdirx(k,x,1);
		j=calculdiry(k,y,1);
		while (i>=0 && j>=0 && i<10 && j<10 && !h[i][j].couleur){
			info[i][j] = 1;
			i=calculdirx(k,i,1);
			j=calculdiry(k,j,1);
		}
	}
}

int encorepion(CONT h[10][10], int player){
	int i =0;
	int j = 0;
	int flag = 0;
	while (!flag && j< 5){
		while (!flag && i<5){
			if (h[2*i][2*j+1].couleur == player || h[2*i+1][2*j].couleur == player){
				flag = 1;
			}
			i++;
		}
		i=0;
		j++;
	}
	return flag;
}

int findujeu(CONT h[10][10], int nbcoups, int player){

	int i = 0;
	int j = 0;
	int finjeu = 1;
	if (encorepion(h,player) && !nbcoups){
		while (finjeu && j< 10){
			while (finjeu && i<10){
				if (h[i][j].couleur==player){
					if (h[i][j].dame){
						if (j==9){
							if (i==0){
								finjeu = h[1][8].couleur;
							}
							else{
								finjeu = (h[i+1][8].couleur && h[i-1][8].couleur);
							}
						}
						else if (j == 0){
							if (i==9){
								finjeu = h[8][1].couleur;
							}
							else{
								finjeu = (h[i+1][1].couleur && h[i-1][1].couleur);
							}
						}
						else{
							if (i==0){
								finjeu = (h[1][j+1].couleur && h[1][j-1].couleur);
							}
							else if (i==9){
								finjeu = (h[8][j+1].couleur && h[8][j-1].couleur);
							}
							else{
								finjeu = (h[i-1][j-1].couleur && h[i-1][j+1].couleur && h[i+1][j-1].couleur && h[i+1][j+1].couleur);
							}
						}
					}
					else{
						if (player == 1){
							if (i==9){
								finjeu = h[8][j-1].couleur;
							}
							else if (i==0){
								finjeu = h[1][j-1].couleur;
							}
							else{
								finjeu = (h[i-1][j-1].couleur && h[i+1][j-1].couleur);
							}
						}
						else{
							if (i==9){
								finjeu = h[8][j+1].couleur;
							}
							else if (i==0){
								finjeu = h[1][j+1].couleur;
							}
							else{
								finjeu = (h[i-1][j+1].couleur && h[i+1][j+1].couleur);
							}
						}
					}
				}
				i++;
			}
			i=0;
			j++;
		}
	}
	else if (nbcoups){
		finjeu = 0;
	}
	return finjeu;
}
