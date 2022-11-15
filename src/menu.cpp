#include "../include/menu.hpp"



Menu::Menu(SDL_Renderer* renderer)
{

    isRunning = true;

    cursor = Vector2();
    widgets.push_back(Widget(300, 400, TextureManager::LoadTexture("../assets/playbutton.png", renderer)));

}

void Menu::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT){
                leftClick(event.motion.x, event.motion.y);
            }else if (event.button.button == SDL_BUTTON_RIGHT){
                //rightClick(event.motion.x, event.motion.y);
            }
            break;
        case SDL_MOUSEMOTION:
            cursor.setX(event.motion.x);
            cursor.setY(event.motion.y);
            break;

        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Menu::Update(SDL_Renderer* renderer)
{   
    cout << "size =" << widgets.size() << endl;
    for(Widget widget : widgets) {
        
        widget.BlitWidget(renderer);
        
    }
   
}

void Menu::leftClick(double x, double y) {

    for(Widget widget : widgets) {
        
        if (widget.hasClick(x, y)) {
            
            cout << "heee" << endl;
            isRunning = false;
        }
        
    }
    
}
