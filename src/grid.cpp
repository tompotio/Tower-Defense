#include "../include/grid.hpp"

//! Constructor
/**
 * @param width largeur de la grille.
 * @param height hauteur de la grille.
 * @param cellsize taille d'une cellule.
 * @param offset position de la grille par rapport à l'écran SDL (0,0).
*/
Grid::Grid(int width,int height,int cellsize, int offsetx, int offsety){
    this->width = width;
    this->height = height;
    this->cellsize = cellsize;
    this->offsetx = offsetx;
    this->offsety = offsety;
}