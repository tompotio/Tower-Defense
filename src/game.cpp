#include "../include/game.hpp"
#include <typeinfo>
/**
     * vague 1 : 5 goblins
     * vague 2 : 7 goblins et 2 elfes
     * vague 3 : 10 goblins et 4 elfs
     * vague 4 : 8 elfs
     * vague 5 : 20 goblins
     * vague 6 : 1 golem
     * vague 7 : 2 golems, 8 goblins et 4 elfs
     * vague 8 : 3 golems, 10 goblins et 6 elfs
     * vague 9 : 1 knights, 1 golem, 1 goblin et 1 elf
     * vague 10 : orc
     * vague 11 : 3 knights, 2 golems, 10 goblins, 5 elfs
     * vague 12 : 6 knights, 4 golems, 15 goblins, 10 elfs
*/

/**
 * Constructeur de la classe game. Initialise les éléments du jeu.
 * @param title Titre.
 * @param xpos Position en x de la fenêtre.
 * @param ypos Position en y de la fenêtre.
 * @param width Largeur de la fenêtre.
 * @param height Hauteur de la fenêtre.
 * @param fullscreen FullScreen ou non.
*/
Game::Game(Body** body, Menu** menu)
{   
    this->body = body;
    this->menu = menu;
    this->leftMouseButtonDown = false;
    this->tower1Selected = false;
    this->tower2Selected = false;
    this->tower3Selected = false;
    // this->isRunning = true;
    renderer = (*body)->GetRenderer();

    SDL_GetWindowSize((*body)->GetWindow(), &WindowSize.w, &WindowSize.h);

    // Champ de déclaration des assets du jeu 
    assetManager = AssetManager();

    font = load_font( "../assets/arial.ttf", 14);
    if (font == nullptr) std::cout << "ptdr null" << std::endl;


    assetManager.AddTexture(
        "sb",
        LoadTexture("../assets/PNG/Menu/settings/settings_button1.png", (*body)->GetRenderer())
    );

    assetManager.AddTexture(
        "sb2",
        LoadTexture("../assets/PNG/Menu/settings/sbutton_bg.png", (*body)->GetRenderer())
    );

    assetManager.AddTexture(
        "soldier",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile245.png",renderer)
    );
    assetManager.AddTexture(
        "fire_proj",
        LoadTexture("../assets/fire_proj.png", (*body)->GetRenderer())
    );

    assetManager.AddTexture(
        "commander",
        LoadTexture("../assets/commander.png", (*body)->GetRenderer())
    );

    assetManager.AddTexture(
        "sb",
        LoadTexture("../assets/PNG/Menu/settings/settings_button1.png", (*body)->GetRenderer())
    );

    assetManager.AddTexture(
        "sb2",
        LoadTexture("../assets/PNG/Menu/settings/sbutton_bg.png", (*body)->GetRenderer())
    );

    assetManager.AddTexture(
        "soldier",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile245.png",renderer)
    );
    assetManager.AddTexture(
        "soldier",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile245.png",renderer)
    );

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

    assetManager.AddTexture(
        "enemy_explosion",
        LoadTexture("../assets/tiles/Default size/towerDefense_tile296.png", renderer)
    );

    assetManager.AddTexture(
        "t1",
        LoadTexture("../assets/PNG/Menu/settings/tower1.png", renderer)
    );
    assetManager.AddTexture(
        "t2",
        LoadTexture("../assets/PNG/Menu/settings/tower2.png", renderer)
    );
    assetManager.AddTexture(
        "t3",
        LoadTexture("../assets/PNG/Menu/settings/tower3.png", renderer)
    );

    assetManager.AddTexture(
        "ice",
        LoadTexture("../assets/PNG/Menu/settings/ice2.png", renderer)
    );

    assetManager.AddTexture(
        "thunder",
        LoadTexture("../assets/PNG/Menu/settings/explosion2.png", renderer)
    );

    assetManager.AddTexture(
        "life_bar",
        LoadTexture("../assets/PNG/Menu/settings/life_bar.png", renderer)
    );

    

    widgets.push_back(Widget("s-i", (WindowSize.w-185), 10, assetManager.GetTexture("sb")));
    widgets.push_back(Widget("tower1", 0, 0, assetManager.GetTexture("t1"), false));
    widgets.push_back(Widget("tower2", 0, 0, assetManager.GetTexture("t3"), false));
    widgets.push_back(Widget("tower3", 0, 0, assetManager.GetTexture("t2"), false));
    widgets.push_back(Widget("life_bar", ((WindowSize.w-GetTextureSize(assetManager.GetTexture("life_bar")).w)/2), (WindowSize.h-100), assetManager.GetTexture("life_bar")));

    InitAnimationImage("coin", "../assets/PNG/Menu/settings/coin/", 8, 1, true);
    InitAnimationImage("ice", "../assets/PNG/Menu/settings/ice/", 7, 0.7, false);
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
    isRunning = true;
    playerMoney = 500;

    // Provisoire
    inventory_grid_cells = 5;
    inventory_grid_cells_size = 64;
    inventory_grid_offset = 10;
    inventory_pos_x = 530;
    inventory_pos_y = 695;


   /*  Enemy new_enemy = Goblin(vec2<double>(0,0), assetManager);
    new_enemy.SetPosition(vec2<double>(WindowSize.w/2,WindowSize.h/2));
    enemies.push_back(new_enemy); */
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
                leftMouseButtonDown = true;

                grid_cursor.x = (event.motion.x / grid_cell_size) * grid_cell_size;
                grid_cursor.y = (event.motion.y / grid_cell_size) * grid_cell_size;
                
                
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
                
                for(Widget &widget : widgets) {
                    if (widget.isHovering(cursor.x, cursor.y)) {

                        if (widget.getId() == "s-i") {
                            (*menu)->isRunning = true;
                            (*menu)->isSetting = true;
                            isRunning = false;
                            break;

                        }
                    } 
                }

                Cell* c = map.GetGridObject(cursor.x/grid_cell_size, cursor.y/grid_cell_size);

                if (c->tower_on) {
                    
                    for(Tower &tower : towers) {
                        int tower_case_x;
                        int tower_case_y;
                        tower.GetGridCase(&tower_case_x, &tower_case_y, grid_cell_size);
                        if (c->x == tower_case_x && c->y == tower_case_y) {

                            if (tower.GetShowRange()) {
                                tower.SetShowRange(false);

                            }
                            else {
                                tower.SetShowRange(true);

                            }
                        }
                        
                    }
                }
            }else if (event.button.button == SDL_BUTTON_RIGHT){
                showgrid = !showgrid;
                details = !details;
            }
            break;
        // Position de la souris
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT && leftMouseButtonDown){
                if (tower1Selected) {
                    AddTower(FIRE, assetManager);
                    tower1Selected = false;
                    GetWidget("tower1")->setActive(false);
                }
                if (tower2Selected) {
                    AddTower(ICE, assetManager);
                    tower2Selected = false;
                    GetWidget("tower2")->setActive(false);
                }
                if (tower3Selected) {
                    AddTower(THUNDER, assetManager);
                    tower3Selected = false;
                    GetWidget("tower3")->setActive(false);
                }
                leftMouseButtonDown = false;
            }


        case SDL_MOUSEMOTION:
            cursor = {event.motion.x, event.motion.y};
            grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
            grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;
            break;
        // Appuie une touche du clavier
        case SDL_KEYDOWN:
            // Touche K pour créer un nouveau chemin de test
            if (event.key.keysym.sym == SDLK_k){
                pressing_key_k = true;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            }
            if (event.key.keysym.sym == SDLK_f){
                show_fps = !show_fps;
            }
            if (event.key.keysym.sym == SDLK_e){
                show_enemies_range = !show_enemies_range;
            }
            if (event.key.keysym.sym == SDLK_g){
                showgrid = !showgrid;
            }
            break;
        // Lache une touche du clavier
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_k){
                pressing_key_k = false;
            }
            break;

        case SDL_QUIT:
            (*body)->setRunning(false);
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

    DrawSFX();

    apply_text(renderer,WindowSize.w/2,WindowSize.h/2,200,200,"MONEY",font);

    if (details){
        //Affiche le curseur de la grille
        DrawCursor();

        if(showgrid){
            // Affiche la grille map
            map.DrawGrid(renderer);
        }

        if(show_fps){
            //Affiche les FPS
            DrawFPS();
        }

        //Dessine les lignes du chemin
        if (found_testing_path){
            DrawPath(testingpath,orange);
        }
        DrawPath(bottompath,yellow_green);
    }

    for(Tower &tower : towers) {
        
        tower.BlitTower(renderer);

        tower.DrawRange(renderer, grid_cell_size);
        
    }
    for(Widget &widget : widgets) {
        if (widget.isHovering(cursor.x, cursor.y)) {
            if (widget.getId() == "s-i"){
                widget.setTexture(assetManager.GetTexture("sb2"));
            }
        }
        else {
            if (widget.getId() == "s-i"){
                widget.setTexture(assetManager.GetTexture("sb"));
            }
        }
        widget.BlitWidget(renderer);
    }


    // Affiche les projectiles
    DrawProjectiles();

    // Affiche une petite fenêtre de dialogue entre chaque wave
    if(intermit_screen){
        DrawDialogScreen();
    }

    if(intermit_count){
        DrawCount();
    }

    // Affiche l'inventaire
    DrawInventory();
    
    // Affiche la barre de vie
    DrawBaseHealthBar();

    //(couleur de fond de base du jeu)
    SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);

    for(Widget &widget : widgets) {
        if (widget.isHovering(cursor.x, cursor.y)) {

            if (widget.getId() == "s-i"){
                widget.setTexture(assetManager.GetTexture("sb2"));

            }

        }
        else {
            if (widget.getId() == "s-i"){
                widget.setTexture(assetManager.GetTexture("sb"));
            }
        
        }
        widget.BlitWidget(renderer);
        
    }

    DrawAnimation("coin", 1200, 800);
    DrawAnimation("ice", 500, 500);

    

    
}

