#pragma once

#include "assetsmanager.hpp"
#include "audiomanager.hpp"
#include "widget.hpp"
#include "grid.hpp"
#include "body.hpp"

class Menu
{
    public:
        Menu(Body** body);
        ~Menu() = default;

        void HandleEvents();
        void leftClick();
        //void rightClick(double x, double y);
        void Update(SDL_Renderer* renderer);
        bool running() {return isRunning;}
        bool inSettings() {return isSetting;}
        void UpdateSound();

        Widget* GetWidget(std::string id);

        Body** GetBody() {return body;}
        AssetManager GetAssets() {return assets;};

        std::vector<Widget> widgetsM;
        std::vector<Widget> widgetsS;
        Sprite sprite;
        SDL_Rect rect;
    private:
        AssetManager assets;
        AudioManager audio;
        Body** body;
        SDL_Rect WindowSize;
        SDL_Point cursor;
        int music_volume;
        int sfx_volume;
        bool music_volume_selected;
        bool sfx_volume_selected;
        bool isRunning;
        bool isSetting;
        bool leftMouseButtonDown;
     
        
};