#include "../include/menu.hpp"

Menu::Menu(Body** body) {
    
    this->isRunning = true;
    this->isSetting = false;
    this->music_volume_selected = false;
    this->leftMouseButtonDown = false;
    this->music_volume = MIX_MAX_VOLUME;
    this->sfx_volume = MIX_MAX_VOLUME;
    this->body = body;
    
    this->assets = AssetManager();
    
    SDL_GetWindowSize((*body)->GetWindow(), &WindowSize.w, &WindowSize.h);
    
    audio = AudioManager();
    assets.AddMusic("boss", "../assets/Sound/Boss_Music.mp3");
    assets.AddSFX("sucess", "../assets/Sound/success.wav");
    audio.PlayMusic("boss", &assets, 1);
    // audio.PlaySFX("sucess", &assets, 5);
    
    assets.AddTexture(
        "sb",
        LoadTexture("../assets/PNG/Menu/settings/settings_button1.png", (*body)->GetRenderer())
    );

    assets.AddTexture(
        "sb2",
        LoadTexture("../assets/PNG/Menu/settings/sbutton_bg.png", (*body)->GetRenderer())
    );

    assets.AddTexture(
        "mt",
        LoadTexture("../assets/PNG/Menu/settings/menu_tile1.png", (*body)->GetRenderer())
    );

    assets.AddTexture(
        "mb",
        LoadTexture("../assets/PNG/Menu/settings/menu_button3.png", (*body)->GetRenderer())
    );

    assets.AddTexture(
        "mb2",
        LoadTexture("../assets/PNG/Menu/settings/menu_button2.png", (*body)->GetRenderer())
    );

    assets.AddTexture(
        "cross",
        LoadTexture("../assets/PNG/Menu/settings/cross1.png", (*body)->GetRenderer())
    );

    assets.AddTexture(
        "drag_button",
        LoadTexture("../assets/PNG/Menu/settings/drag_button.png", (*body)->GetRenderer())
    );
    
    assets.AddTexture(
        "bar",
        LoadTexture("../assets/PNG/Menu/settings/bar.png", (*body)->GetRenderer())
    );


    assets.AddTexture(
        "music",
        LoadTexture("../assets/PNG/Menu/settings/music.png", (*body)->GetRenderer())
    );

    assets.AddTexture(
        "sounds",
        LoadTexture("../assets/PNG/Menu/settings/sounds.png", (*body)->GetRenderer())
    );

    assets.AddTexture(
        "effect",
        LoadTexture("../assets/PNG/Menu/settings/sfx.png", (*body)->GetRenderer())
    );

    /* assets.AddTexture(
        "play",
        LoadTexture("../assets/PNG/Menu/settings/play.png", (*body)->GetRenderer())
    ); */

    widgetsM.push_back(Widget("playb", assets.GetTexture("mb"), WindowSize));
    //widgetsM.push_back(Widget("text_play", (WindowSize.w-GetTextureSize(assets.GetTexture("play")).w)/2, (WindowSize.h-GetTextureSize(assets.GetTexture("play")).h)/2 - 7, assets.GetTexture("play")));
    widgetsM.push_back(Widget("s-i", (WindowSize.w-185), 10, assets.GetTexture("sb")));


    widgetsS.push_back(Widget("s-bg", assets.GetTexture("mt"), WindowSize));
    widgetsS.push_back(Widget("s-cross", (WindowSize.w-185), 10, assets.GetTexture("cross")));

    widgetsS.push_back(Widget("s-music_bar", ((WindowSize.w-GetTextureSize(assets.GetTexture("bar")).w)/2), (WindowSize.h/2), assets.GetTexture("bar")));
    widgetsS.push_back(Widget("s-sfx_bar", ((WindowSize.w-GetTextureSize(assets.GetTexture("bar")).w)/2), (WindowSize.h/2 + 200), assets.GetTexture("bar")));
    widgetsS.push_back(Widget("s-music_drag_button", ((WindowSize.w+GetTextureSize(assets.GetTexture("bar")).w)/2 - GetTextureSize(assets.GetTexture("drag_button")).w), (WindowSize.h /2 - 10), assets.GetTexture("drag_button")));
    widgetsS.push_back(Widget("s-sfx_drag_button", ((WindowSize.w+GetTextureSize(assets.GetTexture("bar")).w)/2 - GetTextureSize(assets.GetTexture("drag_button")).w), (WindowSize.h /2 + 190), assets.GetTexture("drag_button")));
    
    widgetsS.push_back(Widget("s-text_music", (*GetWidget("s-music_bar")).getRect().x - 150, (WindowSize.h/2 - 70), assets.GetTexture("music")));
    widgetsS.push_back(Widget("s-text_sfx", (*GetWidget("s-sfx_bar")).getRect().x - 150, (WindowSize.h/2 + 130), assets.GetTexture("effect")));
    widgetsS.push_back(Widget("s-text_sounds", ((WindowSize.w-GetTextureSize(assets.GetTexture("sounds")).w)/2), 80, assets.GetTexture("sounds")));

}

