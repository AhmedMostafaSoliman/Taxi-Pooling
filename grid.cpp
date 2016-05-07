#include "grid.h"

std::vector<std::vector<cell*>> * Grid::cells = nullptr;

std::vector<std::vector<cell*>> *Grid::getgrid() {
  if (!cells)
  {
    Grid::cells=new std::vector<std::vector<cell*>>(numRows,std::vector<cell*>(numCols));
  }
  return cells;
}
