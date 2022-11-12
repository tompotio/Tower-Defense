#pragma once

#include "assetsmanager.hpp"
#include "audiomanager.hpp"
#include "instances.hpp"
#include "grid.hpp"

class Menu
{
    public:
        Menu();
        ~Menu() = default;

        void Update(); 

    

        // Renvoie si le jeu est en cours
        bool running() {return isRunning; };
        
        AssetManager assetManager;
        Instance instances;

        Grid map;
        Grid inventory;

        Pathfinding* pathfinding;

        SDL_Renderer *renderer;

    private:
        int cnt;
        int playerMonney;
        int grid_cell_size;

        bool isRunning;
        bool mouse_hover = true;
        bool showgrid = false;

        SDL_Rect grid_cursor;
        SDL_Rect grid_cursor_ghost;
        
        SDL_Window *window;

        SDL_Color grid_background = {22, 22, 22, 255};
        SDL_Color grid_line_color = {255, 255, 255, 255};
        SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
        SDL_Color grid_cursor_color = {50, 50, 50, 255};
};