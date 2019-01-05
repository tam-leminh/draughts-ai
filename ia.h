#define INFININEG -5000
#define INFINIPOS 5000
#define PROFONDEURMAX 2
#define VALPION 10
#define VALDAME 30
#define COMP 1
#define MOB 5

void ajuster(CONT h[10][10], int player, int *nbcoups, COUP liste[100]);
void constr (CONT base[10][10], COUP modif, CONT result[10][10],int player);
int evaluation(CONT h[10][10], int player);
int minimax (CONT h[10][10], int profondeurmax, int profondeur, int player, PCOUP soluse, int joueur);
int horizon (CONT h[10][10], int player, int joueur);
int alphabeta (CONT h[10][10], int profondeurmax, int profondeur, int player, PCOUP soluse, int joueur, int alpha, int beta);
