#include "graphics.h"



const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CASE_WIDTH = 100;
const int CASE_HEIGHT = 100;
const int NB_CASES = 12;
const int NB_GRAINES = 5;
const int GRAINE_RADIUS = 5;
const int TROU_RADIUS = 40;
TTF_Font* font=NULL;
TTF_Font* font2=NULL;
int tours_sans_recolte=20;
int** planche=NULL;


// Sound Effects Playing 

void playOGA(const char *path) {
    Mix_Music *music = Mix_LoadMUS(path);
    if (music == NULL) {
        printf("Failed to load OGA file! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, 1);

    // Wait for the music to finish
    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    // Free the music
    Mix_FreeMusic(music);
}



// SDL IMAGE DISPLAYING 
 void displayImage(SDL_Renderer* renderer, const char* path, int x,int y) {
    SDL_Surface* newSurface = NULL;
    newSurface = IMG_Load(path);
    if (newSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
    SDL_Rect destRect = {x, y, 0, 0};

    // Query the texture to get its width and height
    SDL_QueryTexture(imageTexture, NULL, NULL, &destRect.w, &destRect.h);

    // Render the texture at the specified position
    SDL_RenderCopy(renderer, imageTexture, NULL, &destRect);
}


// Initialiser SDL
int initSDL(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Awélé", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 0;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }
    return 1;
}

// initialiser le SDL TTF 
int initTTF()
{
    // Initialiser SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }  
    // Charger une police
    font =TTF_OpenFont("ressources/ARIAL.ttf", 30);
    font2 =TTF_OpenFont("ressources/ARIAL.ttf", 20);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }
    
    return 1;
}


// Dessiner un cercle (pour représenter une graine ou un trou)
void drawCircle(SDL_Renderer *renderer, int centreX, int centreY, int rayon) {
    for (int w = 0; w < rayon * 2; w++) {
        for (int h = 0; h < rayon * 2; h++) {
            int dx = rayon - w; // distance horizontale depuis le centre
            int dy = rayon - h; // distance verticale depuis le centre
            if ((dx * dx + dy * dy) <= (rayon * rayon)) {
                SDL_RenderDrawPoint(renderer, centreX + dx, centreY + dy);
            }
        }
    }
}

// Afficher du texte sur l'écran 
void writeText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Unable to create text surface! SDL Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect textRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}



// Dessiner le plateau de jeu
void drawGameBoard(SDL_Renderer *renderer) {
    
    SDL_Rect gameRect;
    // Calcul pour centrer le plateau
    int startX = (WINDOW_WIDTH - (CASE_WIDTH * (NB_CASES / 2))) / 2;
    int startY = (WINDOW_HEIGHT - (2 * CASE_HEIGHT)) / 2;
    

    // Couleur de fond
    SDL_SetRenderDrawColor(renderer, 210, 180, 140, 255); // Couleur bois
    SDL_RenderClear(renderer);
    // Dessiner les cases et les trous pour les deux joueurs
    for (int i = 0; i < NB_CASES / 2; i++) {
        
        
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Marron
        gameRect = (SDL_Rect){i * CASE_WIDTH +startX, WINDOW_HEIGHT / 2 - CASE_HEIGHT , CASE_WIDTH, CASE_HEIGHT*2};
        SDL_RenderFillRect(renderer, &gameRect);


        int inverse;
        // Trou pour chaque joueur
        for (int j = 0; j < 2; j++) {
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir pour les trous            
            (j==0) ? inverse=i : (inverse=5-i); 
            int x = startX + i * CASE_WIDTH + CASE_WIDTH / 2;
            int y = startY + ((j+1)%2) * CASE_HEIGHT + CASE_HEIGHT / 2;
            drawCircle(renderer, x, y, TROU_RADIUS);
            
            // Dessiner des graines dans les trous
            SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Or pour les graines
            int grainX,grainY;
            
            for (int k = 0; k < planche[j][inverse]; k++) {
                // Petit décalage pour la position des graines
                
                if(k%2 == 0)
                {
                    grainY = y + (6*k - TROU_RADIUS/2 );
                    grainX = x - 10 ;
                }
                else
                { 
                    grainY = y + (6*k - TROU_RADIUS/2 );
                    grainX = x+ 10;
                }
                drawCircle(renderer, grainX, grainY, GRAINE_RADIUS);
            }
        }
    }
   

}



void afficheTourSansRecolte(SDL_Renderer* renderer)
{
    char text[100];
    SDL_Color textColor={255,255,255};
    sprintf(text,"Tours Sans Recolte: %d",tours_sans_recolte);
    writeText(renderer,font2,text,textColor,20,10);
}
void afficheCurrentPlayer(SDL_Renderer* renderer,joueur* player)
{
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);          
    if(player->numJoueur==0)
    {
        drawCircle(renderer,315,468,10);
    }
    else
    {
        drawCircle(renderer,315,115,10);
    }
   
}




