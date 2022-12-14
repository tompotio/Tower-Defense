#include "../include/menu.hpp"

Menu::Menu(Body* body)
{
    this->isRunning = true;
    this->isSetting = false;
    this->volume_selected = false;
    this->leftMouseButtonDown = false;
    volume_bar = {700, 250, 300, 50};
    vol_drag_button = {(volume_bar.x + volume_bar.w - 15), volume_bar.y, 15, volume_bar.h};
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
    
    widgetsM.push_back(Widget("playb", assets.GetTexture("mb"), WindowSize));
    widgetsM.push_back(Widget("s-i", (WindowSize.w-160), 10, assets.GetTexture("sb")));
    widgetsS.push_back(Widget("s-bg", assets.GetTexture("mt"), WindowSize));
    widgetsS.push_back(Widget("s-cross", (WindowSize.w-160), 10, assets.GetTexture("cross")));
    

}

void Menu::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        

        
        case SDL_MOUSEBUTTONDOWN:
            leftMouseButtonDown = true;
            if(SDL_PointInRect(&cursor, &vol_drag_button)) {
                volume_selected = true;
            }
            if (event.button.button == SDL_BUTTON_LEFT){
                leftClick();
                
            }/* else if (event.button.button == SDL_BUTTON_RIGHT){
                //rightClick();
            } */
            break;
        case SDL_MOUSEBUTTONUP:
            if (leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                leftMouseButtonDown = false;
                
            }


        case SDL_MOUSEMOTION:
            cursor = {event.motion.x, event.motion.y};
            
            if (leftMouseButtonDown && volume_selected && cursor.x > volume_bar.x && cursor.x < (volume_bar.x + volume_bar.w - vol_drag_button.w)) {

                vol_drag_button.x = cursor.x;
                //volume_bar->y = mousePos.y - clickOffset.y;

            }
            break;        

        default:
            break;
    }
}

void Menu::Update(SDL_Renderer* renderer)
{   
    SDL_RenderCopy(renderer, TextureManager::LoadTexture("../assets/PNG/Menu/bg1.jpg", renderer), NULL, NULL);
    
    if (isSetting) {
        for(Widget &widget : widgetsS) {
            widget.BlitWidget(renderer);
            
        }
        DrawVolumeBar();
            
    }
    else // Menu
    {
        for(Widget &widget : widgetsM) {
            widget.BlitWidget(renderer);
            /* if (widget.getId() == "s-i" && widget.isHovering(cursor.x, cursor.y)){
                widget.setTexture(assets.GetTexture("sb2"));

            }else if (widget.getId() == "s-i"){
                widget.setTexture(assets.GetTexture("sb"));
            } */
        }
    }
    
   
}



void Menu::leftClick() {

    if (isSetting) {
        for(Widget &widget : widgetsS) {
        
            if (widget.isHovering(cursor.x, cursor.y)) {

                if (widget.getId() == "s-cross") {
                    isSetting = false;
                }
            
            }
        }
            
    }
    else // Menu
    {
        for(Widget &widget : widgetsM) {
        
            if (widget.isHovering(cursor.x, cursor.y)) {

                if (widget.getId() == "playb") {
                    isRunning = false;  
                }
                if (widget.getId() == "s-i") {
                    isSetting = true;
                    std::cout << "test" << std::endl;
                    break;

                }

            
            } 
        }
    }
    

    
   
    
}




void Menu::DrawVolumeBar(){
    SDL_SetRenderDrawColor(body->GetRenderer(), 0,0,0,255);
    SDL_RenderFillRect(body->GetRenderer(), &volume_bar);

    
    SDL_SetRenderDrawColor(body->GetRenderer(), 255,255,255,255);
    SDL_RenderFillRect(body->GetRenderer(), &vol_drag_button);

    

}