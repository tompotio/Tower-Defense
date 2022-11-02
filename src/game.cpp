#include "../include/game.hpp"

Game::Game()
{}

void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
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

    // Champ de déclaration des assets du jeu 
    AssetManager assetManager = AssetManager();

    assetManager.AddTexture(
        "enemyBlack1",
        TextureManager::LoadTexture("../assets/enemyBlack1.png",renderer)
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

    objective_t A;
    objective_t B;
    objective_t C;

    instances.objectives.push_back(A);
    instances.objectives.push_back(B);
    instances.objectives.push_back(C);

    instances.objectives[0].next = &B;
    instances.objectives[0].position = Vector2(100,100);

    instances.objectives[1].next = &C;
    instances.objectives[1].position = Vector2(400,200);

    instances.objectives[2].next = NULL;
    instances.objectives[2].position = Vector2(600,600);

    Enemy& enei = instances.GetEnemy(0);
    enei.SetObjective(
        instances.objectives[0]
    );

    Vector2 v = (*enei.GetObjective()).position - enei.GetPosition(); 
    v = Vector2(v.getX(),v.getY());
    v.normalizeVector();

    enei.SetDirection(v);
   
    /*
        Le menu se lance
            Choix jouer
                Choix de la carte
                Bouton start
            Choix son

        Le jeu se lance
            Une partie
                Lis la carte, 
                    Infos 
                        Position des tiles 
                        Position des objectifs 
    */

    /*
    instances.AddEnemy(
        Enemy(
            Vector2(
                300,
                300
            ),
            50,
            1,
            assetManager
        )
    );
    */
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

// On va séparer les autres updates fonctions
void Game::Update()
{   
    // Example de code pour charger la map
    /*
        SDL_Rect t{0,0, 16,16};
        for(int x = 0; x < 40; x++){
            for(int z = 0; z < 40; z++){
                SDL_Rect r{x*16,z*16, 16,16};

                SDL_RenderCopy(renderer,tileset,&t,&r);
            }
        }
    */
    
    for (auto enemy : instances.GetEnemies()) {
        TextureManager::BlitSprite(
            enemy.GetSprite(),
            renderer
        );
    }

    Enemy& e = instances.GetEnemy(0);
    Vector2 v = e.GetDirection();
    
    Vector2 ob_pos = (*e.GetObjective()).position;
    //ob_pos.printVector2();

    Vector2 dis = ob_pos - e.GetPosition();
    dis = Vector2(dis.getX(),dis.getY());

    //printf("%f \n",dis.getMag());
    
    // Vérifier que l'ennemi est aux alentours de l'objectif
    if (!(&dis == NULL)){
        if (dis.getMag() <= 10){
            //printf("Dépassement \n");
            for(int i = 0; i < instances.objectives.size(); i++){
                if (&(instances.objectives[i]) == e.GetObjective()){
                    printf("premier");
                    if ((i + 1) < instances.objectives.size()){
                        e.SetObjective(instances.objectives[i+1]);
                    }
                }
            }
            (*e.GetObjective()).position.printVector2();

            Vector2 v = (*e.GetObjective()).position - e.GetPosition(); 
            v = Vector2(v.getX(),v.getY());
            v.normalizeVector();

            e.SetDirection(v);
        }
    }
    
    v.setMag(e.GetSpeed());
    e.Move(
        v
    );
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