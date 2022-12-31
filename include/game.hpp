#pragma once

#include "assetsmanager.hpp"
#include "audiomanager.hpp"
#include "instances.hpp"
#include "menu.hpp"
#include "grid.hpp"
#include "body.hpp"

#define INTERMITENCE_TIME 3

class Audiomanager;

class Game 
{
    public:
        Game(Body** body, Menu** menu);
        ~Game() = default;

        void InitCellTypes();

        void HandleEvents();

        void UpdateGraphics();

        void UpdateGame();

        void WaveManager();

        void MoveEnemies();

        void UpdateTime();

        void ResetValuesForWave();

        void UpdateIntermit();

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
        void AddTower(Tower_t t, AssetManager assetmanager);
        Tower GetTower(int id);
        
        Body** GetBody(){return body;};

        Widget* GetWidget(std::string id);

        // Renvoie si le jeu est en cours
        bool running() {return isRunning; };

        double deltatime;
        int fps = 60;

    private:
        Body** body;
        Menu** menu;
        SDL_Rect WindowSize;

        // Values
        int playerMoney;
        int base_HP;
        int current_HP;
        int grid_cell_size;
        int mouse_X = 0;
        int mouse_Y = 512;
        int bottompath_size;
        int toppath_size;
        int map_x_size;
        int map_y_size;

        int inventory_grid_cells;
        int inventory_grid_cells_size;
        int inventory_grid_offset;
        int inventory_pos_x;
        int inventory_pos_y;

        // Waves management
        int goblin_nb = 0;
        int elf_nb = 0;
        int orc_nb = 0;
        int golem_nb = 0;
        int knight_nb = 0;

        int goblin_max_nb = 5;
        int elf_max_nb = 0;
        int golem_max_nb = 0;
        int knight_max_nb = 0;
        int orc_max_nb = 0;

        int wave_nb = 1;

        double delta_s = 0; // temps en millisecondes de chaque frame
        double seconds_mil = 0; // Temps précis en secondes et millisecondes
        double last_seconds_mil = 0;
        int seconds = 0; // Temps en secondes
        int cpt_intermit = -1; 

        // Bools
        bool found_testing_path = false;
        bool isRunning;
        bool mouse_hover = true;
        bool showgrid = false;
        bool pressing_key_k = false;
        bool wave_ongoing = true;
        bool intermit_screen = false;
        bool intermit_count = false;

        bool leftMouseButtonDown;
        bool tower1Selected;
        bool tower2Selected;
        bool tower3Selected;

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

        std::vector<Widget> widgets;

        // Cursor
        SDL_Point cursor;
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