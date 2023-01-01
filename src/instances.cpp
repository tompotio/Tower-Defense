#include "../include/instances.hpp"

Goblin::Goblin(vec2<double> spawnPosition, AssetManager& assetmanager){
    this->Max_HP = GOBLIN_HP;
    this->Current_HP = Max_HP;
    this->speed = GOBLIN_SPEED;

    SDL_Texture* texture = assetmanager.GetTexture("zombie");
    int w;
    int h;
    this->dmg = 5;
    this->type = GOBLIN;
    this->dead = false;
    this->explosion = assetmanager.GetTexture("enemy_explosion");
    this->explode = false;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);

    this->sprite = Sprite(
        SDL_Rect {
            (int) position.x,
            (int) position.y,
            w,
            h
        },
        texture
    );
}

Elf::Elf(vec2<double> spawnPosition, AssetManager& assetmanager){
    this->Max_HP = ELF_HP;
    this->Current_HP = Max_HP;
    this->speed = ELF_SPEED;

    SDL_Texture* texture = assetmanager.GetTexture("soldier");
    int w;
    int h;
    this->dmg = 5;
    this->type = ELF;
    this->dead = false;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);

    this->sprite = Sprite(
        SDL_Rect {
            (int) position.x,
            (int) position.y,
            w,
            h
        },
        texture
    );
}

Golem::Golem(vec2<double> spawnPosition, AssetManager& assetmanager){
    this->Max_HP = GOLEM_HP;
    this->Current_HP = Max_HP;
    this->speed = GOLEM_SPEED;

    SDL_Texture* texture = assetmanager.GetTexture("zombie");
    int w;
    int h;
    this->dmg = 5;
    this->type = GOLEM;
    this->dead = false;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);

    this->sprite = Sprite(
        SDL_Rect {
            (int) position.x,
            (int) position.y,
            w,
            h
        },
        texture
    );
}

Knight::Knight(vec2<double> spawnPosition, AssetManager& assetmanager){
    this->Max_HP = KNIGHT_HP;
    this->Current_HP = Max_HP;
    this->speed = KNIGHT_SPEED;

    SDL_Texture* texture = assetmanager.GetTexture("zombie");
    int w;
    int h;
    this->dmg = 5;
    this->type = KNIGHT;
    this->dead = false;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);

    this->sprite = Sprite(
        SDL_Rect {
            (int) position.x,
            (int) position.y,
            w,
            h
        },
        texture
    );
}

Orc::Orc(vec2<double> spawnPosition, AssetManager& assetmanager){
    this->Max_HP = ORC_HP;
    this->Current_HP = Max_HP;
    this->speed = ORC_SPEED;

    SDL_Texture* texture = assetmanager.GetTexture("zombie");
    int w;
    int h;
    this->dmg = 5;
    this->type = ORC;
    this->dead = false;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);

    this->sprite = Sprite(
        SDL_Rect {
            (int) position.x,
            (int) position.y,
            w,
            h
        },
        texture
    );
}

// Récupère la position de l'ennemi
vec2<double>& Enemy::GetPosition(){
    return position;
}

void Enemy::SetDirection(vec2<double>  direction){
    this->direction = direction;
}

// Change la position de l'ennemi et met à jour sprite (à cause du rect)
void Enemy::SetPosition(vec2<double>  pos){
    this->position = pos;

    // Met à jour le rect 
    SDL_Rect rect;

    rect.w = this->sprite.GetRect().w;
    rect.h = this->sprite.GetRect().h;
    rect.x = (int) position.x;
    rect.y = (int) position.y;

    sprite.SetRect(rect);
}

// Déplace l'ennemi via un vecteur
void Enemy::Move(vec2<double>  step){
    SetPosition(step + position);
}

void Enemy::BlitExplosion(SDL_Renderer* renderer) {
    BlitTexture(explosion, renderer, position.x, position.y);
}

