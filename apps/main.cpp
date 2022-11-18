#include "../include/game.hpp"
#include "../include/menu.hpp"
#include "../include/vector2.hpp"
#include <unistd.h>

#define RESOLUTION_X 1410
#define RESOLUTION_Y 832
#define FPS 60

int main(int argc, char *args[])
{   
    const Uint32 frameDelay = 1000.0f / FPS;

    Uint32 frameStart;
    Uint32 frameTime;

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
        frameStart = SDL_GetTicks();

        body->RenderClear();

        // Affichage
        game->UpdateGraphics();

        // Input du joueur d'abord
        game->HandleEvents();

        // Déroulement de la partie
        game->UpdateGame();

        body->RenderPresent();

        frameTime = SDL_GetTicks() - frameStart;
        game->deltatime = (frameTime / 1000.0f);

        // Ajoute un délai lorsque l'ordinateur tourne trop rapidement pour rester à 60 fps
        // NB : Pour je ne sais quelle raison, SDL_Delay ralenti énormément le déplacement de grid shadow tout en ayant 60 fps constant.
        /*
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        */

       // En attendant qu'un jour le bug soit réglé, j'ai mis un mini délai de 1 qui semble ne pas trop troubler le jeu.
       SDL_Delay(1);

        // Affiche les FPS sur le terminal pour les tests
        //std::cout << 1000 / (SDL_GetTicks() - frameStart) << std::endl;
    }

    game->~Game();
    body->Clean();
    return 0;
}
