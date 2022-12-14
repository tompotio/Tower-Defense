#pragma once 

#include "vector2.hpp"
#include "assetsmanager.hpp"
#include "grid.hpp"

// Stats
/* #define GOBLIN_SPEED 18
#define GOLEM_SPEED 12
#define ELF_SPEED 25
#define KNIGHT_SPEED 50
#define ORC_SPEED 32 */

#define GOBLIN_SPEED 150
#define GOLEM_SPEED 80
#define ELF_SPEED 80
#define KNIGHT_SPEED 80
#define ORC_SPEED 80

#define GOBLIN_HP 50
#define GOLEM_HP 500
#define ELF_HP 100
#define KNIGHT_HP 250
#define ORC_HP 1250

/*
    Notes : 
        Transférer toutes les fonctions rédigées ici dans le .cpp : 
        Je pense que c'est plus propre de définir les fonctions dans le header et de les rédiger uniquement dans le .cpp.
*/

enum Entity_t 
{   
    GOBLIN,
    KNIGHT,
    GOLEM,
    ELF,
    ORC
};

enum Tower_t 
{   
    FIRE,
    ICE,
    THUNDER
};

class Entity
{
    public: 
        // Renvoie le sprite de l'entité
        Sprite& GetSprite(){return sprite;};
        vec2<double> GetDirection(){return this->direction;};

        // Modifie la direction de l'entité
        void SetDirection(vec2<double>  direction);
        vec2<double>& GetPosition();
        // Modifie la position de l'entité
        void SetPosition(vec2<double> pos);
        // Déplace l'entité
        void Move(vec2<double>  step);

    protected:
        vec2<double>  direction;
        vec2<double>  position;
        Sprite sprite;
};

class Enemy : public Entity
{
    public: 
        // Renvoie la vitesse de l'ennemi
        int GetSpeed(){return this->speed;};
        int GetDamage(){return this->dmg;};
        Entity_t GetType(){return this->type;};
        
        void BlitExplosion(SDL_Renderer* renderer);
        // Modifie la direction de l'ennemi

        // Déplace l'ennemi via un vecteur (exemple avance de 10 en x et 0 en y)
        


        int maxcell = 0;
        int i = 0;
        bool dead;
        bool selected = true;
        int Max_HP;
        int Current_HP;
        bool explode;
        std::vector<Cell>* path;
        SDL_Texture* explosion;

    protected:
        
        int dmg;
        float speed;
        Entity_t type;
};

class Goblin : public Enemy
{
    public: 
        Goblin(vec2<double> spawnPosition, AssetManager& assetmanager); 
};

class Tower {
    public: 
        Tower(Tower_t type, int x, int y, AssetManager assetmanager);
        void BlitTower(SDL_Renderer* renderer);
        void DrawRange(SDL_Renderer * renderer, int cell_size);
        void GetGridCase(int* x, int* y, int grid_cell_size);
        void Fire(std::vector<Enemy> enemies, int seconds, double seconds_mil, double last_seconds_mil);
        void SetTarget(Enemy* enemy) {this->target = enemy;};
        SDL_Rect GetRect() {return rect;}
        void SetShowRange(bool show) {this->showrange = show;};
        bool GetShowRange() {return showrange;}
        /* void AttackEnemy();
        void RotateSprite(); //Modifie l'angle de rotation du sprite      */   
        Tower_t type;
        int range; // euclidian distance
        int cadence;      // attaque par sec
        int degat;
        int price;
        SDL_Texture* effect_texture;
        double CD;

    private:
        SDL_Texture* texture;
        SDL_Rect rect;
        bool showrange;

        // Fire
        Enemy* target;

        // Ice


        // THUNDER

};

class HomingProjectile
{
    public: 
        HomingProjectile(vec2<double> pos, AssetManager& assetmanager, Enemy * target);
        void UpdateDirection(vec2<double> direction);

        Enemy* target;
        SDL_Texture* texture;
        // Cooldown animation
        double CD;
        int speed;
        int dmg;
        int animationstep = 0;
        vec2<double> position;
        vec2<double> direction;

        bool active;
};

class Elf : public Enemy
{
    public: 
        Elf(vec2<double> spawnPosition, AssetManager& assetmanager);
};

class Golem : public Enemy
{
    public:
        Golem(vec2<double> spawnPosition, AssetManager& assetmanager);
};

class Knight : public Enemy
{
    public: 
        Knight(vec2<double> spawnPosition, AssetManager& assetmanager);
};

class Orc : public Enemy
{
    public: 
        Orc(vec2<double> spawnPosition, AssetManager& assetmanager);
};