Tower::Tower(Tower_t type, int x, int y, AssetManager assets) {

    switch (type) {
        case FIRE:
            this->texture = assets.GetTexture("t1");
            this->range = 300;
            this->cadence = 10; // tte les 3sec
            this->degat = 100;

            break;

        case ICE:
            this->texture = assets.GetTexture("t3");
            this->range = 100;
            this->cadence = 10; // 1 fois par sec ou 2 / sec
            this->degat = 1;


            break;
        
        case THUNDER:
            this->texture = assets.GetTexture("t2");
            this->range = 200;
            this->cadence = 10; // tte les 2 sec
            this->degat = 50;


            break;

        default:
            break;

    }
    this->target = nullptr;
    this->showrange = false;
    this->type = type;
    this->rect = GetTextureSize(texture);
    this->rect.x = x-rect.w/2;
    this->rect.y = y-rect.h/2;
}

void Tower::BlitTower(SDL_Renderer* renderer) {
    BlitTexture(this->texture, renderer, this->rect.x, this->rect.y);

}

void Tower::GetGridCase(int* x, int* y, int grid_cell_size) {
    *x = rect.x/grid_cell_size + 1;
    *y = rect.y/grid_cell_size + 1;
}


void Tower::DrawRange(SDL_Renderer * renderer, int cell_size)
{
    if (this->showrange) {
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
        

        SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
        SDL_SetRenderDrawColor(renderer, 127, 255, 0, 255);
        
        const int32_t diameter = (range * 2);

        int32_t x = (range - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(renderer, rect.x + x + rect.w/2, rect.y - y + rect.h/2);
            SDL_RenderDrawPoint(renderer, rect.x + x + rect.w/2, rect.y + y + rect.h/2);
            SDL_RenderDrawPoint(renderer, rect.x - x + rect.w/2, rect.y - y + rect.h/2);
            SDL_RenderDrawPoint(renderer, rect.x - x + rect.w/2, rect.y + y + rect.h/2);
            SDL_RenderDrawPoint(renderer, rect.x + y + rect.w/2, rect.y - x + rect.h/2);
            SDL_RenderDrawPoint(renderer, rect.x + y + rect.w/2, rect.y + x + rect.h/2);
            SDL_RenderDrawPoint(renderer, rect.x - y + rect.w/2, rect.y - x + rect.h/2);
            SDL_RenderDrawPoint(renderer, rect.x - y + rect.w/2, rect.y + x + rect.h/2);

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

        SDL_SetRenderDrawColor(renderer, r, g, b, a);

    }
}

void Tower::Fire(std::vector<Enemy> enemies) {
    switch (type) {
        case FIRE:
            
            break;

        case ICE:
            // if (cadence = time) {}
            /* for (Enemy& enemy : enemies) {

                if(!enemy.dead){
                    int a = rect.x + rect.w/2;
                    int b = rect.y + rect.h/2;
                    double c = enemy.GetPosition().x;
                    double d = enemy.GetPosition().y;

                    //std::cout << "range " << pow(pow(c-a, 2) + pow(d-b, 2), 0.5) << " " << range << std::endl;

                    if ( pow(pow(c-a, 2) + pow(d-b, 2), 0.5) <= (range/2)) {
                        enemy.Current_HP = 5;
                        //std::cout << "HIT" << enemy.Current_HP << std::endl;
                        
                        
                    } 
                    

                } 
            } */
            
            break;
        
        case THUNDER:
            {
            /* if (cadence = time) {}
            int closest = range/2;
            Enemy* closest_enemy;
            for (Enemy& enemy : enemies) {

                if(!enemy.dead){
                    int a = rect.x + rect.w/2;
                    int b = rect.y + rect.h/2;
                    double c = enemy.GetPosition().x;
                    double d = enemy.GetPosition().y;

                    int dist = pow(pow(c-a, 2) + pow(d-b, 2), 0.5);
                    if ( dist <= closest) {
                        closest = dist;
                        closest_enemy = &enemy;
                        
                    } 
                    

                } 
            }
            closest_enemy->Current_HP -= this->degat;
            closest_enemy->SetExplode(true); */


            break;
            }

        default:
            break;

    }

}