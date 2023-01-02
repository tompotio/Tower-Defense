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
SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
    // Charge l'image
    SDL_Texture* texture = IMG_LoadTexture(renderer, fileName);
    if (!texture){
        std::cerr<<"La texture : " << fileName << " ne s'est pas chargée!" << std::endl;
		exit(EXIT_FAILURE);
    };
	return texture;
}

SDL_Rect GetTextureSize(SDL_Texture* texture){
    SDL_Rect dstcrect; 
    
    SDL_QueryTexture(texture, NULL, NULL, &dstcrect.w, &dstcrect.h);
    
    return dstcrect;
}

//! DestroyTexture
/**
 * Détruit la texture en question.
 * @param texture pointeur vers une texture.
*/
void DestroyTexture(SDL_Texture* texture)
{
    // Libérer une texture
    SDL_DestroyTexture(texture);
}


void BlitTextureTransparent(SDL_Texture* texture, SDL_Renderer* renderer, int x , int y){
    SDL_Rect dstcrect; 
    dstcrect.x = x;
    dstcrect.y = y;

    // Récupère les informations de la texture (width et height)
    SDL_QueryTexture(texture, NULL, NULL, &dstcrect.w, &dstcrect.h);
    SDL_SetTextureAlphaMod(texture, 165);
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
void BlitTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x , int y)
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
void BlitSprite(Sprite sprite, SDL_Renderer* renderer)
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

/**
 * Ajoute une music dans assetManager.
 * @param id identifiant de la music.
 * @param path chemin de la music.
*/

void AssetManager::AddMusic(std::string id, std::string path) {

    char* p = &path[0];
    music.emplace(id, Mix_LoadMUS(p));
    
}

void AssetManager::AddSFX(std::string id, std::string path) {
    char* p = &path[0];
    sfx.emplace(id, Mix_LoadWAV(p));
}

Mix_Music* AssetManager::GetMusic(std::string id) {
    return music[id];
}
Mix_Chunk* AssetManager::GetSFX(std::string id) {
    return sfx[id];
}

void init_ttf(){
    if(TTF_Init()==-1) {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    }
}


/**
 * La fonction charge une police
 * @param path le chemin du fichier correpondant à la police
 * @param font_size la taille de la police
 * @return la police chargée
*/
TTF_Font * load_font(const char* path, int font_size){
    TTF_Font *font = TTF_OpenFont(path, font_size);
    if(font == NULL){
        std::cout << "Erreur pendant chargement font: " << SDL_GetError() << std::endl;
    }
    return font;
}

/**
 * \brief La fonction applique un texte dans une certaine police sur le renderer à une certaine position et avec une certaine dimension
 * \param renderer le renderer
 * \param x abscisse du coin en haut à gauche du texte
 * \param y son abscisse
 * \param w la largeur du message
 * \param h sa hauteur
 * \param text le texte à afficher
 * \param font la police
*/
void apply_text(SDL_Renderer *renderer,int x, int y, int w, int h, const char* text, TTF_Font *font){
    SDL_Color color = {255, 255, 255};
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
     
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect2 = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
    
    // liberer la mémoire après avoir appliqué la texture
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void clean_font(TTF_Font * font){
    TTF_CloseFont(font);
}