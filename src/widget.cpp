#include "../include/widget.hpp"



Widget::Widget(int x, int y, int width, int height, SDL_Texture* texture){
    rect = {x, y, width, height};
    texture = texture;
}



/* 
std::vector<Enemy>& Instance::GetEnemies(){
    return enemies;
} */