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