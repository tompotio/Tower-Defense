#include "../include/game.hpp"

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

    

    widgets.push_back(Widget("s-i", (WindowSize.w-185), 10, assetManager.GetTexture("sb")));
    widgets.push_back(Widget("tower1", 0, 0, assetManager.GetTexture("t1"), false));
    widgets.push_back(Widget("tower2", 0, 0, assetManager.GetTexture("t3"), false));
    widgets.push_back(Widget("tower3", 0, 0, assetManager.GetTexture("t2"), false));

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
    wave_ongoing = true; // Je bougerai cette valeur plus tard qui se mettra true après une petite fenêtre de dialogue dans le jeu avant de débuter la partie ! 
    isRunning = true;

    // Provisoire
    inventory_grid_cells = 5;
    inventory_grid_cells_size = 64;
    inventory_grid_offset = 10;
    inventory_pos_x = 300;
    inventory_pos_y = 735;


    Enemy new_enemy = Goblin(vec2<double>(0,0), assetManager);
    new_enemy.SetPosition(vec2<double>(WindowSize.w/2,WindowSize.h/2));
    enemies.push_back(new_enemy);
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
                
                for(Widget &widget : widgets) {
                    if (widget.isHovering(cursor.x, cursor.y)) {

                        if (widget.getId() == "s-i") {
                            (*menu)->isRunning = true;
                            (*menu)->isSetting = true;
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

    if (showgrid){
        //Affiche le curseur de la grille
        DrawCursor();

        // Affiche la grille map
        map.DrawGrid(renderer);
        int w;
        int h;
        TTF_SizeText(font, "FPS", &w, &h);
        apply_text(renderer,50,50,w,h,"FPS",font);

        char current_fps[100];
        sprintf(current_fps,"%d",fps);

        TTF_SizeText(font,current_fps, &w, &h);
        apply_text(renderer,100,50,w,h,current_fps,font);

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

    for(Tower &tower : towers) {
        
        tower.BlitTower(renderer);
        tower.DrawRange(renderer, grid_cell_size);
        tower.Fire(enemies);
        
    }
    

    
}

// Met à jour les unités du jeu.
void Game::UpdateGame(){

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

    if((wave_ongoing)){
        WaveManager();
        // For each sur les tours 

        MoveEnemies();
        ResetValuesForWave();
    }
    else{
        UpdateIntermit();
    }
}

/**
 * Fonction où l'on hard-code chaque wave
 * @param
**/
void Game::WaveManager(){
    Entity_t type; // type d'énnemis
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

    // On vérifie si tous les énnemis sont morts, sinon on met endwave à falses
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

void Game::UpdateIntermit(){
    if(seconds <= 5){
        // UpdateGraphics s'occupe d'afficher la fenêtre d'intermitence 
        intermit_screen = true;
    }else{
        intermit_screen = false;
        intermit_count = true;
        if(cpt_intermit == -1){
            cpt_intermit = INTERMITENCE_TIME;
        }else if(cpt_intermit == 0){
            intermit_count = false;
            wave_ongoing = true;
        }else{
            cpt_intermit -= 1;
        }
    }
}

void Game::UpdateTime(){
    // On met à jour le temps écoulé en milisecondes
    seconds_mil += deltatime;

    // Si une seconde vient de s'écouler seconds +=1
    if(int(seconds_mil) > seconds){
        seconds +=1;
        last_seconds_mil = seconds_mil;
    }
}

// Déplace les énnemis 
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

// Dessine les ennemis sur l'écran
void Game::DrawEnemies(){
    for (Enemy& enemy : enemies) {
        if(!enemy.dead){
            BlitSprite(
                enemy.GetSprite(),
                renderer
            );
            if (enemy.explode) {
                enemy.BlitExplosion(renderer);

            }
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
            cursor.x/grid_cell_size * grid_cell_size + (grid_cell_size / 2),
            cursor.y/grid_cell_size * grid_cell_size + (grid_cell_size / 2), assetmanager);

            towers.push_back(new_tower);
            c->tower_on = true;
        } 

    }

  
}

/**
 * Récupère une tour dans la liste (vector) via son indexe.
 * @param id l'ennemi à rajouter.
*/

