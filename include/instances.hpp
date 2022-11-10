#pragma once 

#include "vector2.hpp"
#include "assetsmanager.hpp"

/*
    Notes : 
        Transférer toutes les fonctions rédigées ici dans le .cpp : 
        Je pense que c'est plus propre de définir les fonctions dans le header et de les rédiger uniquement dans le .cpp.
*/

struct objective_t
{
    Vector2 position;
    objective_t* next;
};

class Enemy
{
    public: 
        Enemy() = default;
        Enemy(Vector2 spawnPosition, int Max_HP, int Speed, AssetManager& assetmanager);

        ~Enemy() = default;

        Vector2 GetDirection(){return this->direction;};

        // Renvoie le sprite de l'ennemi
        Sprite& GetSprite(){return sprite;};

        // Renvoie la vitesse de l'ennemi
        int GetSpeed(){return this->speed;};

        // Modifie la direction de l'ennemi
        void SetDirection(Vector2 direction);

        // Récupère la position de l'ennemi
        Vector2 GetPosition(){return this->position;};

        // Modifie l'objectif d'un ennemi
        void SetObjective(objective_t ob){this->objective = &ob;};

        objective_t* GetObjective(){return this->objective;};

        // Modifie la position de l'ennemi via un vecteur
        void SetPosition(Vector2 pos);

        // Déplace l'ennemi via un vecteur (exemple avance de 10 en x et 0 en y)
        void Move(Vector2 step);

    private:
        objective_t* objective;
        Vector2 direction;
        Vector2 position;
        Sprite sprite;

        int Max_HP;
        int Current_HP;
        int speed;
};

enum Towers_t 
{   
    ARCHER,
};

class Tower
{
    public: 
        Tower();
        Tower(Towers_t type);
        ~Tower() = default;

        Enemy GetEnemy();
        void AttackEnemy();
        void RotateSprite(); //Modifie l'angle de rotation du sprite        

    private:
        Enemy target;
        Vector2 dir;
        Vector2 position;
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

class Instance
{
    public:
        Instance();
        ~Instance() = default;

        //Enemy Management
        void AddEnemy(const Enemy& enemy);
        Enemy& GetEnemy(int id);
        std::vector<Enemy>& GetEnemies();

        //Tower Management
        void AddTower(std::string id, Tower tower);
        Tower GetTower(std::int16_t id);
        std::vector<objective_t> objectives;

    private:
        std::vector<Enemy> enemies;
        std::vector<Tower> towers;
};