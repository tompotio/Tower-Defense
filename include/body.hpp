#pragma once

#include <SDL2/SDL.h>

#include <iostream>
#include <SDL2/SDL_mixer.h>

class Body {
    public:
        Body(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
            int flags = 0;
            if(fullscreen){
                flags = SDL_WINDOW_FULLSCREEN;
            }

            if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
            {
                std::cout << "Subsystems Initialised!..." << std::endl;

                window = SDL_CreateWindow(title, xpos, ypos, width, height,flags);
                if(window){
                    std::cout << "Window created!" << std::endl;
                }

                renderer = SDL_CreateRenderer(window,-1,0);

                if(renderer)
                {
                    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
                    std::cout << "Renderer created!" << std::endl;
                }
                
                isRunning = true;
            }
            else {
                isRunning = false;
            }

            SDL_SetWindowTitle(window, "SDL tiles on grid test");
        };

        void HandleEvents();

        void Clean(){
            SDL_DestroyWindow(window);
            SDL_Quit();
            std::cout << "Game Cleaned" << std::endl;
        };

        // Applique le nouveau rendu (Donc ce qu'il y avait dans le backbuffer précédent)
        void RenderClear()
        {
            SDL_RenderClear(renderer);
        };

        // Rajoute un nouveau rendu à afficher.
        void RenderPresent()
        {
            SDL_RenderPresent(renderer);
        };

        // Renvoie si le jeu est en coursmake

        bool running() {return isRunning;};
        void setRunning(bool state) {isRunning = state;}
        SDL_Renderer* GetRenderer(){return renderer;};
        SDL_Window* GetWindow(){return window;};

    private:
        SDL_Renderer* renderer;
        SDL_Window *window;
        bool isRunning;
};