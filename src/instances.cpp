#include "../include/instances.hpp"

Enemy::Enemy(Vector2 spawnPosition, int Max_HP, int Speed, AssetManager& assetmanager){
    this->Max_HP = Max_HP;
    this->Current_HP = Max_HP;
    this->speed = Speed;

    SDL_Texture* texture = assetmanager.GetTexture("soldier");
    int w;
    int h;

    SetPosition(spawnPosition);
    
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);

    this->sprite = Sprite(
        SDL_Rect {
            (int) GetPosition().getX(),
            (int) GetPosition().getY(),
            w,
            h
        },
        texture
    );
}

void Enemy::SetDirection(Vector2 direction){
    this->direction = direction;
}

// Change la position de l'ennemi et met à jour sprite (à cause du rect)
void Enemy::SetPosition(Vector2 pos){
    this->position = pos;

    // Met à jour le rect 
    SDL_Rect rect;

    rect.w = this->sprite.GetRect().w;
    rect.h = this->sprite.GetRect().h;
    rect.x = (int) GetPosition().getX();
    rect.y = (int) GetPosition().getY();

    sprite.SetRect(rect);
}

// Déplace l'ennemi via un vecteur
void Enemy::Move(Vector2 step){
    SetPosition(step + GetPosition());
}

Tower::Tower(){
    Tower(ARCHER);
}

Tower::Tower(Towers_t type){
    
}

Enemy Tower::GetEnemy(){
    return Enemy();
}

void Tower::AttackEnemy(){

}

void Tower::RotateSprite(){
    
}

Instance::Instance(){

}

void Instance::AddEnemy(const Enemy& enemy){
    enemies.push_back(enemy);
}


Enemy& Instance::GetEnemy(int id){
    return enemies[id];
}

std::vector<Enemy>& Instance::GetEnemies(){
    return enemies;
}

void Instance::AddTower(std::string id, Tower tower){

}

Tower Instance::GetTower(std::int16_t id){
    return Tower();
}