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
        Game(Body** body);
        ~Game() = default;

        void InitCellTypes();

        void HandleEvents();

        void UpdateGraphics();

        void UpdateGame();

        void Draw();

        void DrawTiles();

        void DrawEnemies();
        
        void DrawPath(std::vector<Cell> path, SDL_Color color);

        void DrawBaseHealthBar();

        void DrawGrid(Grid grid);

        void DrawCursor();

        void DrawInstances();

        void DrawInventory();

        void PosEnemy(Enemy& enemy, int choice);

        void SpawnEnemy(int choice, Entity_t type);

        //Enemy Management
        void AddEnemy(Enemy enemy);

        void DeleteEnemy(int id);

        Enemy& GetEnemy(int id);

        //Tower Management
        void AddTower(Tower tower);

        Tower GetTower(int id);
        
        Body** GetBody(){return body;};

        // Renvoie si le jeu est en cours
        bool running() {return isRunning; };

        double deltatime;
        double fps = 60;

    private:
        Body** body;

        // Values
        int playerMonney;
        int base_HP;
        int current_HP;
        int grid_cell_size;
        int mouse_X = 0;
        int mouse_Y = 512;
        int wave_nb = 0;
        int bottompath_size;
        int toppath_size;
        int map_x_size;
        int map_y_size;

        int inventory_grid_cells;
        int inventory_grid_cells_size;
        int inventory_grid_offset;
        int inventory_pos_x;
        int inventory_pos_y;

        double wave_cout_s = 0;

        // Bools
        bool found_testing_path = false;
        bool isRunning;
        bool mouse_hover = true;
        bool showgrid = false;
        bool pressing_key_k = false;
        bool wave_ongoing = false;

        // Utilitaries classes
        AssetManager assetManager;

        // Grid
        Grid map;

        // Les différents chemins
        std::vector<Cell> bottompath;
        std::vector<Cell> toppath;
        std::vector<Cell> testingpath;

        // Les entités du jeu
        std::vector<Enemy> enemies;
        std::vector<Tower> towers;

        // Cursor
        SDL_Rect grid_cursor;
        SDL_Rect grid_cursor_ghost;

        // Screen
        SDL_Renderer *renderer;
        SDL_Window *window;
        TTF_Font* font;

        // Colors (bientôt deprecated)
        SDL_Color grid_background = {22, 22, 22, 255};
        SDL_Color grid_line_color = {255, 255, 255, 255};
        SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
        SDL_Color grid_cursor_color = {50, 50, 50, 255};
        SDL_Color yellow_green = {154,205,50,255};
        // Nouvelle couleurs (plus compréhensibles)
        SDL_Color orange = {255,165,0,255};
        SDL_Color lime = {0,255,0,255};
        SDL_Color saddlebrown = {139,69,19,255};
        SDL_Color black = {0,0,0,255};
};