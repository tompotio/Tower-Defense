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
        // Vérifie si l'ennemi est actif ou non
        bool GetStatus(){return this->active;};
        // Modifie le statut actif ou non actif de l'ennemi
        void SetStatus(bool status){this->active = status;};
        Entity_t GetType(){return this->type;};
        void Reset(){};

        // Modifie la direction de l'ennemi
        void SetDirection(vec2<double>  direction);

        vec2<double>& GetPosition();

        // Modifie la position de l'ennemi via un vecteur
        void SetPosition(vec2<double> pos);

        // Déplace l'ennemi via un vecteur (exemple avance de 10 en x et 0 en y)
        void Move(vec2<double>  step);

        int maxcell = 0;
        int i = 0;
        std::vector<Cell>* path;

    protected:
        int Max_HP;
        int Current_HP;
        int dmg;
        float speed;
        bool active;
        Entity_t type;
};

class Goblin : public Enemy{
    public: 
        Goblin(vec2<double> spawnPosition, AssetManager& assetmanager); 
        void Reset();
};

class Tower : public Entity
{
    public: 
        Tower(Entity_t type);
        void AttackEnemy();
        void RotateSprite(); //Modifie l'angle de rotation du sprite        

    private:
        Enemy& target;
        vec2<double>  dir;
        vec2<double>  position;
        Sprite sprite;

        //Si la tour est activée ou pas (genre un ennemi qui désactive les tours)
        bool status; 
};

// A coder beaucoup plus tard
class Allies
{
    public: 
        Allies(/* args */);
        ~Allies();
};