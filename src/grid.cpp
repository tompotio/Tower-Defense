#include "../include/grid.hpp"

Cell::Cell(int x, int y){
    this->x = x;
    this->y = y;
}

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

    for (int x = 0; x < width; x++){
        std::vector<Cell> newrow;
        cells.push_back(newrow);
        for (int y = 0; y < width; y++){
            cells[x].push_back(Cell(x,y));
        }
    }
}

Cell& Grid::GetGridObject(int x, int y){
    return cells[x][y];
}

// Dessine une grille sur l'écran.
void Grid::DrawGrid(SDL_Renderer* renderer){
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

Pathfinding::Pathfinding(Grid grid){
    this->grid = grid;
}

bool Pathfinding::Find(Cell cell, std::vector<Cell> list){
    for(Cell c : list){
        if (c.x == cell.x && c.y == cell.y) return true;
    }
    return false;
}

int Pathfinding::GetPositionInList(Cell cell, std::vector<Cell> list){
    int i = 0;
    for (Cell c : list){
        if (c.x == cell.x && c.y == cell.y)return i;
        i++;
    }
    exit(1);
}

std::vector<Cell> Pathfinding::FindPath(int startX, int startY, int endX, int endY){
    Cell& startCell = grid.GetGridObject(startX,startY);
    Cell& endCell = grid.GetGridObject(endX,endY);

    openList.push_back(startCell);

    for (int x = 0; x < grid.GetWidth(); x++){
        for (int y = 0; y < grid.GetHeight(); y++){
            Cell cell = grid.GetGridObject(x,y);
            cell.gCost = std::numeric_limits<int>::max();;
            cell.CalculateFCost();
            cell.cameFromCell = nullptr;
        }
    }

    startCell.gCost = 0;
    startCell.hCost = CalculateDistanceCost(startCell,endCell);
    startCell.CalculateFCost();

    while (openList.size() > 0){
        Cell& currentCell = GetLowestFCostCell(openList);
        if (&currentCell == &endCell){
            return CalculatePath(endCell);
        }
        // Oui tout ça juste pour retirer un élément spécifique...
        openList.erase(openList.begin() + GetPositionInList(currentCell, openList) - 1);
        closedList.push_back(currentCell);

        for (Cell neighbourcell : GetNeighbourList(currentCell)){
            if (Find(neighbourcell, closedList)) continue;

            int tentativeGCost = currentCell.gCost + CalculateDistanceCost(currentCell, neighbourcell);
            if (tentativeGCost < neighbourcell.gCost){
                neighbourcell.cameFromCell = &currentCell;
                neighbourcell.gCost = tentativeGCost;
                neighbourcell.hCost = CalculateDistanceCost(neighbourcell, endCell);
                neighbourcell.CalculateFCost();

                if (!(Find(neighbourcell, openList))){
                    openList.push_back(neighbourcell);
                }
            }
        }
    }
    std::vector<Cell> null;
    return null;
}

std::vector<Cell> Pathfinding::GetNeighbourList(Cell currentCell){
    std::vector<Cell> neighbourList;

    if (currentCell.x - 1 >= 0){
        // À gauche
        neighbourList.push_back(grid.GetGridObject(currentCell.x -1, currentCell.y));
        // À gauche en bas
        if (currentCell.y - 1 >= 0) neighbourList.push_back(grid.GetGridObject(currentCell.x - 1, currentCell.y - 1));
        // À gauche en haut
        if (currentCell.y + 1 < grid.GetHeight()) neighbourList.push_back(grid.GetGridObject(currentCell.x - 1, currentCell.y + 1));
    }
    if (currentCell.x + 1 < grid.GetWidth()) {
        // À droite
        neighbourList.push_back(grid.GetGridObject(currentCell.x + 1, currentCell.y));
        // À droite en bas
        if (currentCell.y - 1 >= 0) neighbourList.push_back(grid.GetGridObject(currentCell.x + 1, currentCell.y - 1));
        // À droite en haut
        if (currentCell.y + 1 < grid.GetHeight()) neighbourList.push_back(grid.GetGridObject(currentCell.x + 1, currentCell.y + 1));
    }
    // En bas
    if (currentCell.y - 1 >= 0) neighbourList.push_back(grid.GetGridObject(currentCell.x, currentCell.y -1));
    // En haut
    if (currentCell.y + 1 < grid.GetHeight()) neighbourList.push_back(grid.GetGridObject(currentCell.x, currentCell.y + 1));

    return neighbourList;
}

std::vector<Cell> Pathfinding::CalculatePath(Cell endCell){
    std::vector<Cell> path;
    path.push_back(endCell);

    Cell& currentCell = endCell;
    while (currentCell.cameFromCell != nullptr){
        path.push_back(*(currentCell.cameFromCell));
        currentCell = *(currentCell.cameFromCell);

    }

    std::reverse(path.begin(), path.end());
    return path;
}

Cell& Pathfinding::GetLowestFCostCell(std::vector<Cell> List){
    Cell& lowestFCostNode = List[0];
    for (int i = 1; i < List.size(); i++){
        if (List[i].fCost < lowestFCostNode.fCost) {
            lowestFCostNode = List[i];
        }
    }
    return lowestFCostNode;
}

int Pathfinding::CalculateDistanceCost(Cell a, Cell b){
    int xDistance = std::abs(a.x - b.x);
    int yDistance = std::abs(a.y - b.y);
    int remaining = std::abs(xDistance - yDistance);
    return MOVE_DIAGONAL_COST * std::min(xDistance,yDistance) + MOVE_STRAIGHT_COST * remaining;
}