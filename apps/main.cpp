#include "../include/game.hpp"
#include "../include/menu.hpp"
#include "../include/vector2.hpp"
#include <unistd.h>
#include <time.h> 

/* #define RESOLUTION_X 1920
#define RESOLUTION_Y 1080 */
#define RESOLUTION_X 1410
#define RESOLUTION_Y 900

#define FPS 60

int main(int argc, char *args[])
{   
    const double frameDelay = (1000.0f / FPS) / 1000;


    static Body* body = new Body(
        "GameWindow", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        RESOLUTION_X,
        RESOLUTION_Y,
        false
    );

    // Game n'est plus static pour permettre la désallocation lorsque recrée une partie. (Voir plus tard dans le projet)
    Menu* menu = new Menu(&body);
    Game* game = new Game(&body, &menu);

	Uint32 frameStart;
    Uint32 frameTime;
    Uint32 CD = 0;
    std::cout << "Game créé" << std::endl;

    while(body->running())
    {
        body->RenderClear();
        frameStart = SDL_GetTicks();

        
        if (menu->running()) {
            menu->HandleEvents();
            menu->Update(body->GetRenderer());
            
        }
        //else if (game->running()) {
        else {
            
            // Affichage
            game->UpdateGraphics();

            // Input du joueur d'abord
            game->HandleEvents();

            // Déroulement de la partie
            game->UpdateGame();
        }

        SDL_Delay(8);
        frameTime = (SDL_GetTicks() - frameStart);
        game->deltatime = frameTime/1000.0f;
        CD+=1;

        if((CD - 150) == 0){
            CD = 0;
            game->fps = int(1000.0f/frameTime);
        }
        body->RenderPresent();
    }

    game->~Game();
    body->Clean();
    return 0;
}