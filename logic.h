#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Trous 6
#define Graine 3
#define max_tour_sans_recolte 20

// Enumerations
typedef enum {
    Player1,
    Player2
} PlayerNb;

// Structures
typedef struct joueur {
    PlayerNb numJoueur;
    char nom[20];
    int score;
    int x;
    int y;
} joueur;

// Global variables
extern int** planche;
extern int tours_sans_recolte;

// Function declarations
void init_planche();
void init_joueur(joueur *j, PlayerNb plr);
void recolte(joueur *plr);
bool est_vide(int* tab);
void aff_liste(int* liste);
bool est_dans_liste(int* liste, int val);
int* init_liste_trou();
int choix_trou(joueur *plr, int *liste_trous, int trou_choisi);
void change_player(joueur **plr, joueur **adv);
bool player_bloque(joueur *plr);
int end_game(joueur* current, joueur* plr2);
void trous_possibles(joueur player, int* liste);
int jeu_bloque(joueur* player, int *liste_trous_valides);
void ajoutNomJoueur(joueur* P, char* nomJoueur);
int choisirTrouOrdinateur(joueur *joueur, int *listeTrous);

#endif 
