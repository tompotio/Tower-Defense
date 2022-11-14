#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <string>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Sprite
{
    public:
		Sprite() = default;
        Sprite(SDL_Rect rect, SDL_Texture* texture);

        bool Sprites_collide(Sprite sp1, Sprite sp2);

		SDL_Rect& GetRect(){return rect;};

		void SetRect(SDL_Rect r){this->rect = r;};

		SDL_Texture* GetTexture(){return texture;};

    private:
        SDL_Rect rect;

		//pointeur vers une texture
        SDL_Texture* texture;

		double angle;
};


namespace TextureManager
{
	SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);

	void BlitTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);

	void DestroyTexture(SDL_Texture* texture);

	void BlitSprite(Sprite sprite, SDL_Renderer* renderer);
};

class AssetManager
{
	public:
		AssetManager() = default;

		~AssetManager() = default;

		//Texture Management
		void AddTexture(std::string id, SDL_Texture* texture);
		SDL_Texture* GetTexture(std::string id);

		//Font Management
		void AddFont(std::string id, std::string path, int fontSize);
		TTF_Font* GetFont(std::string id);

		//Sound Management
		void AddMusic(std::string id, std::string path);
		// Basiquement les WAV
		void AddSFX(std::string id, std::string path); 
		Mix_Music* GetMusic(std::string id);
		Mix_Chunk* GetSFX(std::string id);

	private:
		std::map<std::string, SDL_Texture*> textures;
		std::map<std::string, TTF_Font*> fonts;
		std::map<std::string, Mix_Music*> music;
		std::map<std::string, Mix_Chunk*> sfx;
		std::map<std::string, SDL_Rect*> decortiles;
};

class Map
{
	public:
        static int* ParseMap(const char* fileName);
        static void GetTiles(const char* fileName);
        static void PrintMap(const char* fileName);
        
	private: 
		const int Taille = 16;
};