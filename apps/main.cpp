#include "../include/game.hpp"
#include "../include/vector2.hpp"

#define RESOLUTION_X 1280
#define RESOLUTION_Y 720
#define FPS 60

int main(int argc, char *args[])
{   
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    static Game* game = new Game(
        "GameWindow", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        RESOLUTION_X,
        RESOLUTION_Y,
        false
    );

    while(game->running())
    {

        frameStart = SDL_GetTicks();

        // Met à jour les événements du jeu
        game->HandleEvents();

        //(couleur de fond de base du jeu)
        SDL_SetRenderDrawColor(game->renderer, 22, 22, 22, 255);

        // Applique le nouveau rendu (Donc ce qu'il y avait dans le backbuffer précédent)
        game->RenderClear();

        game->Update();
        
        // Rendu final (stocke dans le backbuffer)
        game->RenderPresent();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    game->Clean();

    return 0;
}
