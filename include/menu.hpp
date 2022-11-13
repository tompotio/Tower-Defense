#pragma once

#include "assetsmanager.hpp"
#include "audiomanager.hpp"
#include "instances.hpp"
#include "grid.hpp"

class Menu
{
    public:
        Menu(SDL_Renderer* renderer);
        ~Menu() = default;

        void Update(SDL_Renderer* renderer); 
        bool running() {return isRunning;};
        
        std::vector<Sprite> widgets;
        Sprite sprite;
        SDL_Rect rect;


    private:
        bool isRunning;
     
        
};