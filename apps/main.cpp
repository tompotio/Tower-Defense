#include "../include/game.hpp"
#include "../include/vector2.hpp"

#define RESOLUTION_X 1080
#define RESOLUTION_Y 720
#define FPS 60

int main(int argc, char *args[])
{   
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    static Game* game = new Game();
    game->Init(
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

        game->HandleEvents();
        game->RenderClear();
        game->Update();
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
