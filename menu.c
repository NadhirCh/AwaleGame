#include "menu.h"
#include "graphics.h"


MenuOption currentOption = MENU_START;
ModeOption currentModeOption= PLAYER_VS_ORD;

void afficheMenu(SDL_Renderer* renderer)
{
    displayImage(renderer,"ressources/Images/AwaleMenu.png",0,0);   

}
void afficheMenuOptions(SDL_Renderer* renderer)
{
    SDL_Color noir={0,0,0};
    SDL_Color marron = {139, 69, 19, 255};
    if(currentOption==MENU_START)
    {
    writeText(renderer,font2,"Start Game",marron,350,215);
    writeText(renderer,font2,"End Game",noir,350,270);
    }
    else
    {
        writeText(renderer,font2,"Start Game",noir,350,215);
        writeText(renderer,font2,"End Game",marron,350,270);
    }
}


void switchCurrentOption(int keyUp,int keyDown,int onMenu,int onMode)
{
    if(onMenu)
    {
        if((keyUp==1)&&(currentOption==MENU_EXIT))
        {
            currentOption=MENU_START;
            playOGA("ressources/SoundEffects/house-selected.oga");
        }
        else if((keyDown==1)&&(currentOption==MENU_START))
        {
            currentOption=MENU_EXIT;
            playOGA("ressources/SoundEffects/house-selected.oga");
        }
    }
    if(onMode)
    {
        if((keyUp==1)&&(currentModeOption==PLAYER_VS_PLAYER))
        {
            currentModeOption=PLAYER_VS_ORD;
            playOGA("ressources/SoundEffects/house-selected.oga");
        }
        else if((keyDown==1)&&(currentModeOption==PLAYER_VS_ORD))
        {
            currentModeOption=PLAYER_VS_PLAYER;
            playOGA("ressources/SoundEffects/house-selected.oga");
        }
    }
        
}
void afficheModeOptions(SDL_Renderer* renderer)
{
    SDL_Color noir={0,0,0};
    SDL_Color marron = {139, 69, 19, 255};
    if(currentModeOption==PLAYER_VS_ORD)
    {
    writeText(renderer,font2,"1 Player",marron,350,215);
    writeText(renderer,font2,"2 Players",noir,350,270);
    }
    else
    {
        writeText(renderer,font2,"1 Player",noir,350,215);
        writeText(renderer,font2,"2 Players",marron,350,270);
    }
}
void handleEnterButton(SDL_Renderer* renderer,int* onMenu,int* onMode,int* quit,int*nameRead,int* read)
{
    if((currentOption==MENU_START)&&(*onMenu==1))
                        {
                            *onMode=1;
                            *onMenu=0;
                            SDL_RenderClear(renderer);
                            afficheMenu(renderer);
                            playOGA("ressources/SoundEffects/match-finished.oga");

                        }
                        else if(currentOption == MENU_EXIT)
                        {
                            *quit=1;
                        }
                        else if((currentModeOption== PLAYER_VS_PLAYER)&&(*onMode))
                        {
                            
                            *onMode=0;
                            *nameRead=1;
                            playOGA("ressources/SoundEffects/match-finished.oga");
                            afficheMenu(renderer);
                        }
                        else if((currentModeOption==PLAYER_VS_ORD)&&(*onMode))
                        {
                            *onMode=0;
                            *nameRead=1;
                            playOGA("ressources/SoundEffects/match-finished.oga");
                            afficheMenu(renderer);
                        }
                        else if(*nameRead)
                        {
                            if(currentModeOption==PLAYER_VS_PLAYER)
                            {   
                                SDL_StartTextInput();
                                if(*read==0)
                                {
                                    *read=2;
                                }
                                else
                                {
                                *read=1;
                                }
                            }
                            else if(currentModeOption==PLAYER_VS_ORD)
                            *read=1;
                            SDL_Delay(500);
                        }
                        
}
