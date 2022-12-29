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
    this->body = body;
    renderer = body->GetRenderer();

    // Champ de déclaration des assets du jeu 
    assetManager = AssetManager();

    font = load_font( "../assets/arial.ttf", 14);
    if (font == nullptr) std::cout << "ptdr null" << std::endl;

    assetManager.AddTexture(
        "zombie",
        LoadTexture("../assets/tiles/zombie_000.png",renderer)
    );

    assetManager.AddTexture(
        "cadre",
        LoadTexture("../assets/u_wu.png",renderer)
    );

    assetManager.AddTexture(
        "blur",
        LoadTexture("../assets/beur.png",renderer)
    );

    //LoadTexture("../../move/skeleton-move_0t.png",renderer)

    assetManager.AddTexture(
        "grass",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile024.png",renderer)
    );

    assetManager.AddTexture(
        "dirt",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile050.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top-curve-right",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile004.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top-curve-left",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile003.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom-curve-right",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile027.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom-curve-left",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile026.png",renderer)
    );

    assetManager.AddTexture(
        "grass-right",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile023.png",renderer)
    );

    assetManager.AddTexture(
        "grass-left",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile025.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top-corner-right",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile046.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile047.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile001.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom-corner-right",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile002.png",renderer)
    );

    assetManager.AddTexture(
        "grass-bottom-corner-left",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile299.png",renderer)
    );

    assetManager.AddTexture(
        "grass-top-corner-left",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile048.png",renderer)
    );

    // Dimension d'une cellule (On pourra peut être créer des maps plus petites)
    grid_cell_size = 64;
    base_HP = 100;
    current_HP = 100;

    // Dimension de la carte en cellules (On pourra directement lire)
    map_x_size = 22;
    map_y_size = 10;

    // Génère les grilles pour la partie
    map = Grid(map_x_size,map_y_size,grid_cell_size,0,0,renderer);

    InitCellTypes();

    // Génère les curseurs de la partie (On peut imaginer qu'on pourra les personnaliser plus tard)
    grid_cursor = {
        .x = (map.GetWidth() - 1) * grid_cell_size,
        .y = (map.GetHeight() - 1) * grid_cell_size,
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
    toppath_size = toppath.size();
    bottompath_size = bottompath.size();
    wave_nb += 1;
    wave_ongoing = true; // Je bougerai cette valeur plus tard qui se mettra true après une petite fenêtre de dialogue dans le jeu avant de débuter la partie ! 
    isRunning = true;

    // Provisoire
    inventory_grid_cells = 5;
    inventory_grid_cells_size = 64;
    inventory_grid_offset = 10;
    inventory_pos_x = 300;
    inventory_pos_y = 735;
}

