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
    this->explosion = assetmanager.GetTexture("thunder");
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
    this->explosion = assetmanager.GetTexture("thunder");

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
    this->explosion = assetmanager.GetTexture("thunder");

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
    this->explosion = assetmanager.GetTexture("thunder");

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
    this->explosion = assetmanager.GetTexture("thunder");

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
vec2<double>& Entity::GetPosition(){
    return position;
}

void Entity::SetDirection(vec2<double> direction){
    this->direction = direction;
}

// Change la position de l'ennemi et met à jour sprite (à cause du rect)
void Entity::SetPosition(vec2<double> pos){
    this->position = pos;

    // Met à jour le rect 
    SDL_Rect rect;

    rect.w = this->sprite.GetRect().w;
    rect.h = this->sprite.GetRect().h;
    rect.x = (int)position.x;
    rect.y = (int)position.y;

    sprite.SetRect(rect);
}

// Déplace l'ennemi via un vecteur
void Entity::Move(vec2<double>  step){
    SetPosition(step + position);
}


Tower::Tower(Tower_t type, int x, int y, AssetManager assets) {

    this->effect_texture = NULL;
    switch (type) {
        case FIRE:
            this->texture = assets.GetTexture("t1");
            this->range = 300;
            this->cadence = 3; // tte les 3sec
            this->degat = 100;
            this->price = 1000;

            break;

        case ICE:
            this->texture = assets.GetTexture("t3");
            this->range = 150;
            this->cadence = 1; // 1 fois par sec ou 2 / sec
            this->degat = 10;
            this->effect_texture = assets.GetTexture("ice");
            this->price = 500;


            break;
        
        case THUNDER:
            this->texture = assets.GetTexture("t2");
            this->range = 250;
            this->cadence = 2; // tte les 2 sec
            this->degat = 50;
            this->effect_texture = assets.GetTexture("thunder");
            this->price = 700;


            break;

        default:
            break;

    }
    this->target = nullptr;
    this->showrange = false;
    this->type = type;
    this->rect = GetTextureSize(texture);
    this->rect.x = x;
    this->rect.y = y;
    this->CD = 0;
}

void Tower::BlitTower(SDL_Renderer* renderer) {

    BlitTexture(this->texture, renderer, this->rect.x - rect.w/2, this->rect.y - rect.h/2);

}

void Tower::GetGridCase(int* x, int* y, int grid_cell_size) {
    *x = rect.x/grid_cell_size;
    *y = rect.y/grid_cell_size;
}


void Tower::DrawRange(SDL_Renderer * renderer, int cell_size)
{

    if (this->showrange) {
        // std::cout << "TOWER X : " << rect.x << " Y : " << rect.y << std::endl;
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
            SDL_RenderDrawPoint(renderer, rect.x + x, rect.y - y);
            SDL_RenderDrawPoint(renderer, rect.x + x, rect.y + y);
            SDL_RenderDrawPoint(renderer, rect.x - x, rect.y - y);
            SDL_RenderDrawPoint(renderer, rect.x - x, rect.y + y);
            SDL_RenderDrawPoint(renderer, rect.x + y, rect.y - x);
            SDL_RenderDrawPoint(renderer, rect.x + y, rect.y + x);
            SDL_RenderDrawPoint(renderer, rect.x - y, rect.y - x);
            SDL_RenderDrawPoint(renderer, rect.x - y, rect.y + x);

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


HomingProjectile::HomingProjectile(vec2<double> pos, AssetManager& assetmanager, Enemy * target){
    this->speed = 150;
    this->target = target;
    this->texture = assetmanager.GetTexture("fire_proj");
    this->dmg = 100;
    this->active = true;
    this->position = pos;
}

void HomingProjectile::UpdateDirection(vec2<double> direction){
    this->direction = direction.normalize();
}