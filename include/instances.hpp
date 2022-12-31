#pragma once 

#include "vector2.hpp"
#include "assetsmanager.hpp"
#include "grid.hpp"

// Stats
#define GOBLIN_SPEED 18
#define GOLEM_SPEED 12
#define ELF_SPEED 25
#define KNIGHT_SPEED 50
#define ORC_SPEED 32

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

};

class Entity
{
    public: 
        // Renvoie le sprite de l'ennemi
        Sprite& GetSprite(){return sprite;};
        vec2<double> GetDirection(){return this->direction;};

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

        // Modifie la direction de l'ennemi
        void SetDirection(vec2<double>  direction);

        vec2<double>& GetPosition();

        // Modifie la position de l'ennemi via un vecteur
        void SetPosition(vec2<double> pos);

        // Déplace l'ennemi via un vecteur (exemple avance de 10 en x et 0 en y)
        void Move(vec2<double>  step);

        int maxcell = 0;
        int i = 0;
        bool dead;
        int Max_HP;
        int Current_HP;
        std::vector<Cell>* path;

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