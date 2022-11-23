#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Body{
    public:
        Body(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
            int flags = 0;
            if(fullscreen){
                flags = SDL_WINDOW_FULLSCREEN;
            }

            if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
            {
                window = SDL_CreateWindow(title, xpos, ypos, width, height,flags);
                if(window){
                    std::cout << "Fenêtre créée !" << std::endl;
                }

                renderer = SDL_CreateRenderer(window,-1,0);

                if(renderer)
                {
                    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
                    std::cout << "Renderer créé !" << std::endl;
                }
            }
            if (TTF_Init() == 0)
		        std::cout << "TTF initialisé !" << std::endl;

            SDL_SetWindowTitle(window, "Tower Defense");
        };

        void Clean(){
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            std::cout << "Game Cleaned" << std::endl;
        };

        // Applique le nouveau rendu (Donc ce qu'il y avait dans le backbuffer précédent)
        void RenderClear()
        {
            SDL_RenderClear(renderer);
        }

        // Rajoute un nouveau rendu à afficher.
        void RenderPresent()
        {
            SDL_RenderPresent(renderer);
        }
        
        SDL_Renderer* GetRenderer(){return renderer;};
        SDL_Window* GetWindow(){return window;};

    private:
        SDL_Renderer* renderer;
        SDL_Window *window;
};