// Met à jour les unités du jeu.
void Game::UpdateGame(){


    GameOver();
    for(int i = 0; i < inventory_grid_cells; i++) {
        
        SDL_Rect rect = {
            (i * (inventory_grid_cells_size + inventory_grid_offset)) + inventory_pos_x,
            inventory_pos_y,
            inventory_grid_cells_size,
            inventory_grid_cells_size
        };

        if (SDL_PointInRect(&cursor, &rect) && leftMouseButtonDown) {

            if(i==0 && tower2Selected == false && tower3Selected == false) {
                tower1Selected = true;
                GetWidget("tower1")->setActive(true);

            }
            if(i==1 && tower1Selected == false && tower3Selected == false) {
                tower2Selected = true;
                GetWidget("tower2")->setActive(true);

            }
            if(i==2 && tower1Selected == false && tower2Selected == false) {
                tower3Selected = true;
                GetWidget("tower3")->setActive(true);

            }
        }
        
        
    }

    

    if (tower1Selected) {
        GetWidget("tower1")->setX(cursor.x - GetWidget("tower1")->getRect().w/2);
        GetWidget("tower1")->setY(cursor.y - GetWidget("tower1")->getRect().h/2);
    }

    if (tower2Selected) {
        GetWidget("tower2")->setX(cursor.x - GetWidget("tower2")->getRect().w/2);
        GetWidget("tower2")->setY(cursor.y - GetWidget("tower2")->getRect().h/2);
    }
    if (tower3Selected) {
        GetWidget("tower3")->setX(cursor.x - GetWidget("tower3")->getRect().w/2);
        GetWidget("tower3")->setY(cursor.y - GetWidget("tower3")->getRect().h/2);
    }

    UpdateTime();
    TowerSelection();

    if((wave_ongoing)){
        WaveManager();
        MoveEnemies();
        MoveProjectiles();
        TowersAttack();
        // Si la wave s'est terminée, la fonction va remettre à niveau les valeurs
        ResetValuesForWave();
    }else{
        UpdateIntermit();
    }
}

