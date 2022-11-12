#include "../include/game.hpp"

/*
    NB : 
        [CURSEUR DE GRILLE]
            - Ne doit s'afficher que lorsqu'il la souris est sur la grille map ou sur l'inventaire
            - Positionner le curseur en fonction de la position de la grille (pour qu'il n'y ait pas de décalage sur l'inventaire)

        [PATHFINDING]

        [WIDGETS]

        [Autres]
            Créer un singleton pour le rendu

            Créer une superclasse pour les instances 

*/

//! Constructor
/**
 * Constructeur de la classe game. Initialise les éléments du jeu.
 * @param title Titre.
 * @param xpos Position en x de la fenêtre.
 * @param ypos Position en y de la fenêtre.
 * @param width Largeur de la fenêtre.
 * @param height Hauteur de la fenêtre.
 * @param fullscreen FullScreen ou non.
*/
Menu::Menu()
{
    

    

    


    grid_cell_size = 64;

    this->inventory = Grid(1,1,grid_cell_size,100, 670);


    grid_cursor = {
        .x = (inventory.GetWidth() - 1) * grid_cell_size,
        .y = (inventory.GetHeight() - 1) * grid_cell_size,
        .w = grid_cell_size,
        .h = grid_cell_size,
    };

    grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size, grid_cell_size};

}



void Menu::Update()
{   
    // Affiche les tiles sur la grille
    DrawTiles();

    if (showgrid){
        // Dessine le grid cursor
        SDL_SetRenderDrawColor(renderer, grid_cursor_color.r, grid_cursor_color.g, grid_cursor_color.b, grid_cursor_color.a);

        //
        SDL_RenderFillRect(renderer, &grid_cursor);

        // Dessine le grid ghost cursor
        SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r, grid_cursor_ghost_color.g, grid_cursor_ghost_color.b, grid_cursor_ghost_color.a);

        //
        SDL_RenderFillRect(renderer, &grid_cursor_ghost);
    }

    // Applique la couleur des lignes (Lire la doc de la fonction pour comprendre le fonctionnement)
    SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g, grid_line_color.b, grid_line_color.a);

    if (showgrid){
        // Affiche la grille map
        map.DrawGrid(renderer);
    }

    // Affiche la grille inventory
    inventory.DrawGrid(renderer);

    //(couleur de fond de base du jeu)
    SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);

   
}

