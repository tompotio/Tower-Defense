#include "../include/assetsmanager.hpp"

Sprite::Sprite(SDL_Rect rect, SDL_Texture* text){
    this->rect = rect;
    this->texture = text;
}

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
    // Charge l'image
    SDL_Texture* texture = IMG_LoadTexture(renderer, fileName);
    if (!texture){
        std::cerr<<"La texture ne s'est pas chargée! \n";
		exit(EXIT_FAILURE);
    };
	return texture;
}

void TextureManager::DestroyTexture(SDL_Texture* texture)
{
    // Libérer une texture
    SDL_DestroyTexture(texture);
}

void TextureManager::BlitTexture(SDL_Texture* texture,SDL_Renderer* renderer, int x , int y)
{
    SDL_Rect dstcrect; 
    dstcrect.x = x;
    dstcrect.y = y;

    // Récupère les informations de la texture (width et height)
    SDL_QueryTexture(texture, NULL, NULL,&dstcrect.w, &dstcrect.h);

    // Copier (une partie de) la texture dans le renderer
    SDL_RenderCopy(renderer, texture, NULL, &dstcrect);
}

// On suppose les coordonées de rect connues (modifiées lors d'un mouvement etc)
void TextureManager::BlitSprite(Sprite sprite, SDL_Renderer* renderer)
{
    SDL_Rect r = sprite.GetRect();
    
    // Copier (une partie de) la texture dans le renderer
    SDL_RenderCopy(renderer, sprite.GetTexture(), NULL, &r);
}

void AssetManager::AddTexture(std::string id, SDL_Texture* texture)
{
    //emplace() is preferred for efficiency reasons.
    textures.emplace(id, texture);
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

int* Map::ParseMap(const char* fileName){
    return NULL;
}  

void Map::GetTiles(const char* fileName){

}


void Map::PrintMap(const char* fileName){

}