void Game::DrawFPS(){
    int w;
    int h;
    TTF_SizeText(font, "FPS", &w, &h);
    apply_text(renderer,50,50,w,h,"FPS",font);

    char current_fps[100];
    sprintf(current_fps,"%d",fps);

    TTF_SizeText(font,current_fps, &w, &h);
    apply_text(renderer,100,50,w,h,current_fps,font);
}

// Dessine le compteur du temps avant le début de chaque wave à l'écran
void Game::DrawCount(){
    int w;
    int h;

    char current_count[100];
    sprintf(current_count,"%d",cpt_intermit);

    TTF_SizeText(font, "The wave will start in : ", &w, &h);
    apply_text(renderer,1100,500,w,h,"The wave will start in : ",font);

    TTF_SizeText(font,current_count, &w, &h);
    apply_text(renderer,1250,500,w,h,current_count,font);
}

// Fonction qui gère la sélection des tours
void Game::TowerSelection(){
    for(int i = 0; i < inventory_grid_cells; i++) {
        SDL_Rect rect = {
            (i * (inventory_grid_cells_size + inventory_grid_offset)) + inventory_pos_x,
            inventory_pos_y,
            inventory_grid_cells_size,
            inventory_grid_cells_size
        };
        if (SDL_PointInRect(&cursor, &rect) && leftMouseButtonDown) {
            if(i==0 && tower2Selected == false && tower3Selected == false) {
                tower1Selected = true;
                GetWidget("tower1")->setActive(true);
            }
            if(i==1 && tower1Selected == false && tower3Selected == false) {
                tower2Selected = true;
                GetWidget("tower2")->setActive(true);
            }
            if(i==2 && tower1Selected == false && tower2Selected == false) {
                tower3Selected = true;
                GetWidget("tower3")->setActive(true);
            }
        }
    }

    if (tower1Selected) {
        GetWidget("tower1")->setX(cursor.x - GetWidget("tower1")->getRect().w/2);
        GetWidget("tower1")->setY(cursor.y - GetWidget("tower1")->getRect().h/2);
    }

    if (tower2Selected) {
        GetWidget("tower2")->setX(cursor.x - GetWidget("tower2")->getRect().w/2);
        GetWidget("tower2")->setY(cursor.y - GetWidget("tower2")->getRect().h/2);
    }
    if (tower3Selected) {
        GetWidget("tower3")->setX(cursor.x - GetWidget("tower3")->getRect().w/2);
        GetWidget("tower3")->setY(cursor.y - GetWidget("tower3")->getRect().h/2);
    }
}

