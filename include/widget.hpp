#pragma once 

#include "vector2.hpp"
#include "assetsmanager.hpp"

class Widget 
{
    public:
        Widget() = default;
        
        // Constructeur normal
        Widget(std::string id, int x, int y, SDL_Texture* texture, bool active = true, double timer_init = 0.5, int number_print = -1);
        // Constructeur center widget
        Widget(std::string id, SDL_Texture* texture, SDL_Rect WindowSize);
        
        void BlitWidget(SDL_Renderer* renderer);

        SDL_Rect& getRect() {return rect;}

        SDL_Texture* getTexture() {return texture;}
        std::string getId() {return id;}
        void setTexture(SDL_Texture* texture2) {this->texture = texture2;};
        void setRect(SDL_Rect rect) {this->rect = rect;};
        void setX(int x) {this->rect.x = x;};
        void setY(int y) {this->rect.y = y;};
        void setActive(bool a) {this->active = a;};
        bool getActive() {return this->active;};
        bool isHovering(int x, int y);
        void BlitWidgetTransparent(SDL_Renderer* renderer);
        
        double timer_actual;
        double timer_init;
        int number_print;

    private:
        std::string id;
        SDL_Rect rect;
        SDL_Texture* texture;
        bool active;
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