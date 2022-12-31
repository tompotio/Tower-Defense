#include "../include/grid.hpp"

Cell::Cell(int x, int y, bool tower_on){
    this->x = x;
    this->y = y;
    this->tower_on = tower_on;
}

//! Constructor
/** Constructeur d'une grille.
 * Une grille possède un algorithme de calcul de "path". C'est un algorithme A * (https://fr.wikipedia.org/wiki/Algorithme_A*). 
 * L'algorithme recherche le plus court chemin entre deux cellules.
 * @param width largeur de la grille.
 * @param height hauteur de la grille.
 * @param cellsize taille d'une cellule.
 * @param offset position de la grille par rapport à l'écran SDL (0,0).
*/
Grid::Grid(int width,int height,int cellsize, int offsetx, int offsety, SDL_Renderer* renderer){
    this->width = width;
    this->height = height;
    this->cellsize = cellsize;
    this->offsetx = offsetx;
    this->offsety = offsety;
    this->renderer = renderer;

    for (int x = 0; x < GetWidth(); x++){
        std::vector<Cell> newrow;
        cells.push_back(newrow);
        for (int y = 0; y < GetHeight(); y++){
            cells[x].push_back(Cell(x,y));
        }
    }
}

//! Constructor
/**
 * @param x position x dans vector cells.
 * @param y position y dans vector cells.
 * @param c choix pour le type de la cellule (TOWER, DIRT ou MISC).
*/
void Grid::AffectTypeToCell(int x, int y, char c){
    cells[x][y].type = c;
}

/**
 * Renvoie un pointeur vers une cellule dans la liste cells.
 * @param x position x.
 * @param y position y.
*/
Cell* Grid::GetGridObject(int x, int y){
    return &(cells[x][y]);
}

/**
 * Dessine une grille sur l'écran.
 * @param renderer renderer de SDL.
*/
void Grid::DrawGrid(SDL_Renderer* renderer){
    // Applique la couleur des lignes (Lire la doc de la fonction pour comprendre le fonctionnement)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Dessine les lignes de la grille verticalement à chaque position x
    for(int x = 0; x < GetWidth() + 1; x++){
        SDL_RenderDrawLine(
            renderer, 
            x * GetCellSize() + GetOffsetX(), // x de départ
            GetOffsetY(), // y de départ (câlé sur offset)
            x * GetCellSize() + GetOffsetX(), // x de départ
            GetHeight() * GetCellSize() + GetOffsetY() // y d'arrivée
        );
    }

    // Dessine les lignes horizontales à chaque position y
    for(int y = 0; y < GetHeight() + 1; y++){
        SDL_RenderDrawLine(
            renderer, 
            GetOffsetX(), // x de départ (câlé sur offset)
            y * GetCellSize() + GetOffsetY(), // y de départ
            GetWidth() * GetCellSize() + GetOffsetX(), // x d'arrivée
            y * GetCellSize() + GetOffsetY() // y de départ
        );
    }
}

/**
 * Renvoie vrai si la cellule a été retrouvée dans une liste.
 * @param cell la cellule.
 * @param list la liste.
*/
bool Grid::Find(Cell* cell, std::vector<Cell*> list){
    for(Cell* c : list){
        if (c == cell) return true;
    }
    return false;
}

/**
 * Renvoie la position de la cellule dans une liste.
 * @param cell la cellule.
 * @param list la liste.
*/
int Grid::GetPositionInList(Cell* cell, std::vector<Cell*> list){
    int i = 0;
    for (Cell* c : list){
        if (c == cell)return i;
        i++;
    }
    exit(1);
}