void Menu::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        

        
        case SDL_MOUSEBUTTONDOWN:
            
            if (event.button.button == SDL_BUTTON_LEFT){
               

                if(SDL_PointInRect(&cursor, &(*GetWidget("s-music_drag_button")).getRect())) {
                    music_volume_selected = true;
                }

                if(SDL_PointInRect(&cursor, &(*GetWidget("s-music_bar")).getRect())) {
                    (*GetWidget("s-music_drag_button")).setX(cursor.x - ((*GetWidget("s-music_drag_button")).getRect().w/2));
                    
                }

                if(SDL_PointInRect(&cursor, &(*GetWidget("s-sfx_drag_button")).getRect())) {
                    sfx_volume_selected = true;
                }

                if(SDL_PointInRect(&cursor, &(*GetWidget("s-sfx_bar")).getRect())) {
                    (*GetWidget("s-sfx_drag_button")).setX(cursor.x - ((*GetWidget("s-sfx_drag_button")).getRect().w/2));
                }
                leftMouseButtonDown = true;
                leftClick();
                
            }/* else if (event.button.button == SDL_BUTTON_RIGHT){
                //rightClick();
            } */
            break;
        case SDL_MOUSEBUTTONUP:
            if (leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                    
                if (music_volume_selected) {
                    music_volume_selected = false;
                }
                if (sfx_volume_selected) {
                    sfx_volume_selected = false;
                }
                leftMouseButtonDown = false;
            }
            break;

        case SDL_MOUSEMOTION:
            cursor = {event.motion.x, event.motion.y};
            
            if (leftMouseButtonDown && music_volume_selected && cursor.x > (*GetWidget("s-music_bar")).getRect().x && cursor.x < ((*GetWidget("s-music_bar")).getRect().x + (*GetWidget("s-music_bar")).getRect().w - (*GetWidget("s-music_drag_button")).getRect().w)) {

                (*GetWidget("s-music_drag_button")).setX(cursor.x);

            }

            if (leftMouseButtonDown && sfx_volume_selected && cursor.x > (*GetWidget("s-sfx_bar")).getRect().x && cursor.x < ((*GetWidget("s-sfx_bar")).getRect().x + (*GetWidget("s-sfx_bar")).getRect().w - (*GetWidget("s-sfx_drag_button")).getRect().w)) {

                (*GetWidget("s-sfx_drag_button")).setX(cursor.x);

            }
            break;

        case SDL_QUIT:
            (*body)->setRunning(false);
            isRunning = false;
            break;

        default:
            break;
    }
}

void Menu::Update(SDL_Renderer* renderer)
{   
    // SDL_RenderCopy(renderer, LoadTexture("../assets/PNG/Menu/bg1.jpg", renderer), NULL, NULL);

    
    if (isSetting) {
        for(Widget &widget : widgetsS) {
            widget.BlitWidget(renderer);
            
        }
        UpdateSound();
    }
    else // Menu
    {

        for(Widget &widget : widgetsM) {

            if (widget.isHovering(cursor.x, cursor.y)) {

                if (widget.getId() == "s-i"){
                    widget.setTexture(assets.GetTexture("sb2"));

                }
                if (widget.getId() == "playb"){
                    widget.setTexture(assets.GetTexture("mb2"));
                }
            }
            else {
                if (widget.getId() == "s-i"){
                    widget.setTexture(assets.GetTexture("sb"));
                }
                if (widget.getId() == "playb"){
                    widget.setTexture(assets.GetTexture("mb"));
                }
            }
            widget.BlitWidget(renderer);
            
             
        }
    }
    
   
}



void Menu::leftClick() {

    if (isSetting) {
        for(Widget &widget : widgetsS) {
        
            if (widget.isHovering(cursor.x, cursor.y)) {

                if (widget.getId() == "s-cross") {
                    isSetting = false;
                    break;
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
                    break;
                }
                if (widget.getId() == "s-i") {
                    isSetting = true;
                    break;

                }

            } 
        }
    }
    

    
   
    
}





void Menu::UpdateSound() {

    music_volume = ( ((*GetWidget("s-music_drag_button")).getRect().x - (*GetWidget("s-music_bar")).getRect().x) * 100 / (*GetWidget("s-music_bar")).getRect().w ) * MIX_MAX_VOLUME / 100;
    sfx_volume = ( ((*GetWidget("s-sfx_drag_button")).getRect().x - (*GetWidget("s-sfx_bar")).getRect().x) * 100 / (*GetWidget("s-sfx_bar")).getRect().w ) * MIX_MAX_VOLUME / 100;
    audio.music_volume(music_volume);
    audio.sfx_volume(&assets, sfx_volume);


}


Widget* Menu::GetWidget(std::string id) {
    for(Widget &widget : widgetsS) {
        if (widget.getId() == id) {return &widget;}
    }
    for(Widget &widget : widgetsM) {
        if (widget.getId() == id) {return &widget;}
    }
    return NULL;
}