#pragma once

#include <iostream>
#include "vector"
#include <algorithm>
#include <cmath>
#include <functional>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum Cell_type_t 
{   
    TOWER,
    DIRT = '5',
    MISC,
};

class Cell{
    public:
        Cell(int x, int y, bool tower_on = false);

        void CalculateFCost(){this->fCost = this->gCost + this->hCost;};
        
        char type;
        Cell* cameFromCell;

        int gCost;
        int hCost;
        int fCost;

        int x;
        int y;

        bool tower_on;
};

class Grid
{
    public:
        Grid() = default;
        Grid(int width,int height,int cellsize, int offsetx, int offsety, SDL_Renderer* renderer);

        int GetWidth(){return this->width;};

        int GetHeight(){return this->height;};

        int GetCellSize(){return this->cellsize;};

        int GetOffsetX(){return this->offsetx;};

        int GetOffsetY(){return this->offsety;};

        void DrawGrid(SDL_Renderer* renderer);        

        void AffectTypeToCell(int x, int y, char c);

        std::vector<Cell> FindPath(int startX, int startY, int endX, int endY);

        Cell* GetGridObject(int x, int y);

    private:
        Cell* GetLowestFCostCell();

        int GetPositionInList(Cell* cell, std::vector<Cell*> list);

        int CalculateDistanceCost(Cell* a, Cell* b);

        bool Find(Cell* cell, std::vector<Cell*> list);

        int MOVE_STRAIGHT_COST = 10;
        int MOVE_DIAGONAL_COST = 14;
        int width;
        int height;
        int cellsize;
        int offsetx;
        int offsety;

        SDL_Renderer* renderer;

        // Liste des cellules en cours de traitement
        std::vector<Cell*> openList;

        // Liste des cellules déjà parcourues
        std::vector<Cell*> closedList;

        // Tableau à deux dimensions des cellules contenues dans la grille
        std::vector<std::vector<Cell>> cells;
        std::vector<Cell*> GetNeighbourList(Cell* currentCell);
        std::vector<Cell> CalculatePath(Cell* endCell);
};