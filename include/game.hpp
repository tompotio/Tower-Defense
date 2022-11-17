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

        void UpdateGraphics(); 

        void UpdateGame();

        void Draw();

        void DrawTiles();

        void DrawGrid(Grid grid);

        void DrawInstances();
        
        Body* GetBody(){return body;};

        // Renvoie si le jeu est en cours
        bool running() {return isRunning; };

        double deltatime;

    private:
        Body* body;

        // Values
        int playerMonney;
        int grid_cell_size;
        int X = 0;
        int Y = 512;
        int wave_nb = 1;

        double wave_cout_s = 0;

        // Bools
        bool foundpath = false;
        bool isRunning;
        bool mouse_hover = true;
        bool showgrid = false;
        bool pressing_key_k = false;
        bool wave_ongoing = false;

        // Utilitaries classes
        AssetManager assetManager;
        Instance instances;

        // Grid
        Grid map;
        Grid inventory;
        std::vector<Cell> path;

        // Cursor
        SDL_Rect grid_cursor;
        SDL_Rect grid_cursor_ghost;

        // Screen
        SDL_Renderer *renderer;
        SDL_Window *window;

        // Colors
        SDL_Color grid_background = {22, 22, 22, 255};
        SDL_Color grid_line_color = {255, 255, 255, 255};
        SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
        SDL_Color grid_cursor_color = {50, 50, 50, 255};
};