#ifndef GRID_H
#define GRID_H
#include <vector>
#include<cell.h>
class Grid
{
private:
   static std::vector<std::vector<cell*>> * cells;
   const static int numRows=20;
   const static int numCols=20;
 public:
   static std::vector<std::vector<cell*>> * getgrid();
};

#endif // GRID_H