/**
 * En fonction du type de tour on lance un effet différent
 * @param tower attaque de la tour à lancer
*/
void Game::TowerAttackCase(Tower& tower){
    switch(tower.type){
        case FIRE:
        {
            Enemy* closest_enemy = nullptr; // remplacer NULL par tower.FindNearestEnemy();
            //Cherche le plus proche ennemi
            for (Enemy& enemy : enemies) {
                int closest = tower.range;
                if(!enemy.dead){
                    int a = tower.GetRect().x;
                    int b = tower.GetRect().y;
                    double c = enemy.GetSprite().GetRect().x + enemy.GetSprite().GetRect().w/2;
                    double d = enemy.GetSprite().GetRect().y + enemy.GetSprite().GetRect().h/2;
                    int dist = int(pow(pow(c-a, 2) + pow(d-b, 2), 0.5));
                    if (dist <= closest) {
                        closest = dist;
                        closest_enemy = &enemy;
                    }
                }
            }
            // Si on a trouvé un ennemi
            if(!(closest_enemy == nullptr)){
                // On vérifie le CD de la tour
                if(tower.CD >= tower.cadence){
                    tower.CD = 0;
                    vec2<double> position = vec2<double>(tower.GetRect().x,tower.GetRect().y);
                    SpawnProjectile(position, closest_enemy);
                }
            }
            break;
        }
        case ICE:
        {
            
            if (seconds % tower.cadence == 0 && (last_seconds_mil == seconds_mil)) {
                //AddSfx(tower.effect_texture, tower.GetRect().x, tower.GetRect().y);
                std::vector<Enemy*> e;
                for (Enemy& enemy : enemies) {

                    if(!enemy.dead){
                        int a = tower.GetRect().x;
                        int b = tower.GetRect().y;
                        double c = enemy.GetSprite().GetRect().x + enemy.GetSprite().GetRect().w/2;
                        double d = enemy.GetSprite().GetRect().y + enemy.GetSprite().GetRect().h/2;


                        if ( int(pow(pow(c-a, 2) + pow(d-b, 2), 0.5)) <= tower.range) {
                            e.push_back(&enemy);

                        } 
                    
                    } 
                }
                std::cout << "ENEMY : NUM : " <<  e.size() << std::endl;
                if (e.size() > 0) {
                    LaunchAnimation("ice", tower.GetRect().x, tower.GetRect().y, 1);
                    for (Enemy* enemy : e) {
                        //enemy.Current_HP -= tower.degat;
                        enemy->Current_HP = 0;
                        
                    }
                }
                
                
            }
            
            break;
        }

        case THUNDER:
        {

            if (seconds % tower.cadence == 0 && (last_seconds_mil == seconds_mil)) {
                int closest = tower.range;
                Enemy* closest_enemy = NULL;
                for (Enemy& enemy : enemies) {

                    if(!enemy.dead){
                        int a = tower.GetRect().x;
                        int b = tower.GetRect().y;
                        double c = enemy.GetSprite().GetRect().x + enemy.GetSprite().GetRect().w/2;
                        double d = enemy.GetSprite().GetRect().y + enemy.GetSprite().GetRect().h/2;

                        int dist = int(pow(pow(c-a, 2) + pow(d-b, 2), 0.5));
                        if ( dist <= closest) {
                            closest = dist;
                            closest_enemy = &enemy;
                            
                        } 
                        
                        

                    } 
                }
                if (closest_enemy != NULL) {
                    if(tower.CD >= tower.cadence){
                        tower.CD = 0;
                        closest_enemy->Current_HP -= tower.degat;
                        //AddSfx(tower.effect_texture, tower.GetRect().x, tower.GetRect().y);
                        AddSfx(closest_enemy->explosion, closest_enemy->GetSprite().GetRect().x + closest_enemy->GetSprite().GetRect().w/2, closest_enemy->GetSprite().GetRect().y + closest_enemy->GetSprite().GetRect().h/2);
                    }
                    

                }

            }
            break;
        }
        default:
            break;
    }
}

// Fonction qui gère les attaques de chaque tour en les parcourant
void Game::TowersAttack(){
    for(Tower& tower : towers){
        tower.CD += deltatime;
        TowerAttackCase(tower);
    }
}

