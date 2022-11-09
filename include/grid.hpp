#pragma once

#include <iostream>

class Cell{
    public:

    private:

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

        //Vector2 GetWorldPosition(int x, int y);

    private:
        int width;
        int height;
        int cellsize;
        int offsetx;
        int offsety;
};