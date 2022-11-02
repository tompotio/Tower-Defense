#pragma once

#include "assetsmanager.hpp"
#include "audiomanager.hpp"
#include "instances.hpp"

class Audiomanager;

class Game 
{
    public:
        Game();
        ~Game() = default;

        void Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

        void HandleEvents();

        //update par rapport aux inputs etc.
        void Update(); 

        void RenderClear();

        void Draw();

        void RenderPresent();

        void Clean();

        bool running() {return isRunning; };
        
        AssetManager assetManager;
        Instance instances;

        SDL_Renderer *renderer;

    private:
        int cnt = 0;
        int playerMonney = 0;

        bool isRunning;
        
        SDL_Window *window;
};