/**
 * Fonction où l'on hard-code chaque wave pour les ennemis
 * @param
**/
void Game::WaveManager(){
    Entity_t type; // type d'ennemis
    int path; // Génère un nombre "aléatoire" en 1 et 2 pour choisir le chemin

    // Crée un goblin toutes les 4 secondes
    if(((seconds % 4) == 0) && (last_seconds_mil == seconds_mil)){
        // Je me sers de goblin_max_nb pour savoir si je dois faire spawn un ennemi (si le max est à 0, aucun ennemi de ce type spawnera à cette manche)
        if((goblin_nb < goblin_max_nb) && (goblin_max_nb > 0)){
            goblin_nb +=1;
            type = GOBLIN;
            path = rand() % 2 +1;
            SpawnEnemy(path, type);
        }
    }
    // Crée un elfe toutes les 8 secondes
    if(((seconds % 8) == 0) && (last_seconds_mil == seconds_mil)){
        // Je me sers de goblin_max_nb pour savoir si je dois faire spawn un ennemi (si le max est à 0, aucun ennemi de ce type spawnera à cette manche)
        if((elf_nb < elf_max_nb) && (elf_max_nb > 0)){
            elf_nb +=1;
            type = ELF;
            path = rand() % 2 +1;
            SpawnEnemy(path, type);
        }
    }
    // Crée un golem toutes les 13 secondes
    if(((seconds % 13) == 0) && (last_seconds_mil == seconds_mil)){
        // Je me sers de goblin_max_nb pour savoir si je dois faire spawn un ennemi (si le max est à 0, aucun ennemi de ce type spawnera à cette manche)
        if((golem_nb < golem_max_nb) && (golem_max_nb > 0)){
            golem_nb +=1;
            type = GOLEM;
            path = rand() % 2 +1;
            SpawnEnemy(path, type);
        }
    }
    // Crée un knight toutes les 10 secondes
    if(((seconds % 10) == 0) && (last_seconds_mil == seconds_mil)){
        // Je me sers de goblin_max_nb pour savoir si je dois faire spawn un ennemi (si le max est à 0, aucun ennemi de ce type spawnera à cette manche)
        if((knight_nb < goblin_max_nb) && (knight_max_nb > 0)){
            knight_nb +=1;
            type = KNIGHT;
            path = rand() % 2 +1;
            SpawnEnemy(path, type);
        }
    }
    // Crée un orc toutes les 15 secondes
    if(((seconds % 15) == 0) && (last_seconds_mil == seconds_mil)){
        // Je me sers de goblin_max_nb pour savoir si je dois faire spawn un ennemi (si le max est à 0, aucun ennemi de ce type spawnera à cette manche)
        if((orc_nb < orc_max_nb) && (orc_max_nb > 0)){
            orc_nb +=1;
            type = ORC;
            path = rand() % 2 +1;
            SpawnEnemy(path, type);
        }
    }
}

//Reset les valeurs de chaque wave
void Game::ResetValuesForWave(){
    bool endwave = true;
    if((golem_nb + knight_nb + orc_nb + goblin_nb + elf_nb) == 0) endwave = false;

    // On vérifie si tous les ennemis sont morts, sinon on met endwave à falses
    for(auto enemy: enemies){
        if(!(enemy.dead)){
            endwave = false;
            break;
        }
    }

    if(endwave){
        // Valeurs constantes (compteurs)
        goblin_nb = 0;
        elf_nb = 0;
        orc_nb = 0;
        golem_nb = 0;
        knight_nb = 0;

        goblin_max_nb = 0;
        elf_max_nb = 0;
        golem_max_nb = 0;
        knight_max_nb = 0;
        orc_max_nb = 0;
        wave_nb += 1;

        wave_ongoing = false;
        delta_s = 0;
        seconds_mil = 0;
        last_seconds_mil = 0;
        seconds = 0;
        cpt_intermit = -1; 

        // Valeurs dépendantes du numéro de waves
        switch (wave_nb)
        {
        case 2:
            goblin_max_nb = 7;
            elf_max_nb = 2;
            break;
        case 3:
            goblin_max_nb = 10;
            elf_max_nb = 4;
            break;
        case 4:
            elf_max_nb = 8;
            break;
        case 5:
            goblin_max_nb = 20;
            break;
        case 6:
            golem_max_nb = 1;
            break;
        case 7:
            golem_max_nb = 2;
            goblin_max_nb = 8;
            elf_max_nb = 4;
            break;
        case 8:
            golem_max_nb = 3;
            goblin_max_nb = 10;
            elf_max_nb = 6;
            break;
        case 9:
            knight_max_nb = 1;
            golem_max_nb = 1;
            goblin_max_nb = 1;
            elf_max_nb = 1;
            break;
        case 10:
            orc_max_nb = 1;
            break;
        case 11:
            knight_max_nb = 3;
            golem_max_nb = 2;
            goblin_max_nb = 10;
            elf_max_nb = 5;
            break;
        case 12:
            knight_max_nb = 6;
            golem_max_nb = 4;
            goblin_max_nb = 15;
            elf_max_nb = 10;
            break;
        default:
            break;
        }
    }
}

void Game::DrawDialogScreen(){
    SDL_Rect fond = {100,490,1380, 150};
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, 165);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &fond);

    BlitTexture(
        assetManager.GetTexture("commander"),
        renderer,
        0,
        440
    );
}

