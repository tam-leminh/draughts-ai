/* Dimensions de la fenetre */
#define LARGEUR 500
#define HAUTEUR 500

/* Declaration des objets utilises */
SDL_Surface *ecran, *f, *pb, *pn, *db, *dn, *cb, *cr, *cv, *menunb, *menucoul;

/* Une structure contenant les donnees d'affichage et permettant de facilement les
 * passer en parametre à une fonction
 */

struct affichage {
	SDL_Surface *ecran, *pion[10][10], *fond, *cadre[10][10];
	SDL_Rect posPion[10][10], posFond, posCadre[10][10];
};
typedef struct affichage AFFICHAGE;

struct cont {
	int couleur;
	int dame;
};
typedef struct cont CONT;


struct place {
	int x;
	int y;
};
typedef struct place CASE, *PCASE;


/*struct cellcase {
	PCASE place;
	struct cellcase *placesuivante;
};
typedef struct cellcase CELLCASE, *PCELLCASE;


struct listcase {
	PCELLCASE tete;
	PCELLCASE queue;
};
typedef struct listcase LISTCASE, *PLISTCASE;*/


struct coup {
	CASE posini;
	int nbprises;
	CASE prises[20];
	CASE posfin;
};
typedef struct coup COUP, *PCOUP;


/*struct cellcoups {
	PCOUP coup;
	struct cellcoups *coupsuivant;
};
typedef struct cellcoups CELLCOUPS, *PCELLCOUPS;


struct listcoups {
	PCELLCOUPS tete;
	PCELLCOUPS queue;
};
typedef struct listcoups LISTCOUPS, *PLISTCOUPS;

struct arbrepion {
	int profondeur;
	PLISTCASE prises;
	PCASE place;
	struct arbrepion *fils [4]; 0=hg;1=hd;2=bd;3=bg
};
typedef struct arbrepion ARBREPION, *PARBREPION;

struct arbredame {
	int profondeur;
	PLISTCASE prises;
	PCASE place;
	int portee [4];
	struct arbredame *fils [4][8]; 0=hg;1=hd;2=bd;3=bg

typedef struct arbredame ARBREDAME, *PARBREDAME;

struct dcase {
	PCASE prise;
	PCASE destination;
};
typedef struct dcase DCASE, *PDCASE;

struct celldcase {
	PDCASE place;
	struct celldcase *placesuivante;
};
typedef struct celldcase CELLDCASE, *PCELLDCASE;


struct listdcase {
	PCELLDCASE tete;
	PCELLDCASE queue;
};
typedef struct listdcase LISTDCASE, *PLISTDCASE;*/



/*void initSDL(void);
int ecouteUtilisateur(int *px, int *py);
void closeSDL(void);
AFFICHAGE initialisation(CONT h[10][10], int info[10][10]);
void reactualisation(CONT h[10][10],AFFICHAGE *aff, int info[10][10]);
int ouipion(CONT h[10][10], int *pplayer, int x, int y, int *pQuitter, AFFICHAGE *aff, PLISTCOUPS coupspossibles, int info[10][10]);
void deplacement(CONT h[10][10], int x, int y, int xx, int yy, AFFICHAGE *aff, int player, int info[10][10]);
void razcase (PLISTCASE p);
int videcase (LISTCASE l);
void defilercase (PLISTCASE p);
void enfilercase (int x, int y, PLISTCASE p);
void queuecase (LISTCASE l,PCASE p);
void razcoups (PLISTCOUPS p);
int videcoups (LISTCOUPS l);
void defilercoups (PLISTCOUPS p);
void enfilercoups (PCOUP cp, PLISTCOUPS p);
void queuecoups (LISTCOUPS l,PCOUP p);
int presentcase (int x, int y, PLISTCASE p);
void ajoutercoups (PLISTCOUPS ajout, PLISTCOUPS base);
void coupossible (CONT h[10][10], int player, PLISTCOUPS l);
void liberercellcase (PCELLCASE p);
void libererlistcase (PLISTCASE p);
void liberercoup (PCOUP p);
void liberercellcoups (PCELLCOUPS p);
void libererlistcoups (PLISTCOUPS p);
void libererarbrepion (PARBREPION p);
void libererarbredame (PARBREDAME p);
void cherchecoupion (int *max, CONT h[10][10], int i, int j, int player, PLISTCOUPS l);
void copiecase (PLISTCASE base, PLISTCASE copie);
void copiecoups (PLISTCOUPS base, PLISTCOUPS copie);
void consarbrepion (PARBREPION a,int player, CONT h[10][10], int *maxbis, PLISTCOUPS lbis, int i, int j);
void cherchecoupdame (int *max, CONT h[10][10], int i, int j, int player, PLISTCOUPS l);
void consarbredame (PARBREDAME a,int player, CONT h[10][10], int *maxbis, PLISTCOUPS lbis, int i, int j);

int departpos(int x, int y, PLISTCOUPS liste, CONT h[10][10],int player);
void enleverecur (PLISTCOUPS l);
int presentcoup (PCOUP c, PLISTCOUPS l);
int egalcoup(PCOUP c1, PCOUP c2);
int egalistcase(PLISTCASE l1, PLISTCASE l2);
void gardercoups(int x,int y,PLISTCOUPS l);
void inicoups (PLISTCOUPS p);
void inicase (PLISTCASE p);
int priseval(int x, int y, PLISTCOUPS l, int info[10][10]);
int prisesfinies(PLISTCOUPS l);
void maj(int x, int y, PLISTCOUPS l);
int posfinpos(int x, int y, PLISTCOUPS l, int info[10][10]);
*/


