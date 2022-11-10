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

    SDL_SetWindowTitle(window, "SDL tiles on grid test");

    // Champ de déclaration des assets du jeu 
    assetManager = AssetManager();

    assetManager.AddTexture(
        "soldier",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile245.png",renderer)
    );

    assetManager.AddTexture(
        "grass",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile024.png",renderer)
    );

    assetManager.AddTexture(
        "dirt",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile050.png",renderer)
    );

    assetManager.AddTexture(
        "grass-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile023.png",renderer)
    );

    assetManager.AddTexture(
        "grass-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile025.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top-corner-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile046.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile047.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile001.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottow-corner-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile002.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottow-corner-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile299.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top-corner-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile048.png",renderer)
    );

    //std::cout << assetManager.GetTexture("grass") << std::endl;

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

    // NB : Dessiner une grille n'est pas obligatoire, c'est juste un affichage test
    // Je vais avoir besoin de la grille map pour afficher les tiles et avoir d'autres informations
    grid_cell_size = 64;

    inventory = Grid(10,1,grid_cell_size,100, 670);
    map = Grid(20,10,grid_cell_size,0,0);

    grid_cursor = {
        .x = (inventory.GetWidth() - 1) * grid_cell_size,
        .y = (inventory.GetHeight() - 1) * grid_cell_size,
        .w = grid_cell_size,
        .h = grid_cell_size,
    };

    grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size, grid_cell_size};

}

// Met à jour les éléments du jeu en fonction des événements SDL (souris, keys etc).
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
            break;

        //Fermeture du jeu
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

// Met à jour l'affichage du jeu.
void Game::Update()
{   

    // Applique la couleur des lignes
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Affiche les tiles sur la grille
    DrawTiles();

    // Affiche la grille inventory
    DrawGrid(inventory);

    // Affiche la grille map
    DrawGrid(map);

    // Dessine le grid ghost cursor
    SDL_SetRenderDrawColor(
        renderer, grid_cursor_ghost_color.r,
        grid_cursor_ghost_color.g,
        grid_cursor_ghost_color.b,
        grid_cursor_ghost_color.a
    );

    //
    SDL_RenderFillRect(renderer, &grid_cursor_ghost);

    // Dessine le grid cursor
    SDL_SetRenderDrawColor(
        renderer, grid_cursor_color.r,
        grid_cursor_color.g, grid_cursor_color.b,
        grid_cursor_color.a
    );

    //
    SDL_RenderFillRect(renderer, &grid_cursor);

    //(couleur de fond de base du jeu)
    SDL_SetRenderDrawColor(renderer, 22, 22, 22, 255);

    // Affiche les ennemis pour le fun
    for (auto enemy : instances.GetEnemies()) {
        TextureManager::BlitSprite(
            enemy.GetSprite(),
            renderer
        );
    }
}

// Dessiner les tiles
// (Pour le moment sans paramètre, il n'y a qu'une seule map dans le dossier de toute façon)
void Game::DrawTiles()
{
    // Utiliser fopen est 4 à 5 fois plus rapide que std:ifstream ! 
    FILE * fp = NULL;
    fp = fopen("../assets/map1.txt", "r");
    int c;

    if (fp == NULL){
        std::cerr << "Le programme n'a pas réussi à lire la map..." << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int x = 0; x < 20; x++){
        for(int y = 0; y < 10; y++){
            c = fgetc(fp);
            switch(c){
                case ',':
                    break;

                case '1':
                    TextureManager::BlitTexture(
                        assetManager.GetTexture("grass-top"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '4':
                    TextureManager::BlitTexture(
                        assetManager.GetTexture("grass-top"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '5':
                    TextureManager::BlitTexture(
                        assetManager.GetTexture("dirt"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '6':
                    TextureManager::BlitTexture(
                        assetManager.GetTexture("grass"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '7':
                    TextureManager::BlitTexture(
                        assetManager.GetTexture("grass"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                default:
                    break;
            }
        }
    }

}

// Dessine une grille sur l'écran.
void Game::DrawGrid(Grid grid)
{
    // Dessine les lignes de la grille verticalement à chaque position x
    for(int x = 0; x < grid.GetWidth() + 1; x++){
        SDL_RenderDrawLine(
            renderer, 
            x * grid.GetCellSize() + grid.GetOffsetX(), // x de départ
            grid.GetOffsetY(), // y de départ (câlé sur offset)
            x * grid.GetCellSize() + grid.GetOffsetX(), // x de départ
            grid.GetHeight() * grid.GetCellSize() + grid.GetOffsetY() // y d'arrivée
        );
    }

    // Dessine les lignes horizontales à chaque position y
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

// Applique le nouveau rendu (Donc ce qu'il y avait dans le backbuffer précédent)
void Game::RenderClear()
{
    SDL_RenderClear(renderer);
}

// Rajoute un nouveau rendu à afficher.
void Game::RenderPresent()
{
    SDL_RenderPresent(renderer);
}

// Appelle les destructeurs de SDL.
// NB : Sera bientôt deprecated, lors de l'ajout du inventory.
void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}