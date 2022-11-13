#include "../include/menu.hpp"



Menu::Menu(SDL_Renderer* renderer)
{

    isRunning = true;

    
    widgets.push_back(Sprite(SDL_Rect {200, 400, 50, 50}, TextureManager::LoadTexture("../assets/playbutton.png", renderer)));

}



void Menu::Update(SDL_Renderer* renderer)
{   
    cout << "size =" << widgets.size() << endl;
    for(Sprite widget : widgets) {
        
        SDL_Rect w = widget.GetRect();
        TextureManager::BlitSprite(widget, renderer);
    }
   
}

