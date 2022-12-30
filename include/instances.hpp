#pragma once 

#include "vector2.hpp"
#include "assetsmanager.hpp"
#include "grid.hpp"

/*
    Notes : 
        Transférer toutes les fonctions rédigées ici dans le .cpp : 
        Je pense que c'est plus propre de définir les fonctions dans le header et de les rédiger uniquement dans le .cpp.
*/

enum Entity_t 
{   
    GOBLIN,
    ARCHER,
};

enum Tower_t 
{   
    FIRE,
    ICE,
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

class Goblin : public Enemy{
    public: 
        Goblin(vec2<double> spawnPosition, AssetManager& assetmanager); 
        void Reset();
};

class Tower {
    public: 
        Tower(Tower_t type, int x, int y, AssetManager assets);
        void AttackEnemy();
        void RotateSprite(); //Modifie l'angle de rotation du sprite        

    private:
        SDL_Rect rect;
        SDL_Texture* texture;

};

// A coder beaucoup plus tard
class Allies
{
    public: 
        Allies(/* args */);
        ~Allies();
};