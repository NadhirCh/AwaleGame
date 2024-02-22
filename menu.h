#ifndef MENU_H
#define MENU_H
#include "src/include/SDL2/SDL.h"
#include "logic.h"

// Enumerations
typedef enum {
    MENU_START,
    MENU_EXIT
} MenuOption;

typedef enum {
    PLAYER_VS_PLAYER,
    PLAYER_VS_ORD
} ModeOption;

// Global variables
extern MenuOption currentOption;
extern ModeOption currentModeOption;

// Function declarations
void afficheMenu(SDL_Renderer* renderer);
void afficheMenuOptions(SDL_Renderer* renderer);
void switchCurrentOption(int keyUp, int keyDown, int onMenu, int onMode);
void afficheModeOptions(SDL_Renderer* renderer);
void handleEnterButton(SDL_Renderer* renderer, int* onMenu, int* onMode, int* quit, int* nameRead, int* read);

#endif // AWALE_GAME_MENU_H