void Game::UpdateIntermit(){
    if(!intermit_count){
        intermit_screen = true;
        cpt_intermit = INTERMITENCE_TIME;
    }

    if(cpt_intermit <= 0){
        intermit_count = false;
        intermit_screen = false;
        wave_ongoing = true;
    }
    if(last_seconds_mil == seconds_mil){
        cpt_intermit -= 1;
    }
    if(!intermit_count && cpt_intermit == INTERMITENCE_TIME) intermit_count = true;
}

// Met à jour le compteur du temps (secondes)
void Game::UpdateTime(){

    // On met à jour le temps écoulé en milisecondes
    seconds_mil += deltatime;

    // Si une seconde vient de s'écouler seconds +=1
    if(int(seconds_mil) > seconds){
        seconds +=1;
        last_seconds_mil = seconds_mil;
    }
}

// Déplace tous les projectiles (en l'occurence les projectiles à tête chercheuse)
void Game::MoveProjectiles(){
    for(HomingProjectile & proj : projectiles){
        // Si le missile n'a pas été désactivé alors le fait avancer
        if(proj.active){
            // On vérifie si le dernier déplacement n'a pas rapprocher suffisamment le missile de l'ennemi
            vec2<double> vecteur_distance;
            vec2<double> POS_ENNEMI = vec2<double>(proj.target->GetPosition().x, proj.target->GetPosition().y);
            vecteur_distance = POS_ENNEMI - proj.position;
            proj.UpdateDirection(vecteur_distance);

            // Si l'ennemi est vivant
            if(proj.target->dead){
                proj.active = false;
            }

            // Le missile est suffisamment proche de l'ennemi pour le percuter, même si l'ennemi est mort
            if(vecteur_distance.length() <= 16){
                // Ajouter une animation d'explosion si possible
                proj.target->Current_HP -= proj.dmg;
                if(proj.target->Current_HP <= 0){
                    proj.target->dead = true;
                }
                proj.active = false;
            }else{
                proj.position = (proj.direction * (deltatime * proj.speed)) + proj.position;
            }
        }   
    }
}

// Déplace les ennemis 
void Game::MoveEnemies(){
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

void Game::DrawProjectiles(){
    for (HomingProjectile& proj : projectiles) {
        if(proj.active){
            proj.animationstep = (proj.animationstep + 1) % 2;
            SDL_Rect srcrect;
            srcrect.w = 32;
            srcrect.h = 32;
            srcrect.x = 32 * proj.animationstep;
            srcrect.y = 0;

            SDL_Rect dstcrect;
            dstcrect.w = 32;
            dstcrect.h = 32;
            dstcrect.x = proj.position.x + 16;
            dstcrect.y = proj.position.y;
        
            SDL_RenderCopy(renderer, proj.texture, &srcrect, &dstcrect);
        }
    }
}

// Dessine les ennemis sur l'écran
void Game::DrawEnemies() {
    for (Enemy& enemy : enemies) {
        if(!enemy.dead){
            BlitSprite(
                enemy.GetSprite(),
                renderer
            );
            
    
            if (enemy.Current_HP <= 0) {
                enemy.dead = true;
            }
            if(enemy.selected && show_enemies_range && details){
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                
                int diameter = (32);

                int x = (16 - 1);
                int y = 0;
                int tx = 1;
                int ty = 1;
                int error = (tx - diameter);

                vec2<double> pos = enemy.GetPosition();
                int w = enemy.GetSprite().GetRect().w;
                int h = enemy.GetSprite().GetRect().h;

                while (x >= y)
                {
                    //  Each of the following renders an octant of the circle
                    SDL_RenderDrawPoint(renderer, pos.x + x + w/2, pos.y - y + h/2);
                    SDL_RenderDrawPoint(renderer, pos.x + x + w/2, pos.y + y + h/2);
                    SDL_RenderDrawPoint(renderer, pos.x - x + w/2, pos.y - y + h/2);
                    SDL_RenderDrawPoint(renderer, pos.x - x + w/2, pos.y + y + h/2);
                    SDL_RenderDrawPoint(renderer, pos.x + y + w/2, pos.y - x + h/2);
                    SDL_RenderDrawPoint(renderer, pos.x + y + w/2, pos.y + x + h/2);
                    SDL_RenderDrawPoint(renderer, pos.x - y + w/2, pos.y - x + h/2);
                    SDL_RenderDrawPoint(renderer, pos.x - y + w/2, pos.y + x + h/2);

                    if (error <= 0)
                    {
                        ++y;
                        error += ty;
                        ty += 2;
                    }

                    if (error > 0)
                    {
                        --x;
                        tx += 2;
                        error += (tx - diameter);
                    }
                }
            }
        }
    }
}

/**
 * Dessine un chemin généré (peut être utilisé pour débugger ou simplement avoir l'affichage).
 * @param path le chemin de cellules à afficher.
 * @param color couleur que le chemin doit prendre.
*/
void Game::DrawPath(std::vector<Cell> path, SDL_Color color) {
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
   /*  SDL_Rect fond = {900,750,3 * base_HP, 10};
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderFillRect(renderer, &fond); */

    if(current_HP >= 0){
                                                        
        SDL_Rect vie = {GetWidget("life_bar")->getRect().x + 16, (WindowSize.h-100+16),(int)(540 * ((double)current_HP/100)), 20};
        SDL_SetRenderDrawColor(renderer, lime.r, lime.g, lime.b, lime.a);
        SDL_RenderFillRect(renderer, &vie);
    }
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
        if (i==0) {
            SDL_RenderCopy(renderer, assetManager.GetTexture("t1"), NULL, &rect);
        }
        if (i==1) {
            SDL_RenderCopy(renderer, assetManager.GetTexture("t3"), NULL, &rect);
        }
        if (i==2) {
            SDL_RenderCopy(renderer, assetManager.GetTexture("t2"), NULL, &rect);
        }

    }
}

