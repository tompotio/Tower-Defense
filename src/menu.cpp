#include "../include/menu.hpp"

Menu::Menu(Body* body)
{
    this->isRunning = true;
    this->isSetting = false;
    this->body = body;
    this->cursor = vec2<double>();
    this->assets = AssetManager();
    
    SDL_GetWindowSize(body->GetWindow(), &WindowSize.w, &WindowSize.h);

    assets.AddTexture(
        "pb",
        TextureManager::LoadTexture("../assets/playbutton1.png", body->GetRenderer())
    );

    assets.AddTexture(
        "sb",
        TextureManager::LoadTexture("../assets/PNG/Menu/menu_button/settings1.png", body->GetRenderer())
    );
    
    widgets.push_back(Widget("m-pb", assets.GetTexture("pb"), WindowSize));
    widgets.push_back(Widget("m-sb", (WindowSize.w-160), 10,  assets.GetTexture("sb")));
    
    

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
        if (isSetting) {
            if (widget.getId()[0] == 's') {
                widget.BlitWidget(renderer);
            }
            
        }
        else if (widget.getId()[0] == 'm') {
            widget.BlitWidget(renderer);
            std::cout << isSetting << widget.getId() << std::endl;
            /* if (widget.isHovering(cursor.x, cursor.y)){
                widget.BlitWidget(renderer);
            }else{
                widget.BlitWidgetTransparent(renderer);
            } */
        }
        
    }
   
}



void Menu::leftClick() {


    

    for(Widget widget : widgets) {
        
        if (widget.isHovering(cursor.x, cursor.y)) {

            if (widget.getId() == "m-pb") {
                isRunning = false;  
            }
            if (widget.getId() == "m-sb") {
                isSetting = true;  
            }
           
        }
        
    }
    
}