void Game::InitCellTypes(){
    // Utiliser fopen est 4 à 5 fois plus rapide que std:ifstream ! 
    FILE * fp = NULL;
    fp = fopen("../assets/maps/map1.txt", "r");
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
                    mouse_X = grid_cursor.x;  
                    mouse_Y = grid_cursor.y;
                }else{
                    if (mouse_X >= 0 && mouse_X < (map.GetWidth() * grid_cell_size) && mouse_Y >= 0 && mouse_Y < (map.GetHeight() * grid_cell_size)&&
                    grid_cursor.x >= 0 && grid_cursor.x < (map.GetWidth() * grid_cell_size) && grid_cursor.y >= 0 && grid_cursor.y < (map.GetHeight() * grid_cell_size)){
                        std::cout << "Generate a testing path" << std::endl;
                        testingpath = map.FindPath(
                            (mouse_X / grid_cell_size),
                            (mouse_Y / grid_cell_size),
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

    // Affiche les ennemis
    DrawEnemies();

    if (showgrid){
        //Affiche le curseur de la grille
        DrawCursor();

        // Affiche la grille map
        map.DrawGrid(renderer);
        int w;
        int h;
        TTF_SizeText(font, "FPS", &w, &h);
        apply_text(renderer,50,50,w,h,"FPS",font);

        //Dessine les lignes du chemin
        if (found_testing_path){
            DrawPath(testingpath,orange);
        }
        DrawPath(bottompath,yellow_green);
    }

    // Affiche l'inventaire
    DrawInventory();
    
    // Affiche la barre de vie
    DrawBaseHealthBar();

    //(couleur de fond de base du jeu)
    SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);
}

// Met à jour les unités du jeu.
void Game::UpdateGame(){
    if ((wave_ongoing)){
        // On met à jour le temps que la partie a duré
        wave_cout_s += deltatime;

        // Crée un ennemi toutes les environ 5 secondes * temps lié à la difficulté (je coderai ça plus tard)
        if(((int)wave_cout_s + 1) % 2 == 0){
            wave_cout_s += 1;
            int path = rand() % 2 +1; // Génère un nombre "aléatoire" en 1 et 2 pour choisir le chemin                
            SpawnEnemy(path, GOBLIN);
        }

        // Fait avancer chaque ennemi
        for (int i = 0; i < enemies.size(); i++){
            Enemy& enemy = enemies[i];
            // Si l'ennemi n'est pas mort
            if(!(enemy.dead)){
                vec2<double> cellpos = vec2<double>((*enemy.path)[enemy.i].x * grid_cell_size,(*enemy.path)[enemy.i].y * grid_cell_size);
                if((enemy.GetPosition() - cellpos).length() <= 10 && (enemy.i < enemy.maxcell)){
                    enemy.i += 1;
                    if(enemy.i < enemy.maxcell){
                        vec2<double> nextcellpos = vec2<double>((*enemy.path)[enemy.i].x * grid_cell_size,(*enemy.path)[enemy.i].y * grid_cell_size);
                        enemy.SetDirection((nextcellpos - (enemy.GetPosition())).normalize());
                    }
                }
                if((enemy.i >= enemy.maxcell)){
                    // Tue l'ennemi
                    enemy.dead = true;
                    // Inflige des dégâts à la base
                    current_HP -= enemy.GetDamage();
                }else{
                    // Le calcul entre parenthèse pour bien comprendre même si c'est commutatif
                    enemy.Move(enemy.GetDirection() * (deltatime * enemy.GetSpeed()));
                }
            }
        }
    }
}

void Game::DrawCursor(){
    // Dessine le curseur uniquement s'il est dans la grille
    if ((mouse_X >= 0) &&
    (mouse_X < (map.GetWidth() * grid_cell_size)) && 
    (mouse_Y >= 0 && mouse_Y < (map.GetHeight() * grid_cell_size))
    ){
        SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r, grid_cursor_ghost_color.g, grid_cursor_ghost_color.b, grid_cursor_ghost_color.a);
        SDL_RenderFillRect(renderer, &grid_cursor_ghost);
    }
}

