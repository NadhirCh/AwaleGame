#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
#include "src/include/SDL2/SDL_mixer.h"
#include "src/include/SDL2/SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "logic.h"

// Constants
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int CASE_WIDTH;
extern const int CASE_HEIGHT;
extern const int NB_CASES;
extern const int NB_GRAINES;
extern const int GRAINE_RADIUS;
extern const int TROU_RADIUS;
extern TTF_Font* font;
extern TTF_Font* font2;
extern int tours_sans_recolte;
extern int** planche;
 

// Structure definitions (if there are any structures in your code, declare them here)
// For example:


// Function declarations
void playOGA(const char *path);
void displayImage(SDL_Renderer* renderer, const char* path, int x, int y);
int initSDL(SDL_Window **window, SDL_Renderer **renderer);
int initTTF();
void drawCircle(SDL_Renderer *renderer, int centreX, int centreY, int rayon);
void writeText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y);
void drawGameBoard(SDL_Renderer *renderer);
void afficheTourSansRecolte(SDL_Renderer* renderer);
void afficheCurrentPlayer(SDL_Renderer* renderer, joueur* player);
void afficheScore(SDL_Renderer* renderer, joueur j1, joueur j2);
int getTrou(int x, int y, joueur* player);
void drawEndGameScreen(SDL_Renderer* renderer, joueur* P1, joueur* P2);
void afficheGame(SDL_Renderer* renderer, joueur* player, joueur P1, joueur P2);
void semer(joueur *plr, int caze, SDL_Renderer* renderer, joueur P1, joueur P2);

#endif 
