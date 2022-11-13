#include "../include/game.hpp"

/*
    NB : 
        [CURSEUR DE GRILLE]
            - Ne doit s'afficher que lorsqu'il la souris est sur la grille map ou sur l'inventaire
            - Positionner le curseur en fonction de la position de la grille (pour qu'il n'y ait pas de décalage sur l'inventaire)

        [PATHFINDING]

        [WIDGETS]

        [Autres]
            Créer un singleton pour le rendu

            Créer une superclasse pour les instances 

*/

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
        "grass-top-curve-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile004.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top-curve-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile003.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom-curve-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile027.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom-curve-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile026.png",renderer)
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
        "grass-bottom-corner-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile002.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom-corner-left",
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
                500
            ),
            50,
            1,
            assetManager
        )
    );

    instances.AddEnemy(
        Enemy(
            Vector2(
                500,
                500
            ),
            50,
            1,
            assetManager
        )
    );

    instances.AddEnemy(
        Enemy(
            Vector2(
                200,
                500
            ),
            50,
            1,
            assetManager
        )
    );

    // NB : Dessiner une grille n'est pas obligatoire, c'est juste un affichage test
    // Je vais avoir besoin de la grille map pour afficher les tiles et avoir d'autres informations
    grid_cell_size = 64;

    //inventory = Grid(10,1,grid_cell_size,100, 670);

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
            if (event.button.button == SDL_BUTTON_LEFT){
                grid_cursor.x = (event.motion.x / grid_cell_size) * grid_cell_size;
                grid_cursor.y = (event.motion.y / grid_cell_size) * grid_cell_size;
                std::cout << "position = " << grid_cursor.x / 64 << " : " << grid_cursor.y / 64 << std::endl;
                path = map.FindPath(
                    5,
                    5,
                    grid_cursor.x / grid_cell_size,
                    grid_cursor.y / grid_cell_size
                );
                foundpath = true;
            }else if (event.button.button == SDL_BUTTON_RIGHT){
                showgrid = !showgrid;
            }
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
    // Affiche les tiles sur la grille
    DrawTiles();

    if (showgrid){
        // Dessine le grid cursor (Si on souhaite afficher où on clique)
        //SDL_SetRenderDrawColor(renderer, grid_cursor_color.r, grid_cursor_color.g, grid_cursor_color.b, grid_cursor_color.a);

        //
        //SDL_RenderFillRect(renderer, &grid_cursor);

        // Dessine le grid ghost cursor
        SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r, grid_cursor_ghost_color.g, grid_cursor_ghost_color.b, grid_cursor_ghost_color.a);

        //
        SDL_RenderFillRect(renderer, &grid_cursor_ghost);
    }

    // Applique la couleur des lignes (Lire la doc de la fonction pour comprendre le fonctionnement)
    SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g, grid_line_color.b, grid_line_color.a);

    if (showgrid){
        // Affiche la grille map
        map.DrawGrid(renderer);
    }

    // Affiche la grille inventory
    //inventory.DrawGrid(renderer);
    if (foundpath && showgrid){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if (path.size() > 0){
            for (int i = 0; i < path.size() - 1; i++){
                SDL_RenderDrawLine(
                    renderer, 
                    (path[i].x * grid_cell_size) + (grid_cell_size / 2), // x de départ
                    (path[i].y * grid_cell_size) + (grid_cell_size / 2), // y de départ
                    (path[i + 1].x * grid_cell_size) + (grid_cell_size / 2), // x d'arrivée
                    (path[i + 1].y * grid_cell_size) + (grid_cell_size / 2) // y d'arrivée
                );
            }
        }
    }

    // Affiche les ennemis pour le fun
    for (auto enemy : instances.GetEnemies()) {
        TextureManager::BlitSprite(
            enemy.GetSprite(),
            renderer
        );
    }

    //(couleur de fond de base du jeu)
    SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);
    
}

// Dessiner les tiles
// (Pour le moment sans paramètre, il n'y a qu'une seule map dans le dossier de toute façon)
void Game::DrawTiles()
{
    // Utiliser fopen est 4 à 5 fois plus rapide que std:ifstream ! 
    FILE * fp = NULL;
    fp = fopen("../assets/map1.txt", "r");
    int c;
    int x = 0;
    int y = 0;

    if (fp == NULL){
        std::cerr << "Le programme n'a pas réussi à lire la map..." << std::endl;
        exit(EXIT_FAILURE);
    }
    while(c != EOF){
        c = fgetc(fp);
        switch(c){
            case '1':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case '2':
            TextureManager::BlitTexture(
                assetManager.GetTexture("grass-right"),
                renderer,
                x * grid_cell_size,
                y * grid_cell_size
            );
            break;

            case '3':
            TextureManager::BlitTexture(
                assetManager.GetTexture("grass-top-curve-right"),
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
                    assetManager.GetTexture("grass-top-corner-right"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case '7':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-bottom-curve-right"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;
            
            case '8':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-bottom"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case '9':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-left"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'A':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-top-curve-left"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'B':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-bottom-corner-right"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'C':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-bottom-curve-left"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'D':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-top-corner-right"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'E':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-top-corner-left"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;
            

            default:
                break;
        }

        if(c == '\n'){
            y+=1;
            x = 0;
        }
        if(c != ',' && c != '\n' && c != ' '){
            x+=1;
        }
    }
    fclose (fp);
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