#pragma once 

#include "vector2.hpp"
#include "assetsmanager.hpp"

class Widget 
{
    public:
        Widget() = default;
        Widget(std::string id, int x, int y, SDL_Texture* texture);
        Widget(std::string id, SDL_Texture* texture, SDL_Rect WindowSize);
        
        void BlitWidget(SDL_Renderer* renderer);
        SDL_Rect& getRect() {return rect;}
        SDL_Texture* getTexture() {return texture;}
        std::string getId() {return id;}
        void setTexture(SDL_Texture* texture2) {this->texture = texture2;}
        bool isHovering(int x, int y);
        void BlitWidgetTransparent(SDL_Renderer* renderer);
        //void onClick();
        
    private:
        std::string id;
        SDL_Rect rect;
        SDL_Texture* texture;
};
/* 
class Widget 
{
    public:
        Widget() = default;
        Widget(int x, int y, int width, int height, SDL_Texture* texture);
        
        bool MouseHovering(int x, int y);
    private:
        SDL_Rect rect;
        SDL_Texture* texture;

};

 */