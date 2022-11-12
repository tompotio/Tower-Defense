#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vector"
#include <algorithm>
#include <cmath>

class Cell{
    public:
        Cell(int x, int y);

        void CalculateFCost(){
            fCost = gCost + hCost;
        };

        Cell* cameFromCell;

        int gCost;
        int hCost;
        int fCost;

        int x;
        int y;      
};

class Grid
{
    public:
        Grid() = default;
        Grid(int width,int height,int cellsize, int offsetx, int offsety);

        int GetWidth(){return this->width;};

        int GetHeight(){return this->height;};

        int GetCellSize(){return this->cellsize;};

        int GetOffsetX(){return this->offsetx;};

        int GetOffsetY(){return this->offsety;};

        Cell& GetGridObject(int x, int y);

        void DrawGrid(SDL_Renderer* renderer);

        //Vector2 GetWorldPosition(int x, int y);

    private:
        int width;
        int height;
        int cellsize;
        int offsetx;
        int offsety;

        // Tableau à deux dimensions des cellules contenues dans la grille
        std::vector<std::vector<Cell>> cells;
};

class Pathfinding
{
    public:
        Pathfinding(Grid grid);

        int CalculateDistanceCost(Cell a, Cell b);

        Cell& GetLowestFCostCell(std::vector<Cell> List);

        bool Find(Cell cell, std::vector<Cell> list);

        int GetPositionInList(Cell cell, std::vector<Cell> list);

        std::vector<Cell> GetNeighbourList(Cell currentCell);

        std::vector<Cell> CalculatePath(Cell endCell);

        std::vector<Cell> FindPath(int startX, int startY, int endX, int endY);

    private:
        const int MOVE_STRAIGHT_COST = 10;
        const int MOVE_DIAGONAL_COST = 14;

        Grid grid = Grid();

        std::vector<Cell> openList;
        std::vector<Cell> closedList;
};