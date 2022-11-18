#pragma once 

#include "vector2.hpp"
#include "assetsmanager.hpp"

/*
    Notes : 
        Transférer toutes les fonctions rédigées ici dans le .cpp : 
        Je pense que c'est plus propre de définir les fonctions dans le header et de les rédiger uniquement dans le .cpp.
*/

class Enemy
{
    public: 
        Enemy() = default;
        Enemy(vec2<double> spawnPosition, int Max_HP, int Speed, AssetManager& assetmanager);

        ~Enemy() = default;

        vec2<double> GetDirection(){return this->direction;};

        // Renvoie le sprite de l'ennemi
        Sprite& GetSprite(){return sprite;};

        // Renvoie la vitesse de l'ennemi
        int GetSpeed(){return this->speed;};

        // Modifie la direction de l'ennemi
        void SetDirection(vec2<double>  direction);

        vec2<double>& GetPosition();

        // Modifie la position de l'ennemi via un vecteur
        void SetPosition(vec2<double> pos);

        // Déplace l'ennemi via un vecteur (exemple avance de 10 en x et 0 en y)
        void Move(vec2<double>  step);

        int maxcell = 0;
        int i = 0;

    private:
        vec2<double>  direction;
        vec2<double>  position = vec2<double>();
        Sprite sprite;

        int Max_HP;
        int Current_HP;
        float speed;
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

class Instance
{
    public:
        Instance();
        ~Instance() = default;

        //Enemy Management
        void AddEnemy(const Enemy& enemy);
        void DeleteEnemy(int id);
        Enemy& GetEnemy(int id);
        std::vector<Enemy>& GetEnemies();

        //Tower Management
        void AddTower(std::string id, Tower tower);
        Tower GetTower(std::int16_t id);

    private:
        std::vector<Enemy> enemies;
        std::vector<Tower> towers;
};