void initSDL(void);
void closeSDL(void);
int ecouteUtilisateur(int *px, int *py);
AFFICHAGE initialisation(CONT h[10][10], int info[10][10]);
void reactualisation(CONT h[10][10],AFFICHAGE *aff,int info[10][10]);
int ouipion(CONT h[10][10], int *pplayer, int x, int y, int *pQuitter, AFFICHAGE *aff, int *nbcoups, COUP coupspossibles[100], int info[10][10]);
void deplacement(CONT h[10][10], int x, int y, int xx, int yy, AFFICHAGE *aff, int player, int  info[10][10]);
int presentcase (int x, int y, int nbprises, CASE prises[20]);
void ajoutercoups (int nbajout, int nbbase, COUP ajout[100], COUP base[100]);
void coupossible (CONT h[10][10], int player, int *nbcoups, COUP l[100]);
void copiecase (int nbcase, CASE base[20], CASE copie[20]);
void copiecoups (int nbcoup, COUP base[100], COUP copie[100]);
void cherchecoupion (int *max, CONT h[10][10], int i, int j, int player, int *nbcoups, COUP l[100]);
void consarbrepion (int player, CONT h[10][10], int profondeur, int *maxbis, int *nbcoupsbis, COUP lbis[100], int i, int j, int x, int y, CASE prises[20]);
void cherchecoupdame (int *max, CONT h[10][10], int i, int j, int player, int *nbcoups, COUP l[100]);
void consarbredame (int player, CONT h[10][10], int profondeur, int *maxbis, int *nbcoupsbis, COUP lbis[100], int i, int j, int x, int y, CASE prises[20]);
int condirx (int k,int x);
int condiry (int k,int y);
int calculdirx (int k, int x, int y);
int calculdiry (int k, int x, int y);
int prisedame(int k, int x, int y, CONT h[10][10], int *portee,PCASE prise, int player, int xini, int yini);
int deplacedame (CONT h[10][10], int x, int y, int xx, int yy);
int departpos(int x, int y, int nbcoups, COUP liste[100], CONT h[10][10], int player);
void enleverecur (int *nbcoup, COUP l[100]);
int presentcoup (int nbcoups, COUP c, COUP l[100]);
int egalcoup(COUP c1, COUP c2);
int egalistcase(int nbcase, CASE l1[20], CASE l2[20]);
void gardercoups(int x,int y, int *nbcoups, COUP l[100]);
int priseval(int x, int y, int nbcoups, COUP l[100], int info[10][10]);
int prisesfinies(COUP l[100]);
void maj(int x, int y, int *nbcoups, COUP l[100]);
int posfinpos(int x, int y, int nbcoups, COUP l[100], int info[10][10]);
void cons (CONT h[10][10]);
void majdepion (int x, int y, int player, int info[10][10], CONT h [10][10]);
void majdepdame(int x, int y, int info[10][10], CONT h[10][10]);
int encorepion(CONT h[10][10], int player);
int findujeu(CONT h[10][10], int nbcoups, int player);
