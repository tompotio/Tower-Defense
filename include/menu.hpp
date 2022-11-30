#pragma once

#include "assetsmanager.hpp"
#include "widget.hpp"
#include "grid.hpp"
#include "body.hpp"

class Menu
{
    public:
        Menu(Body* body);
        ~Menu() = default;

        void HandleEvents();
        void leftClick();
        //void rightClick(double x, double y);
        void Update(SDL_Renderer* renderer);
        bool running() {return isRunning;}
        bool inSettings() {return isSetting;}
        void DrawVolumeBar();
        Body* GetBody() {return body;}
        AssetManager GetAssets() {return assets;};

        std::vector<Widget> widgets;
        SDL_Rect volume_rect;
        Sprite sprite;
        SDL_Rect rect;
    private:
        AssetManager assets;
        Body* body;
        SDL_Rect WindowSize;
        SDL_Point cursor;
        int sound_volume;
        bool volume_selected;
        bool isRunning;
        bool isSetting;
        bool leftMouseButtonDown;
     
        
};