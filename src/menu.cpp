#include "../include/menu.hpp"

Menu::Menu(Body* body)
{
    this->isRunning = true;
    this->isSetting = false;
    this->volume_selected = false;
    this->leftMouseButtonDown = false;
    volume_rect = {500, 250, 50, 10};
    this->body = body;

    this->assets = AssetManager();
    
    SDL_GetWindowSize(body->GetWindow(), &WindowSize.w, &WindowSize.h);

    
    assets.AddTexture(
        "sb",
        TextureManager::LoadTexture("../assets/PNG/Menu/settings/settings_button1.png", body->GetRenderer())
    );

    assets.AddTexture(
        "sb2",
        TextureManager::LoadTexture("../assets/PNG/Menu/settings/sbutton_bg.png", body->GetRenderer())
    );

    assets.AddTexture(
        "mt",
        TextureManager::LoadTexture("../assets/PNG/Menu/settings/menu_tile1.png", body->GetRenderer())
    );

    assets.AddTexture(
        "mb",
        TextureManager::LoadTexture("../assets/PNG/Menu/settings/menu_button1.png", body->GetRenderer())
    );

    assets.AddTexture(
        "cross",
        TextureManager::LoadTexture("../assets/PNG/Menu/settings/cross1.png", body->GetRenderer())
    );
    
    widgets.push_back(Widget("m-pb", assets.GetTexture("mb"), WindowSize));
    widgets.push_back(Widget("m-sb", (WindowSize.w-160), 10, assets.GetTexture("sb")));
    widgets.push_back(Widget("s-sbg", assets.GetTexture("mt"), WindowSize));
    widgets.push_back(Widget("s-cross", (WindowSize.w-160), 10, assets.GetTexture("cross")));
    

}

void Menu::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        
        case SDL_MOUSEBUTTONDOWN:
            leftMouseButtonDown = true;
            if(SDL_PointInRect(&cursor, &volume_rect)) {
                volume_selected = true;
            }
            if (event.button.button == SDL_BUTTON_LEFT){
                leftClick();
                
            }else if (event.button.button == SDL_BUTTON_RIGHT){
                //rightClick(event.motion.x, event.motion.y);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                leftMouseButtonDown = false;
                
            }


        case SDL_MOUSEMOTION:
            cursor = {event.motion.x, event.motion.y};
            
            if (leftMouseButtonDown && volume_selected) {
                
                volume_rect.x = cursor.x;
                //volume_rect->y = mousePos.y - clickOffset.y;

            }

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
    for(Widget &widget : widgets) {
        if (isSetting) {
            if (widget.getId()[0] == 's') {
                widget.BlitWidget(renderer);
                
            }
            
            DrawVolumeBar();
            
        }
        else {
            if (widget.getId()[0] == 'm') {
                widget.BlitWidget(renderer);
                if (widget.getId() == "m-sb") {
                    if (widget.isHovering(cursor.x, cursor.y)){
                        widget.setTexture(assets.GetTexture("sb2"));

                    }else{
                        widget.setTexture(assets.GetTexture("sb"));
                    }
                }
            }
            
        }
        
    }
   
}



void Menu::leftClick() {

    for(Widget &widget : widgets) {
        
        if (widget.isHovering(cursor.x, cursor.y)) {

            if (widget.getId() == "m-pb") {
                isRunning = false;  
            }
            if (widget.getId() == "s-cross") {
                isSetting = false;
            }
            if (widget.getId() == "m-sb") {
                isSetting = true;
                std::cout << "test" << std::endl;
                break;

            }

           
        }

        
        
    }
    
}




void Menu::DrawVolumeBar(){
    SDL_SetRenderDrawColor(body->GetRenderer(), 0,0,0,255);
    SDL_RenderFillRect(body->GetRenderer(), &volume_rect);

    SDL_Rect drag_button = {950, 750, 10, 50};
    SDL_SetRenderDrawColor(body->GetRenderer(), 255,255,255,255);
    SDL_RenderFillRect(body->GetRenderer(), &drag_button);

    

}