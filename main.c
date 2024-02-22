#include "graphics.h"
#include "menu.h"
#include "gestionFichiers.h"

int main(int argc, char* args[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    clock_t temps = clock();
    init_planche();
    char nameJoueur1[20];
    char nameJoueur2[20];
    joueur P1,P2,*player,*adversaire;
    init_joueur(&P1,Player1);
    init_joueur(&P2,Player2);
    int trou,onMenu=1;
    int* liste_trous_valides=init_liste_trou();
    player=&P1;
    adversaire=&P2;
    
    int distance=0;
    // initialiser SDL 
    if ((!initSDL(&window, &renderer)) || (!(initTTF())) ) {
        printf("Failed to initialize!\n");
    } else {                        
        afficheMenu(renderer);
        int quit = 0,onMode=0,nameRead=0;
        SDL_Event e;
        int clicked=0;
        int read=0;
        int x,y,gameOver=0;
        char temp[30];
        strcpy(temp,"Player 1: ");
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = 1;
                }
                else if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if( SDL_BUTTON_LEFT == e.button.button)
                    {
                        clicked=1;
                        SDL_GetMouseState(&x,&y);
                    }
                }
                else if(e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_UP)
                    {
                        switchCurrentOption(1,0,onMenu,onMode);
                    }
                    else if (e.key.keysym.sym == SDLK_DOWN)
                    {
                        switchCurrentOption(0,1,onMenu,onMode);
                    }
                    else if(e.key.keysym.sym == SDLK_RETURN) {
                        handleEnterButton(renderer,&onMenu,&onMode,&quit,&nameRead,&read);
                    }      
                }
                else if((e.type=SDL_TEXTINPUT)&&(nameRead))
                {
                    strcat(temp,e.text.text);
                }
               
                
            }
            if(onMenu)
            {
                afficheMenuOptions(renderer);
                SDL_RenderPresent(renderer);
            }
            else if(onMode)
            {
                afficheModeOptions(renderer);
                SDL_RenderPresent(renderer);
            }
            else if(nameRead)
            {   
                    
                    if(currentModeOption==PLAYER_VS_PLAYER)
                    {
                    SDL_Color black={0,0,0};
                    writeText(renderer,font2,temp,black,300,distance+210);

                    if((read==2)&&(distance==0))
                    {
                        memmove(temp, temp + 10, strlen(temp) - 10 + 1);
                        strcpy(nameJoueur1,temp);
                        ajoutNomJoueur(&P1,nameJoueur1);
                        distance=50;
                        strcpy(temp,"Player2 : ");
                    }
                    else if(read==1)
                    {
                        memmove(temp, temp + 10, strlen(temp) - 10 + 1);
                        strcpy(nameJoueur2,temp);
                        ajoutNomJoueur(&P2,nameJoueur2);
                        nameRead=0;
                    }
                    }

                    else if(currentModeOption == PLAYER_VS_ORD)
                    {
                    SDL_Color black={0,0,0};
                    writeText(renderer,font2,temp,black,300,210);
                        if(read==1)
                        {
                        memmove(temp, temp + 10, strlen(temp) - 10 + 1);
                        strcpy(nameJoueur1,temp);
                        ajoutNomJoueur(&P1,nameJoueur1);
                        ajoutNomJoueur(&P2,"Ordi");
                        nameRead=0;
                        }
                    }
                SDL_RenderPresent(renderer);
            }
            else
            {
            if(!gameOver)
            {
                //// PARTIE JOUEUR VS JOUEUR
                if(currentModeOption==PLAYER_VS_PLAYER)
                {
                    afficheGame(renderer,player,P1,P2);
                    SDL_RenderPresent(renderer);
                    trou=getTrou(x,y,player);
                    if((choix_trou(player,liste_trous_valides,trou)==0)&&clicked)
                    {
                        SDL_Color textColor={255,0,0};
                        writeText(renderer,font,"Appuiez sur un trou valide !",textColor,230,500);
                        SDL_RenderPresent(renderer);
                    }
                    else if((trou!=-1)&&(choix_trou(player,liste_trous_valides,trou)))
                    {
                        semer(player,trou,renderer,P1,P2);
                        SDL_RenderPresent(renderer);
                        recolte(player);
                        change_player(&player,&adversaire);
                        clicked=0;
                    }
                }

                //// Partie joueur vs Ordi
                else
                {
                    afficheGame(renderer,player,P1,P2);
                    SDL_RenderPresent(renderer);
                    if((player==&P1)&&(adversaire==&P2))
                    {
                        trou=getTrou(x,y,player);
                        if((choix_trou(player,liste_trous_valides,trou)==0)&&clicked)
                        {
                            SDL_Color textColor={255,0,0};
                            writeText(renderer,font,"Appuiez sur un trou valide !",textColor,230,500);
                            SDL_RenderPresent(renderer);
                        }
                        else if((trou!=-1)&&(choix_trou(player,liste_trous_valides,trou))&&(clicked))
                         {
                            semer(player,trou,renderer,P1,P2);
                            SDL_RenderPresent(renderer);
                            recolte(player);
                            trou=-1;
                            change_player(&player,&adversaire);
                            clicked=0;
                        } 
                    }
                    else
                    {
                        trou=choisirTrouOrdinateur(player,liste_trous_valides);
                        if((trou!=-1)&&(choix_trou(player,liste_trous_valides,trou)))
                         {
                            semer(player,trou,renderer,P1,P2);
                            SDL_RenderPresent(renderer);
                            recolte(player);
                            trou=-1;
                            change_player(&player,&adversaire);
                         } 
                    }
                }
            }
            else
            {
                SDL_Delay(1000);
                drawEndGameScreen(renderer,&P1,&P2);
                playOGA("ressources/SoundEffects/gameover.oga");
                SDL_RenderPresent(renderer);
                sauvegarderResultat("Resultats.txt",P1,P2,temps);
                quit=1;
                SDL_Delay(10000);
            }
            gameOver=(end_game(adversaire,player))||(jeu_bloque(adversaire,liste_trous_valides));
            }
        }
    }

    // Nettoyer et quitter SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit(); 
    SDL_Quit();                                         

    return 0;
}