void afficheScore(SDL_Renderer* renderer,joueur j1,joueur j2)
{
    char score1[5];
    char score2[5];
    SDL_Color color = {255,255,255};
    sprintf(score1,"%d",j1.score);
    sprintf(score2,"%d",j2.score);
    writeText(renderer,font,score1,color,500,450);
    writeText(renderer,font,score2,color,500,100);
    SDL_Color textColor={0,0,128};
    writeText(renderer,font,j1.nom,textColor,340,450);
    writeText(renderer,font,j2.nom,textColor,340,100);
}

int getTrou(int x,int y,joueur* player)
{
   if(player->numJoueur == 1 && y >= 210 && y <= 290) {
    for(int i = 0; i < 6; i++) {
        int minX = 110 + 100 * i;
        int maxX = minX + 80;
        if(x >= minX && x <= maxX) {
            return 5-i;
        }
    }}
    if(player->numJoueur == 0 && y >= 310 && y <= 390) {
    for(int i = 0; i < 6; i++) {
        int minX = 110 + 100 * i;
        int maxX = minX + 80;
        if(x >= minX && x <= maxX) {
            return i ;
        }
    }
}
    return -1;
}

void drawEndGameScreen(SDL_Renderer* renderer,joueur* P1,joueur* P2)
{
        SDL_SetRenderDrawColor(renderer, 248, 203, 173, 255); 
        SDL_RenderClear(renderer);
        SDL_Color textColor={0,0,0};
        char Result[100];   
        if(P1->score>P2->score)
        {
            
            sprintf(Result,"%s won ! ",P1->nom);
            writeText(renderer,font,Result,textColor,300,100);
        }
        else
        {   
            sprintf(Result,"%s won ! ",P2->nom);
            writeText(renderer,font,Result,textColor,300,150);
        }
        writeText(renderer,font,"Final Scores:",textColor,300,250);
        char score1[100];
        char score2[100];
        sprintf(score1,"%s %d ",P1->nom,P1->score);
        sprintf(score2,"%s %d ",P2->nom,P2->score);

        writeText(renderer,font,score1,textColor,300,300);
        writeText(renderer,font,score2,textColor,300,350);
        SDL_RenderPresent(renderer);
}


void afficheGame(SDL_Renderer* renderer,joueur* player,joueur P1,joueur P2)
{
    drawGameBoard(renderer);
    afficheCurrentPlayer(renderer,player);
    afficheScore(renderer,P1,P2);
    afficheTourSansRecolte(renderer);
}

// cette fonction doit être dans la partie logique mais vue qu'on aura besoin de faire un refresh du jeu à chaque déplacement de grain
// on aura besoin de SDL 
void semer(joueur *plr, int caze,SDL_Renderer* renderer,joueur P1,joueur P2)
{

    int pas = planche[plr->numJoueur][caze];
    planche[plr->numJoueur][caze] = 0;

    int x = caze + 1;
    int y = plr->numJoueur;

    while (pas != 0)
    {
        if (x >= Trous)
        {
            x = 0;
            if (y == Player1)
                y = Player2;
            else
            {
                y = Player1;
            }
        }

        if (x != caze || (x == caze && y != plr->numJoueur))
        {
            planche[y][x]++;
            SDL_Delay(300);
            playOGA("ressources/SoundEffects/capture-animation.oga");
            afficheGame(renderer,plr,P1,P2);
            SDL_RenderPresent(renderer);
            pas--;
        }
        x++;
        

    }
    x--;
    plr->x = x;
    plr->y = y;
}




