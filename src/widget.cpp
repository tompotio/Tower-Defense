#include "../include/widget.hpp"



Widget::Widget(int x, int y, SDL_Texture* texture){
    this->rect = {x, y};
    this->texture = texture;
}

void Widget::BlitWidget(SDL_Renderer* renderer) {
    TextureManager::BlitTexture(getTexture(), renderer, getRect().x, getRect().y);
}

bool Widget::hasClick(int x, int y) {
    return true;
    /* if (x > getRect().x && x > getRect().x) {
        ......
    } */
}

/* 

Widget::Widget(int x, int y, int width, int height, SDL_Texture* texture){
    this->rect = {x, y, width, height};
    this->texture = texture;
}

std::vector<Enemy>& Instance::GetEnemies(){
    return enemies;
} */