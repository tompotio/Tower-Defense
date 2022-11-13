#pragma once 

#include "vector2.hpp"
#include "assetsmanager.hpp"


class Widget 
{
    public: 
        Widget(int x, int y, int width, int height, SDL_Texture* texture);
        bool MouseHovering(int x, int y);
        
        SDL_Rect rect;
    private:
        SDL_Texture* texture;

};
