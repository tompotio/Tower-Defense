#pragma once

#include "assetsmanager.hpp"
#include "audiomanager.hpp"
#include "instances.hpp"
#include "grid.hpp"
#include "body.hpp"

class Audiomanager;

class Game 
{
    public:
        Game(Body* body);
        ~Game() = default;

        void HandleEvents();

        void Update(); 

        void RenderClear();

        void Draw();

        void DrawTiles();

        void DrawGrid(Grid grid);

        void DrawInstances();

        void RenderPresent();

        Body* GetBody(){return body;};

        // Renvoie si le jeu est en cours
        bool running() {return isRunning; };

    private:
        Body* body;

        int cnt;
        int playerMonney;
        int grid_cell_size;

        bool mouse_hover = true;
        bool showgrid = false;
        bool pressing_key_k = false;

        Sprite spt;

        int X = 0;
        int Y = 0;

        AssetManager assetManager;
        Instance instances;

        Grid map;
        Grid inventory;

        std::vector<Cell> path_test;

        bool foundpath = false;
        bool isRunning;

        SDL_Renderer *renderer;

        SDL_Rect grid_cursor;
        SDL_Rect grid_cursor_ghost;
        
        SDL_Window *window;

        SDL_Color grid_background = {22, 22, 22, 255};
        SDL_Color grid_line_color = {255, 255, 255, 255};
        SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
        SDL_Color grid_cursor_color = {50, 50, 50, 255};
};