#include "../include/widget.hpp"

Widget::Widget(int x, int y, SDL_Texture* texture){
    
    this->rect = {x, y};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    std::cout << "size = " << rect.x << "  " << rect.y << "  " << rect.w << "  " << rect.h << std::endl;
    this->texture = texture;
}

void Widget::BlitWidget(SDL_Renderer* renderer) {
    
    TextureManager::BlitTexture(getTexture(), renderer, getRect().x, getRect().y);
}

bool Widget::hasClick(int x, int y) {
    /* cout << "size = " << getRect().x << "  " << getRect().y << "  " << getRect().w << "  " << getRect().h << endl;
    cout << "pos = " << x << "  " << y  << endl; */
    
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