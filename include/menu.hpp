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


        // Renvoie si le jeu est en cours
        bool running() {return isRunning; };
        
        AssetManager assetManager;

    private:
        

        bool isRunning;
     
        
};