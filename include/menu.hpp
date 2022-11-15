#pragma once

#include "assetsmanager.hpp"
#include "widget.hpp"
#include "grid.hpp"


class Menu
{
    public:
        Menu(SDL_Renderer* renderer);
        ~Menu() = default;

        void HandleEvents();
        void leftClick(double x, double y);
        //void rightClick(double x, double y);
        void Update(SDL_Renderer* renderer); 
        bool running() {return isRunning;};

        std::vector<Widget> widgets;
        Sprite sprite;
        SDL_Rect rect;


    private:
        Vector2 cursor;
        bool isRunning;
     
        
};