#include "../include/game.hpp"
#include "../include/menu.hpp"
#include "../include/vector2.hpp"
#include <unistd.h>
#include <time.h> 

#define RESOLUTION_X 1410
#define RESOLUTION_Y 900
#define FPS 60

int main(int argc, char *args[])
{   
    const double frameDelay = (1000.0f / FPS)/1000;

    double frameStart;
    double frameTime;

    static Body* body = new Body(
        "GameWindow", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        RESOLUTION_X,
        RESOLUTION_Y,
        false
    );

    // Game n'est plus static pour permettre la désallocation lorsque recrée une partie. (Voir plus tard dans le projet)
    Game* game = new Game(body);

    while(game->running())
    {
        frameStart = clock(); //SDL_GetTicks();

        body->RenderClear();

        // Affichage
        game->UpdateGraphics();

        // Input du joueur d'abord
        game->HandleEvents();

        // Déroulement de la partie
        game->UpdateGame();

        body->RenderPresent();

        frameTime = (clock() - frameStart);
        game->deltatime = (frameTime / 1000000.0f); // des micro secondes
        
        game->fps = (100000 / ((frameTime)));
        std::cout << game->fps << std::endl;
        if(frameDelay > frameTime)
        {
            sleep(frameDelay - frameTime);
        }
    }

    game->~Game();
    body->Clean();
    return 0;
}
