#include "../include/widget.hpp"

Widget::Widget(std::string id, int x, int y, SDL_Texture* texture, bool active, double timer_init, int number_print){
    
    this->id = id;
    this->rect = GetTextureSize(texture);
    this->rect.x = x;
    this->rect.y = y;
    this->texture = texture;
    this->active = active;
    this->timer_init = timer_init;
    this->timer_actual = timer_init;
    this->number_print = number_print;
}

// Widget Center
Widget::Widget(std::string id, SDL_Texture* texture, SDL_Rect WindowSize) {

    this->id = id;
    this->rect = GetTextureSize(texture);

    this->rect.x = (WindowSize.w-rect.w)/2;
    this->rect.y = (WindowSize.h-rect.h)/2;
    this->texture = texture;
    this->active = true;


}

void Widget::BlitWidget(SDL_Renderer* renderer) {
    if (this->active) {
        BlitTexture(getTexture(), renderer, getRect().x, getRect().y);

    }
}



/* void Widget::BlitWidgetTransparent(SDL_Renderer* renderer) {
    
} */

bool Widget::isHovering(int x, int y) {

    if (x >= getRect().x && x < (getRect().x+getRect().w) && y < (getRect().y+getRect().h) && y >= getRect().y) {
        return true;
    }
    return false;

}

/* 

Widget::Widget(int x, int y, int width, int height, SDL_Texture* texture){
    this->rect = {x, y, width, height};
    this->texture = texture;
}

std::vector<Enemy>& Instance::GetEnemies(){
    return enemies;
} */