#include "logic.h"
#include "graphics.h"
#define Trous 6
#define Graine 3
#define max_tour_sans_recolte 20




//*erreure type1 : error en allocation memoire
void init_planche()
{
    int i, j;

    planche = (int **)malloc(2 * sizeof(int *));
    if (planche == NULL)
    {
        fprintf(stderr, "Erreur type1\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 2; i++)
    {
        planche[i] = (int *)malloc((Trous) * sizeof(int));
        if (planche[i] == NULL)
        {
            fprintf(stderr, "Erreur type1\n");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < 2; i++)
        for (j = 0; j < Trous; j++)     
           planche[i][j] = Graine;    
        
      
}

void init_joueur(joueur *j, PlayerNb plr)
{
    j->score = 0;
    j->numJoueur = plr;
    j->x = 0;
    j->y = 0;
}

void recolte(joueur *plr)
{
    if (plr->numJoueur != plr->y)
    {
        if (planche[plr->y][plr->x] == 3 || planche[plr->y][plr->x] == 2)
        {
            plr->score += planche[plr->y][plr->x];
            planche[plr->y][plr->x] = 0;
            tours_sans_recolte = max_tour_sans_recolte;
            playOGA("ressources/SoundEffects/harvest-animation.oga");   
        }
        else
        {
            tours_sans_recolte--;
        }
    }
    else
    {
        tours_sans_recolte--;
    }
}

//test si un tableau est vide ou pas
bool est_vide(int* tab)
{
     for (int i = 0; i < Trous; i++)
        if (tab[i] != -1)
            return false;

    return true;
}

void aff_liste(int*liste)
{
	int i;
	for(i=0;i<6;i++)
		printf("%d",liste[i]);
	
	printf("\n");
}

//test si une valeur appartien a une liste
bool est_dans_liste(int* liste,int val)
{
    int i=0;
    while(i<6)
    {
        if(liste[i]!=val)//j'ai dû faire ce teste comme ça parceque dans le while il faisait segmentation fault 
            i++;
        else
            break;  
    }
    if(i==6)
        return false ;
    else
        return true ; 
}

//initialise liste de trous
int* init_liste_trou()
{
    int* liste=(int*)malloc(6*sizeof(int));
    int i;
    for(i=0;i<6;i++)
        liste[i]=-1;
    
    return liste;
}

int choix_trou( joueur *plr, int *liste_trous,int trou_choisi)
{

    if (est_vide(liste_trous))
    {
            return (trou_choisi >= 0 && trou_choisi < Trous && planche[plr->numJoueur][trou_choisi] != 0);          
    }
	else
    {   
        int test=est_dans_liste(liste_trous,trou_choisi);
        for(int i=0;i<6;i++)
        {
            liste_trous[i]=-1;
        }
        return test;
    }
    
}



void change_player(joueur **plr, joueur ** adv)
{
   joueur* aux=*plr;
   *plr=*adv;
   *adv=aux;
}

bool player_bloque( joueur *plr)
{
    for (int i = 0; i < Trous; i++)
        if (planche[plr->numJoueur][i] != 0)
            return false;
    return true;
}

int end_game(joueur* current,joueur* plr2)
{
    if (current->score >= 19 ||plr2->score >= 19 || tours_sans_recolte == 0 || player_bloque(plr2))
        return 1;
    
    else
        return 0;
}



void trous_possibles(joueur player,int* liste)
        //player est le joueur bloque
{
    int pl,i=5,j=0;
    
    if(player.numJoueur==Player1)
        pl=Player2;
    else
        pl=Player1;
    
    while(i>=0)
    {
        if(i+planche[pl][i]>5)
        {
			liste[j]=i;
        }
        i--;
    }
}

int jeu_bloque(joueur* player,int *liste_trous_valides)
{
    if(player_bloque(player))
        {
            trous_possibles(*player,liste_trous_valides);
            //il n'ya aucune possibilitée pour debloqué l'adversaire le jeu s'arrete
            if(est_vide(liste_trous_valides))
            return 1 ;
        }
        return 0;
}

void ajoutNomJoueur(joueur* P,char* nomJoueur)
{
    strncpy(P->nom, nomJoueur, sizeof(P->nom) - 1);
    P->nom[sizeof(P->nom) - 1] = '\0'; // Assurer que la chaîne est terminee par null
}

int choisirTrouOrdinateur(joueur *player, int *listeTrous)
{
    int trouChoisi;

    if (est_vide(listeTrous))
    {
        // choisir le premier trou non vide de droite à gauche
        for (int i = 6 - 1; i >= 0; i--)
        {
            if (planche[player->numJoueur][i] > 0)
            {
                return i;
            }
        }

     
    }
    else
    {
        for(int trou_choisi=0;trou_choisi<6;trou_choisi++)
        if(est_dans_liste(listeTrous,trou_choisi));
        return trouChoisi;
    }
}