// Dessine les ennemis sur l'écran
void Game::DrawEnemies(){
    for (Enemy& enemy : enemies) {
        if(!enemy.dead){
            BlitSprite(
                enemy.GetSprite(),
                renderer
            );
        } 
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

void Game::DrawBaseHealthBar(){
    // NB : IL faudra wrapper SetRender dans une autre fonction pour ne pas à avoir à mettre 5 paramètres à chaque fois !
    SDL_Rect fond = {900,750,3 * base_HP, 10};
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderFillRect(renderer, &fond);

    if(current_HP >= 0){
        SDL_Rect vie = {900,750,3 * current_HP, 10};
        SDL_SetRenderDrawColor(renderer, lime.r, lime.g, lime.b, lime.a);
        SDL_RenderFillRect(renderer, &vie);
    }else{
        //BlitTexture(assetManager.GetTexture("blur"),renderer,0,0);
    }

    //BlitTexture(assetManager.GetTexture("blur"),renderer,0,0);
}

void Game::DrawInventory(){
    // Affiche le background du menu
    BlitTexture(assetManager.GetTexture("cadre"),renderer,0,640);

    // Génère les cellules du menu
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    for(int i = 0; i < inventory_grid_cells; i++){
        SDL_Rect rect = {
            (i * (inventory_grid_cells_size + inventory_grid_offset)) + inventory_pos_x,
            inventory_pos_y,
            inventory_grid_cells_size,
            inventory_grid_cells_size
        };
        SDL_RenderFillRect(renderer, &rect);
    }
}

// Dessine les tiles
void Game::DrawTiles()
{
    for(int x = 0; x < map_x_size; x++){
        for(int y = 0; y < map_y_size; y++){
            switch((*map.GetGridObject(x,y)).type){
                case '1':
                    BlitTexture(
                        assetManager.GetTexture("grass"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '2':
                BlitTexture(
                    assetManager.GetTexture("grass-right"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

                case '3':
                BlitTexture(
                    assetManager.GetTexture("grass-top-curve-right"),
                    renderer,
                    x * grid_cell_size,
                    y * grid_cell_size
                );
                break;

                case '4':
                    BlitTexture(
                        assetManager.GetTexture("grass-top"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '5':
                    BlitTexture(
                        assetManager.GetTexture("dirt"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '6':
                    BlitTexture(
                        assetManager.GetTexture("grass-top-corner-right"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '7':
                    BlitTexture(
                        assetManager.GetTexture("grass-bottom-curve-right"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;
                
                case '8':
                    BlitTexture(
                        assetManager.GetTexture("grass-bottom"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case '9':
                    BlitTexture(
                        assetManager.GetTexture("grass-left"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case 'A':
                    BlitTexture(
                        assetManager.GetTexture("grass-top-curve-left"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case 'B':
                    BlitTexture(
                        assetManager.GetTexture("grass-bottom-corner-right"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case 'C':
                    BlitTexture(
                        assetManager.GetTexture("grass-bottom-curve-left"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case 'D':
                    BlitTexture(
                        assetManager.GetTexture("grass-top-corner-right"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case 'E':
                    BlitTexture(
                        assetManager.GetTexture("grass-top-corner-left"),
                        renderer,
                        x * grid_cell_size,
                        y * grid_cell_size
                    );
                    break;

                case 'F':
                    BlitTexture(
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

//Positionne l'ennemi
void Game::PosEnemy(Enemy& enemy, int choice){
    vec2<double> nextcellpos;
    if (choice == 1){
        enemy.SetPosition(vec2<double>(-32,512));
        nextcellpos = vec2<double>(bottompath[1].x * grid_cell_size,bottompath[1].y * grid_cell_size);
        enemy.maxcell = bottompath_size;
        enemy.path = &bottompath;
    }else{
        enemy.SetPosition(vec2<double>(320,-32));
        nextcellpos = vec2<double>(toppath[1].x * grid_cell_size,toppath[1].y * grid_cell_size);
        enemy.maxcell = toppath_size;
        enemy.path = &toppath;
    }

    enemy.SetDirection(
        (nextcellpos - enemy.GetPosition()).normalize()
    );
}

void Game::SpawnEnemy(int choice, Entity_t type){
    // On parcourt la liste des ennemis et on vérifie si un ennemi est déjà inactif en fonction de son type
    for (Enemy& enemy : enemies){
        if (enemy.dead){
            if(enemy.GetType() == type){
                enemy.Current_HP = enemy.Max_HP;
                enemy.i = 0;
                enemy.dead = false;
                std::cout << enemy.dead << std::endl;
                PosEnemy(enemy, choice);
                return; // On sort de la fonction
            }
        }
    }
    switch (type){
    case GOBLIN: 
        Enemy new_enemy = Goblin(vec2<double>(0,0), assetManager);
        PosEnemy(new_enemy, choice);
        AddEnemy(
            new_enemy
        );
    }
}

/**
 * Rajoute un ennemi dans la liste d'ennemis (vector).
 * @param enemy l'ennemi à rajouter.
*/
void Game::AddEnemy(Enemy enemy){
    enemies.push_back(enemy);
}

/**
 * Détruit un ennemi.
 * @param id indexe de l'ennemi à détruire.
*/
void Game::DeleteEnemy(int id){
    enemies.erase(enemies.begin()+(id-1));
}

/**
 * Récupère un ennemi dans la liste d'ennemis (vector) via son indexe.
 * @param id indexe de l'ennemi à récupérer.
*/
Enemy& Game::GetEnemy(int id){
    return enemies[id];
}

/**
 * Rajoute une tour dans la liste des tours (vector).
 * @param indexe de la tour.
 * @param tower tour à ajouter.
*/
void Game::AddTower(Tower tower){

}

/**
 * Récupère une tour dans la liste (vector) via son indexe.
 * @param id l'ennemi à rajouter.
*/
