#include "../include/assetsmanager.hpp"

//! Constructor
/**
 * @param rect rect.
 * @param texture texture.
*/
Sprite::Sprite(SDL_Rect rect, SDL_Texture* texture){
    this->rect = rect;
    this->texture = texture;
}

//! LoadTexture
/**
 * Charge une texture et la renvoie sous format SDL_Texture.
 * @param fileName chemin vers le fichier.
 * @param renderer renderer de SDL.
*/
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

SDL_Rect TextureManager::GetTextureSize(SDL_Texture* texture){
    SDL_Rect dstcrect; 
    
    SDL_QueryTexture(texture, NULL, NULL, &dstcrect.w, &dstcrect.h);
    
    return dstcrect;
}

//! DestroyTexture
/**
 * Détruit la texture en question.
 * @param texture pointeur vers une texture.
*/
void TextureManager::DestroyTexture(SDL_Texture* texture)
{
    // Libérer une texture
    SDL_DestroyTexture(texture);
}


void TextureManager::BlitTextureTransparent(SDL_Texture* texture, SDL_Renderer* renderer, int x , int y){
    SDL_Rect dstcrect; 
    dstcrect.x = x;
    dstcrect.y = y;

    // Récupère les informations de la texture (width et height)
    SDL_QueryTexture(texture, NULL, NULL, &dstcrect.w, &dstcrect.h);
    SDL_SetTextureAlphaMod(texture, 150);
    // Copier (une partie de) la texture dans le renderer
    SDL_RenderCopy(renderer, texture, NULL, &dstcrect);
}

//! BlitTexture
/**
 * Applique une texture sur le renderer.
 * @param texture pointeur vers une texture.
 * @param renderer renderer de SDL.
 * @param x position en x où placer la texture.
 * @param y position en y où placer la texture.
*/
void TextureManager::BlitTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x , int y)
{
    SDL_Rect dstcrect; 
    dstcrect.x = x;
    dstcrect.y = y;
    // SDL_SetTextureAlphaMod(texture, 255);
    // Récupère les informations de la texture (width et height)
    SDL_QueryTexture(texture, NULL, NULL, &dstcrect.w, &dstcrect.h);

    // Copier (une partie de) la texture dans le renderer
    SDL_RenderCopy(renderer, texture, NULL, &dstcrect);
}

//! BlitSprite
/**
 * Applique une texture sur le renderer depuis un sprite.
 * On suppose les coordonées de rect connues (modifiées lors d'un mouvement etc)
 * @param sprite objet sprite.
 * @param renderer renderer de SDL.
*/
void TextureManager::BlitSprite(Sprite sprite, SDL_Renderer* renderer)
{
    SDL_Rect r = sprite.GetRect();
    
    // Copier (une partie de) la texture dans le renderer
    SDL_RenderCopy(renderer, sprite.GetTexture(), NULL, &r);
}

//! AddTexture
/**
 * Ajoute une texture dans assetManager.
 * @param id identifiant de la texture.
 * @param texture texture à stocker.
*/
void AssetManager::AddTexture(std::string id, SDL_Texture* texture)
{
    //emplace() is preferred for efficiency reasons.
    textures.emplace(id, texture);
}

//! GetTexture
/**
 * Récupère une texture stockée dans assetManager.
 * @param id identifiant de la texture.
*/
SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}