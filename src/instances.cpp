#include "../include/instances.hpp"

Enemy::Enemy(vec2<double> spawnPosition, int Max_HP, int Speed, AssetManager& assetmanager){
    this->Max_HP = Max_HP;
    this->Current_HP = Max_HP;
    this->speed = Speed;

    SDL_Texture* texture = assetmanager.GetTexture("zombie");
    int w;
    int h;

    SetPosition(spawnPosition);
    
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