/**
 * Créer une chaîne de cellules à suivre de manière optimale. En d'autres termes, crée le chemin pour les troupes. 
 * @param startX position de départ X de la cellule dans la grille (ex x = 5 et y = 5, la cellule cells[5][5] de grid).
 * @param startY position de départ y de la cellule.
 * @param endX position d'arrivée x.
 * @param endY position d'arrivée y.
*/
std::vector<Cell> Grid::FindPath(int startX, int startY, int endX, int endY){
    Cell* startCell = GetGridObject(startX,startY);
    Cell* endCell = GetGridObject(endX,endY);
    // Vector de taille nulle
    std::vector<Cell> null;

    if((*startCell).type != DIRT || (*endCell).type != DIRT)return null;

    openList.push_back(startCell);

    for (int x = 0; x < GetWidth(); x++){
        for (int y = 0; y < GetHeight(); y++){
            Cell* cell = GetGridObject(x,y);
            cell->gCost = 100000000;
            cell->CalculateFCost();
            cell->cameFromCell = nullptr;
        }
    }

    startCell->gCost = 0;
    startCell->hCost = CalculateDistanceCost(startCell,endCell);
    startCell->CalculateFCost();

    // Tant qu'il y a des cellules dans openlist à traiter on lance l'algorithme
    while (openList.size() > 0){
        Cell* currentCell = GetLowestFCostCell();
        if (currentCell == endCell){
            return CalculatePath(endCell);
        }
        // On retire la cellule courante d'openlist car elle a été traité et est mise dans closedlist
        openList.erase(openList.begin() + GetPositionInList(currentCell, openList));
        closedList.push_back(currentCell);

        for (Cell* neighbourcell : GetNeighbourList(currentCell)){// À optimiser
            if (Find(neighbourcell, closedList)) continue; // Mettre l'information parcourue dans la cellule
            if ((*neighbourcell).type == DIRT){
                int tentativeGCost = currentCell->gCost + CalculateDistanceCost(currentCell, neighbourcell);
                if (tentativeGCost < neighbourcell->gCost){
                    neighbourcell->cameFromCell = currentCell;
                    neighbourcell->gCost = tentativeGCost;
                    neighbourcell->hCost = CalculateDistanceCost(neighbourcell, endCell);
                    neighbourcell->CalculateFCost();
                    if (!(Find(neighbourcell, openList))){
                        openList.push_back(neighbourcell);
                    }
                }
            }
        }
    }
    return null;
}

/**
 * Renvoie une liste des cellules voisines d'une cellule.
 * @param currentCell cellule en cours d'analyse.
*/
std::vector<Cell*> Grid::GetNeighbourList(Cell* currentCell){
    std::vector<Cell*> neighbourList;
    if (currentCell->x - 1 >= 0){
        // À gauche
        neighbourList.push_back(GetGridObject(currentCell->x -1, currentCell->y));
        // À gauche en bas
        if (currentCell->y - 1 >= 0) neighbourList.push_back(GetGridObject(currentCell->x - 1, currentCell->y - 1));
        // À gauche en haut
        if (currentCell->y + 1 < GetHeight()) neighbourList.push_back(GetGridObject(currentCell->x - 1, currentCell->y + 1));
    }
    if (currentCell->x + 1 < GetWidth()) {
        // À droite
        neighbourList.push_back(GetGridObject(currentCell->x + 1, currentCell->y));
        // À droite en bas
        if (currentCell->y - 1 >= 0) neighbourList.push_back(GetGridObject(currentCell->x + 1, currentCell->y - 1));
        // À droite en haut
        if (currentCell->y + 1 < GetHeight()) neighbourList.push_back(GetGridObject(currentCell->x + 1, currentCell->y + 1));
    }
    // En bas
    if (currentCell->y - 1 >= 0) neighbourList.push_back(GetGridObject(currentCell->x, currentCell->y -1));
    // En haut
    if (currentCell->y + 1 < GetHeight()) neighbourList.push_back(GetGridObject(currentCell->x, currentCell->y + 1));

    return neighbourList;
}

/**
 * Utilise la cellule d'arrivée pour retracer le chemin optimal dans une liste et la renverse pour que l'index 0 corresponde à la cellule de départ.
 * @param endCell Cellule d'arrivée.
*/
std::vector<Cell> Grid::CalculatePath(Cell* endCell){
    std::vector<Cell> path;
    path.push_back(*endCell);

    Cell* currentCell = endCell;
    // Lire le chemin revient à lire la jointure entre chaque cellule (c.f cameFromCell), donc on vide openList et closedList.
    openList.clear();
    closedList.clear();
    
    while (!(currentCell->cameFromCell == nullptr)){
        path.push_back(*currentCell->cameFromCell);
        currentCell = (currentCell->cameFromCell);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// Renvoie la cellule dont le coût est le plus faible dans la liste openList.
Cell* Grid::GetLowestFCostCell(){
    Cell* lowestFCostNode = openList[0];

    for (int i = 1; i < openList.size(); i++){
        if (openList[i]->fCost < lowestFCostNode->fCost) {
            lowestFCostNode = openList[i];
        }
    }
    return lowestFCostNode;
}

/**
 * Renvoie le coût de ddistance entre deux cellules (utilisé pour "l'heuristic cost", l'hypothèse de coût sans obstacle).
 * @param a une cellule.
 * @param b une cellule.
*/
int Grid::CalculateDistanceCost(Cell* a, Cell* b){
    int xDistance = std::abs(a->x - b->x);
    int yDistance = std::abs(a->y - b->y);
    int remaining = std::abs(xDistance - yDistance);
    return MOVE_DIAGONAL_COST * std::min(xDistance,yDistance) + MOVE_STRAIGHT_COST * remaining;
}