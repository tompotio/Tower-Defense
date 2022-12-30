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
    Menu* menu = new Menu(&body);
    Game* game = new Game(&body, &menu);

	
    std::cout << "Game créé" << std::endl;



    while(body->running())
    {
        // frameStart = SDL_GetTicks();

        body->RenderClear();

        
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
        
        

        body->RenderPresent();
        //game->deltatime = (frameTime / 1000000.0f); // des micro secondes

        /* frameTime = (clock() - frameStart);
        
        
        game->fps = (100000 / ((frameTime)));
        //std::cout << game->fps << std::endl;
        
        if(frameDelay > frameTime)
        {
            sleep(frameDelay - frameTime);
        } */


        //frameTime = SDL_GetTicks() - frameStart;
        SDL_Delay(1);
    }

    game->~Game();
    body->Clean();
    return 0;
}