// Dessine les tiles
void Game::DrawTiles()
{
    for(int x = 0; x < map_x_size; x++){
        for(int y = 0; y < map_y_size; y++){

            Cell* c = map.GetGridObject(x,y);
          
            switch(c->type){
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

void Game::SpawnProjectile(vec2<double> pos, Enemy* target){
    // On parcourt la liste des ennemis et on vérifie si un ennemi est déjà inactif en fonction de son type
    for (HomingProjectile& proj : projectiles){
        if (!proj.active){
            proj.position = pos;
            proj.target = target;
            proj.active = true;
            return; // On sort de la fonction
        }
    }
    HomingProjectile newproj = HomingProjectile(pos, assetManager, target);
    projectiles.push_back(newproj);
}

void Game::SpawnEnemy(int choice, Entity_t type){
    // On parcourt la liste des ennemis et on vérifie si un ennemi est déjà inactif en fonction de son type
    for (Enemy& enemy : enemies){
        if (enemy.dead){
            if(enemy.GetType() == type){
                enemy.Current_HP = enemy.Max_HP;
                enemy.i = 0;
                enemy.dead = false;
                PosEnemy(enemy, choice);
                return; // On sort de la fonction
            }
        }
    }
    if(type == GOBLIN){
        Enemy goblin = Goblin(vec2<double>(0,0), assetManager);
        PosEnemy(goblin, choice);
        AddEnemy(
            goblin
        );
    }else if(type == GOLEM){
        Enemy golem = Golem(vec2<double>(0,0), assetManager);
        PosEnemy(golem, choice);
        AddEnemy(
            golem
        );
    }else if(type == ELF){
        Enemy elf = Elf(vec2<double>(0,0), assetManager);
        PosEnemy(elf, choice);
        AddEnemy(
            elf
        );
    }else if(type == KNIGHT){
        Enemy knight = Knight(vec2<double>(0,0), assetManager);
        PosEnemy(knight, choice);
        AddEnemy(
            knight
        );
    }else if(type == ORC){
        Enemy orc = Orc(vec2<double>(0,0), assetManager);
        PosEnemy(orc, choice);
        AddEnemy(
            orc
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

Widget* Game::GetWidget(std::string id) {
    for(Widget &widget : widgets) {
        if (widget.getId() == id) {return &widget;}
    }
    for(Widget &widget : sfx) {
        if (widget.getId() == id) {return &widget;}
    }
    
    return NULL;
}

Widget* Game::GetWidgetAnimation(std::string id, int index) {
    for(Widget &widget : animation[index]) {
        if (widget.getId() == id) {return &widget;}
    }
    
    return NULL;
}

/**
 * Rajoute une tour dans la liste des tours (vector).
 * @param indexe de la tour.
 * @param tower tour à ajouter.
*/
void Game::AddTower(Tower_t type, AssetManager assetmanager){
    if ((mouse_X >= 0) &&
    (mouse_X < (map.GetWidth() * grid_cell_size)) && 
    (mouse_Y >= 0 && mouse_Y < (map.GetHeight() * grid_cell_size))) {
        
        Cell* c = map.GetGridObject(cursor.x/grid_cell_size, cursor.y/grid_cell_size);

        if (c->type == '1' && c->tower_on == false) {
            Tower new_tower = Tower(type,
            c->x * grid_cell_size + (grid_cell_size/2),
            c->y * grid_cell_size + (grid_cell_size/2), assetmanager);


            
            towers.push_back(new_tower);
            c->tower_on = true;
        } 

    }

  
}

void Game::DrawSFX() {
    for (Widget& effect : sfx) {
        
        if (effect.getId()[0] != 'a') {
            if (effect.timer_actual > 0) {
                BlitTexture(effect.getTexture(), renderer, effect.getRect().x, effect.getRect().y);
                effect.timer_actual -= deltatime;
            }
        }
    }
}
void Game::AddSfx(SDL_Texture* texture, int x, int y) {
    
    
    SDL_Rect r = GetTextureSize(texture);
    x = x-r.w/2;
    y = y-r.h/2;

    std::string s = std::to_string(x)+", "+std::to_string(y);
    Widget* w = GetWidget(s);
    if (w==NULL) {
        sfx.push_back(Widget(s, x, y, texture));

    }
    else {
        w->timer_actual = w->timer_init;
        std::cout << "OHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH MERDE" << std::endl;
    }


}

void Game::InitAnimationImage(std::string tag, std::string path, int number, double anim_time, bool infinite) {
    std::vector<Widget> t;
    animation.push_back(t);
    
    for (int z=0; z<number; z++) {
        std::string frame_name = "a-" + tag + "_" + std::to_string(z);
        assetManager.AddTexture(
            frame_name,
            LoadTexture((path+tag+std::to_string(z)+".png").c_str(), renderer)
        );
        std::cout << "LOADED" << (path+tag+std::to_string(z)+".png")<< std::endl;
        if (infinite) {
            animation[animation.size()-1].push_back(Widget(frame_name, 0, 0, assetManager.GetTexture(frame_name), (z==0), anim_time/number, -1));
            
        }
        else {
            animation[animation.size()-1].push_back(Widget(frame_name, 0, 0, assetManager.GetTexture(frame_name), (z==0), anim_time/number, 0));
        }
    }
    std::cout << "NUMBER" <<  animation.size() << " coin size: " << animation[0].size() << std::endl;

}
void Game::DrawAnimation(std::string tag, int x, int y) {
    std::vector<int> c;
    for (int i = 0; i < animation.size(); i++){
        Widget effect = animation[i][0];
        if (effect.getId()[0] == 'a' && (effect.getId().find(tag) != std::string::npos)) {
            c.push_back(i);
            
        }
    }

    
    //std::cout << "NUMBER : " << c.size() << std::endl;
    //std::cout << " BLIT : X  : " << cursor.x << " Y :  " << cursor.y << std::endl;

    for (int j : c) { 
        for (int i = 0; i < animation[j].size(); i++){
            Widget* effect = &animation[j][i];
            
            if (effect->getActive() && (effect->number_print > 0 || effect->number_print==-1)) {
                if (effect->timer_actual > 0) {
                    if (effect->number_print == -1) {
                        BlitTexture(effect->getTexture(), renderer, x, y);

                    }
                    else {
                        BlitTexture(effect->getTexture(), renderer, effect->getRect().x - GetTextureSize(effect->getTexture()).w/2, effect->getRect().y - GetTextureSize(effect->getTexture()).h/2);
                    }
                    effect->timer_actual -= deltatime; 

                }
                else {
                    //std::cout << "first: " << effect->getId() << " active : " << effect->getActive() << std::endl;

                    effect->timer_actual = effect->timer_init;
                    effect->setActive(false);
                    if (effect->number_print != -1) {
                        effect->number_print -= 1;
                    }
                    GetWidgetAnimation("a-" + tag + "_" + std::to_string((i+1)%animation[j].size()), j)->setActive(true);
                }

            }
        }
    }

}

void Game::LaunchAnimation(std::string tag, int x, int y, int number) {
    
    bool found = false;
    std::vector<Widget> t;
    std::cout << "SIZE ANIMATION : " << animation.size() << std::endl;
    for (int i = 0; i < animation.size(); i++){
        //std::cout << "NAME 0 INDEX : " << animation[i][0].getId() << std::endl;
        if (animation[i][0].getId()[0] == 'a' && (animation[i][0].getId().find(tag) != std::string::npos)) {
            int total = 0;
            
            for (int j = 0; j < animation[i].size(); j++){
                Widget* effect = &animation[i][j];
                // std::cout << "NAME  : " << animation[i][0].getId() << " " << effect->number_print << std::endl;

                total += effect->number_print;
                
            }
            if (total == 0) {
                found = true;
                for (int z = 0; z < animation[i].size(); z++){
                    Widget* effect = &animation[i][z];

                    if (effect->getId()[0] == 'a' && (effect->getId().find(tag) != std::string::npos)) {

                        effect->setX(x);
                        effect->setY(y);                   
                        effect->number_print = number;

                    }
                }
                break;
                
            }
            else {
                t = animation[i];
            }
            
        }
        
        
    }

    
    if (found == false) {
        std::cout << "CREATE NEWW  : " << std::endl;
        for (int i = 0; i < t.size(); i++){
            Widget* effect = &t[i];

            effect->setX(x);
            effect->setY(y);
            effect->number_print = number;
        }
        animation.push_back(t);
    }
 
    

}
void Game::GameOver(){
    
    if(current_HP <= 0){
        (*menu)->isRunning = true;
        (*menu)->isSetting = true;
        isRunning = false;

        ResetEverything();
    }
}

void Game::ResetEverything(){
    
    
}
