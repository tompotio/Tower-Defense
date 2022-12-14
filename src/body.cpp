
#include "../include/body.hpp"

void Body::HandleEvents() {
            
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        
        //Fermeture du jeu
        
        case SDL_QUIT:
            std::cout << "Hello" << std::endl;
            isRunning = false;
            break;

        default:
            break;
    }
}