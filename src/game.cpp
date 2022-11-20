#include "../include/game.hpp"


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
    renderer = body->GetRenderer();

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

    // Dimension d'une cellule (On pourra peut être créer des maps plus petites)
    grid_cell_size = 64;

    // Dimension de la carte en cellules (On pourra directement lire)
    map_x_size = 22;
    map_y_size = 10;

    // Génère les grilles pour la partie
    inventory = Grid(10,1,grid_cell_size,100,670,renderer);
    map = Grid(map_x_size,map_y_size,grid_cell_size,0,0,renderer);

    InitCellTypes();

    // Génère les curseurs de la partie (On peut imaginer qu'on pourra les personnaliser plus tard)
    grid_cursor = {
        .x = (inventory.GetWidth() - 1) * grid_cell_size,
        .y = (inventory.GetHeight() - 1) * grid_cell_size,
        .w = grid_cell_size,
        .h = grid_cell_size,
    };
    grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size, grid_cell_size};

    // Génère les chemins des ennemis en fonction de la map
    bottompath = map.FindPath(
        0,
        8,
        21,
        6
    );
    toppath = map.FindPath(
        5,
        0,
        21,
        6
    );
    
    wave_nb += 1;

    bottompath_size = bottompath.size();
    toppath_size = toppath.size();
    wave_ongoing = true; // Je bougerai cette valeur plus tard qui se mettra true après une petite fenêtre de dialogue dans le jeu avant de débuter la partie ! 
    isRunning = true;
}

void Game::InitCellTypes(){
    // Utiliser fopen est 4 à 5 fois plus rapide que std:ifstream ! 
    FILE * fp = NULL;
    fp = fopen("../assets/map1.txt", "r");
    char c;
    int x = 0;
    int y = 0;

    if (fp == NULL){
        std::cerr << "Le programme n'a pas réussi à lire la map..." << std::endl;
        exit(EXIT_FAILURE);
    }
    while(c != EOF){
        c = fgetc(fp);

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
                std::cout << "Position souris : {X = " << grid_cursor.x / grid_cell_size << "; Y = " << grid_cursor.y / grid_cell_size << " } " << std::endl;
                // Lettre K enfoncée
                if (pressing_key_k){
                    X = grid_cursor.x;  
                    Y = grid_cursor.y;
                }else{
                    if (X >= 0 && X < (map.GetWidth() * grid_cell_size) && Y >= 0 && Y < (map.GetHeight() * grid_cell_size)&&
                    grid_cursor.x >= 0 && grid_cursor.x < (map.GetWidth() * grid_cell_size) && grid_cursor.y >= 0 && grid_cursor.y < (map.GetHeight() * grid_cell_size)){
                        std::cout << "Generate a testing path" << std::endl;
                        testingpath = map.FindPath(
                            (X / grid_cell_size),
                            (Y / grid_cell_size),
                            grid_cursor.x / grid_cell_size,
                            grid_cursor.y / grid_cell_size
                        );
                        found_testing_path = true;
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

// Met à jour l'affichage graphique du jeu.
void Game::UpdateGraphics()
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
    inventory.DrawGrid(renderer);

    //Dessine les lignes du chemin
    if (showgrid){
        if (found_testing_path){
            DrawPath(testingpath,orange);
        }
        DrawPath(bottompath,yellow_green);
    }

    // Affiche les ennemis
    DrawEnemies();

    //(couleur de fond de base du jeu)
    SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);
}

// Met à jour les unités du jeu.
void Game::UpdateGame(){
    if ((wave_ongoing)){
        // On met à jour le temps que la partie a duré
        wave_cout_s += deltatime;

        // Crée un ennemi toutes les environ 5 secondes
        if(((int)wave_cout_s + 1) % 2 == 0){
            std::cout << "Énemi généré !" << std::endl;
            wave_cout_s += 1;
            Enemy new_enemy = Enemy(
                vec2<double>(-32,512),
                50,
                50,
                assetManager
            );
            vec2<double> nextcellpos = vec2<double>(bottompath[1].x * grid_cell_size,bottompath[1].y * grid_cell_size);
            new_enemy.SetDirection(
                (nextcellpos - new_enemy.GetPosition()).normalize()
            );
            new_enemy.maxcell = bottompath_size;
            AddEnemy(
                new_enemy
            );
        }
        // Fait avancer chaque ennemi
        for (int i = 0; i < enemies.size(); i++){
            Enemy& enemy = enemies[i];
            vec2<double> cellpos = vec2<double>(bottompath[enemy.i].x * grid_cell_size,bottompath[enemy.i].y * grid_cell_size);
            if((enemy.GetPosition() - cellpos).length() <= 10 && (enemy.i < enemy.maxcell)){
                enemy.i += 1;
                if(enemy.i < enemy.maxcell){
                    vec2<double> nextcellpos = vec2<double>(bottompath[enemy.i].x * grid_cell_size,bottompath[enemy.i].y * grid_cell_size);
                    enemy.SetDirection((nextcellpos - (enemy.GetPosition())).normalize());
                }
            }
            if((enemy.i >= enemy.maxcell)){
                DeleteEnemy(i);
            }
            // Le calcul entre parenthèse pour bien comprendre même si c'est commutatif
            enemy.Move(enemy.GetDirection() * (deltatime * enemy.GetSpeed()));
        }
    }
}

// Dessine les ennemis sur l'écran
void Game::DrawEnemies(){
    for (auto enemy : enemies) {
        TextureManager::BlitSprite(
            enemy.GetSprite(),
            renderer
        );
    }
}

/**
 * Dessine un chemin généré (peut être utilisé pour débugger ou simplement avoir l'affichage).
 * @param path le chemin de cellules à afficher.
 * @param color couleur que le chemin doit prendre.
*/
void Game::DrawPath(std::vector<Cell> path, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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

// Dessine les tiles
void Game::DrawTiles()
{
    for(int x = 0; x < map_x_size; x++){
        for(int y = 0; y < map_y_size; y++){
            switch((*map.GetGridObject(x,y)).type){
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

                case 'F':
                    TextureManager::BlitTexture(
                        assetManager.GetTexture("grass-bottom-corner-left"),
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

void Game::AddEnemy(const Enemy& enemy){
    enemies.push_back(enemy);
}

void Game::DeleteEnemy(int id){
    enemies.erase(enemies.begin()+(id-1));
}

Enemy& Game::GetEnemy(int id){
    return enemies[id];
}

void Game::AddTower(std::string id, Tower tower){

}

Tower Game::GetTower(std::int16_t id){
    return Tower();
}