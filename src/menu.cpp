#include "../include/menu.hpp"

Menu::Menu(Body* body)
{
    this->isRunning = true;
    this->body = body;
    this->cursor = vec2<double>();
    this->assets = AssetManager();

    assets.AddTexture(
        "pb",
        TextureManager::LoadTexture("../assets/playbutton.png", body->GetRenderer())
    );
    // widgets.push_back(Widget(body->GetWindow().w/2, body->GetWindow().h/2, assets.GetTexture("pb")));

}

void Menu::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT){
                leftClick();
            }else if (event.button.button == SDL_BUTTON_RIGHT){
                //rightClick(event.motion.x, event.motion.y);
            }
            break;
        case SDL_MOUSEMOTION:
            cursor.x = event.motion.x;
            cursor.y = event.motion.y;
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
    SDL_RenderCopy(renderer, TextureManager::LoadTexture("../assets/PNG/Menu/bg1.jpg", renderer), NULL, NULL);
    for(Widget widget : widgets) {
        if (widget.isHovering(cursor.x, cursor.y)){
            widget.BlitWidget(renderer);
        }else{
            widget.BlitWidgetTransparent(renderer);
        }
    }
   
}

void Menu::leftClick() {

    for(Widget widget : widgets) {
        
        if (widget.isHovering(cursor.x, cursor.y)) {
            isRunning = false;
        }
        
    }
    
}
