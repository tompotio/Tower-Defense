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
Game::Game(Body* body)
{   
    this-> body = body;

    // Champ de déclaration des assets du jeu 
    assetManager = AssetManager();

    assetManager.AddTexture(
        "soldier",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile245.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile024.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "dirt",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile050.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-top-curve-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile004.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-top-curve-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile003.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-bottom-curve-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile027.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-bottom-curve-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile026.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile023.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile025.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-top-corner-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile046.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-top",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile047.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-bottom",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile001.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-bottom-corner-right",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile002.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-bottom-corner-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile299.png",(*GetBody()).GetRenderer())
    );

    assetManager.AddTexture(
        "grass-top-corner-left",
        TextureManager::LoadTexture("../assets/PNG/Default size/towerDefense_tile048.png",(*GetBody()).GetRenderer())
    );

    //std::cout << assetManager.GetTexture("grass") << std::endl;

    instances = Instance();

    instances.AddEnemy(
        Enemy(
            vec2<double>(
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
            vec2<double>(
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
            vec2<double>(
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

    map = Grid(20,10,grid_cell_size,0,0,body->GetRenderer());

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
        // Clic de la souris
        case SDL_MOUSEBUTTONDOWN:
            // Clic gauche
            if (event.button.button == SDL_BUTTON_LEFT){
                grid_cursor.x = (event.motion.x / grid_cell_size) * grid_cell_size;
                grid_cursor.y = (event.motion.y / grid_cell_size) * grid_cell_size;
                std::cout << "Position souris : {X = " << grid_cursor.x << "; Y = " << grid_cursor.y << " } " << std::endl;
                // Lettre K enfoncée
                if (pressing_key_k){
                    X = grid_cursor.x;  
                    Y = grid_cursor.y;
                    instances.GetEnemy(0).SetPosition(vec2<double>(X,Y));
                }else{
                    if (X >= 0 && X < (map.GetWidth() * grid_cell_size) && Y >= 0 && Y < (map.GetHeight() * grid_cell_size)&&
                    grid_cursor.x >= 0 && grid_cursor.x < (map.GetWidth() * grid_cell_size) && grid_cursor.y >= 0 && grid_cursor.y < (map.GetHeight() * grid_cell_size)){
                    int enemyposx = instances.GetEnemy(0).GetPosition().x;
                    int enemyposy = instances.GetEnemy(0).GetPosition().y;
                    path_test = map.FindPath(
                        (enemyposx / grid_cell_size), // (X / grid_cell_size), 
                        (enemyposy / grid_cell_size), // (Y / grid_cell_size), 
                        grid_cursor.x / grid_cell_size,
                        grid_cursor.y / grid_cell_size
                    );
                    foundpath = true;
                    }
                }
            }else if (event.button.button == SDL_BUTTON_RIGHT){
                showgrid = !showgrid;
            }
            break;
        // Position de la souris
        case SDL_MOUSEMOTION:
            grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
            grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;
            break;
        // Appuie une touche du clavier
        case SDL_KEYDOWN:
            // Touche K
            if (event.key.keysym.sym == SDLK_k){
                pressing_key_k = true;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            }
            break;
        // Lache une touche du clavier
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_k){
                pressing_key_k = false;
            }
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
        //SDL_SetRenderDrawColor((*GetBody()).GetRenderer(), grid_cursor_color.r, grid_cursor_color.g, grid_cursor_color.b, grid_cursor_color.a);

        //
        //SDL_RenderFillRect((*GetBody()).GetRenderer(), &grid_cursor);

        // Dessine le grid ghost cursor
        SDL_SetRenderDrawColor((*GetBody()).GetRenderer(), grid_cursor_ghost_color.r, grid_cursor_ghost_color.g, grid_cursor_ghost_color.b, grid_cursor_ghost_color.a);

        //
        SDL_RenderFillRect((*GetBody()).GetRenderer(), &grid_cursor_ghost);
    }

    // Applique la couleur des lignes (Lire la doc de la fonction pour comprendre le fonctionnement)
    SDL_SetRenderDrawColor((*GetBody()).GetRenderer(), grid_line_color.r, grid_line_color.g, grid_line_color.b, grid_line_color.a);

    if (showgrid){
        // Affiche la grille map
        map.DrawGrid((*GetBody()).GetRenderer());
    }

    // Affiche la grille inventory
    //inventory.DrawGrid((*GetBody()).GetRenderer());

    //Dessine les lignes du chemin
    if (foundpath && showgrid){
        SDL_SetRenderDrawColor((*GetBody()).GetRenderer(), 255, 64, 0, 255);
        if (path_test.size() > 0){
            for (int i = 0; i < path_test.size() - 1; i++){
                SDL_RenderDrawLine(
                    (*GetBody()).GetRenderer(), 
                    (path_test[i].x * grid_cell_size) + (grid_cell_size / 2), // x de départ
                    (path_test[i].y * grid_cell_size) + (grid_cell_size / 2), // y de départ
                    (path_test[i + 1].x * grid_cell_size) + (grid_cell_size / 2), // x d'arrivée
                    (path_test[i + 1].y * grid_cell_size) + (grid_cell_size / 2) // y d'arrivée
                );

                /**
                 * [BUGUÉ] En cours...
                 * [NB :] L'ennemi avance en pixel/frame. Rajouter un produit en croix pour qu'il avance en pixel par seconde.
                 * (1 / FPS)
                */
               
                vec2<double> cellpos = vec2<double>(path_test[i].x * grid_cell_size,path_test[i].y * grid_cell_size);
                vec2<double> dir = cellpos - instances.GetEnemy(0).GetPosition();
                
                dir.normalize();
                instances.GetEnemy(0).Move(dir);
            }
        }
    }

    // Affiche les ennemis pour le fun
    for (auto enemy : instances.GetEnemies()) {
        TextureManager::BlitSprite(
            enemy.GetSprite(),
            (*GetBody()).GetRenderer());
    }

    //(couleur de fond de base du jeu)
    SDL_SetRenderDrawColor((*GetBody()).GetRenderer(), grid_background.r, grid_background.g, grid_background.b, grid_background.a);
    
}

// Dessiner les tiles
// (Pour le moment sans paramètre, il n'y a qu'une seule map dans le dossier de toute façon)
void Game::DrawTiles()
{
    // Utiliser fopen est 4 à 5 fois plus rapide que std:ifstream ! 
    FILE * fp = NULL;
    fp = fopen("../assets/map1.txt", "r");
    char c = '1';
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
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case '2':
            TextureManager::BlitTexture(
                assetManager.GetTexture("grass-right"),
                (*GetBody()).GetRenderer(),
                x * grid_cell_size,
                y * grid_cell_size
            );
            break;

            case '3':
            TextureManager::BlitTexture(
                assetManager.GetTexture("grass-top-curve-right"),
                (*GetBody()).GetRenderer(),
                x * grid_cell_size,
                y * grid_cell_size
            );
            break;

            case '4':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-top"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case '5':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("dirt"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case '6':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-top-corner-right"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case '7':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-bottom-curve-right"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;
            
            case '8':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-bottom"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case '9':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-left"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'A':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-top-curve-left"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'B':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-bottom-corner-right"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'C':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-bottom-curve-left"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'D':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-top-corner-right"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

            case 'E':
                TextureManager::BlitTexture(
                    assetManager.GetTexture("grass-top-corner-left"),
                    (*GetBody()).GetRenderer(),
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;
            

            default:
                break;
        }

        if(c == '\n'){
            y += 1;
            x = 0;
        }
        if(c != ',' && c != '\n' && c != ' '){
            map.AffectTypeToCell(x,y,c);
            x += 1;
        }
    }
    fclose (fp);
}