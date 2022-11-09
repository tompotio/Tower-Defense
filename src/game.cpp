#include "../include/game.hpp"

//! Constructor
/**
 * Constructeur de la classe game. Initialise les éléments du jeu.
 * @param title Titre.
 * @param xpos Position en x de la fenêtre.
 * @param ypos Position en y de la fenêtre.
 * @param width Largeur de la fenêtre.
 * @param height Hauteur de la fenêtre.
 * @param fullscreen FullScreen ou non.
*/
Game::Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
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

    SDL_SetWindowTitle(window, "SDL Grid test");

    // Champ de déclaration des assets du jeu 
    AssetManager assetManager = AssetManager();

    assetManager.AddTexture(
        "enemyBlack1",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile245.png",renderer)
    );

    instances = Instance();

    instances.AddEnemy(
        Enemy(
            Vector2(
                100,
                300
            ),
            50,
            1,
            assetManager
        )
    );

    grid_cell_size = 32;

    menu = Grid(10,1,grid_cell_size,100, 670);
    map = Grid(32,20,grid_cell_size,0,0);

    grid_cursor = {
        .x = (menu.GetWidth() - 1) / 2 * grid_cell_size,
        .y = (menu.GetHeight() - 1) / 2 * grid_cell_size,
        .w = grid_cell_size,
        .h = grid_cell_size,
    };

    grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size, grid_cell_size};
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){

        // Gestion de la souris
        case SDL_MOUSEBUTTONDOWN:
            grid_cursor.x = (event.motion.x / grid_cell_size) * grid_cell_size;
            grid_cursor.y = (event.motion.y / grid_cell_size) * grid_cell_size;
            break;
        case SDL_MOUSEMOTION:
            grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
            grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;

            if (!mouse_active)
                mouse_active = SDL_TRUE;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
                mouse_hover = SDL_TRUE;
            else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
                mouse_hover = SDL_FALSE;
            break;

            //Fermeture du jeu
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

// Met à jour l'affichage du jeu
void Game::Update()
{       
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    DrawGrid(menu);
    DrawGrid(map);

    // Dessine le grid ghost cursor.
    if (mouse_active && mouse_hover) {
        SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r,
                                grid_cursor_ghost_color.g,
                                grid_cursor_ghost_color.b,
                                grid_cursor_ghost_color.a);
        SDL_RenderFillRect(renderer, &grid_cursor_ghost);
    }

    // Dessine le grid cursor.
    SDL_SetRenderDrawColor(renderer, grid_cursor_color.r,
                            grid_cursor_color.g, grid_cursor_color.b,
                            grid_cursor_color.a);
    SDL_RenderFillRect(renderer, &grid_cursor);

    SDL_RenderPresent(renderer);
}

void Game::DrawGrid(Grid grid)
{
    for(int x = 0; x < grid.GetWidth() + 1; x++){
        SDL_RenderDrawLine(
            renderer, 
            x * grid.GetCellSize() + grid.GetOffsetX(), // x de départ
            grid.GetOffsetY(), // y de départ (câlé sur offset)
            x * grid.GetCellSize() + grid.GetOffsetX(), // x de départ
            grid.GetHeight() * grid.GetCellSize() + grid.GetOffsetY() // y d'arrivée
        );
    }

    for(int y = 0; y < grid.GetHeight() + 1; y++){
        SDL_RenderDrawLine(
            renderer, 
            grid.GetOffsetX(), // x de départ (câlé sur offset)
            y * grid.GetCellSize() + grid.GetOffsetY(), // y de départ
            grid.GetWidth() * grid.GetCellSize() + grid.GetOffsetX(), // x d'arrivée
            y * grid.GetCellSize() + grid.GetOffsetY() // y de départ
        );
    }
}

void Game::RenderClear()
{
    SDL_RenderClear(renderer);
}

void Game::RenderPresent()
{
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}