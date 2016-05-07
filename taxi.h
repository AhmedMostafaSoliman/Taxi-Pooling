#ifndef TAXICAR_H
#define TAXICAR_H
#include <stack>
#include <queue>
#include <vector>
#include "cell.h"
class Taxi
{
    int x,y;
    bool occupied;
    std::stack<char>path;
    char orientation;
public:
    Taxi(int x=0,int y=0);
    bool isOccupied();
    void move();
    std::stack<char>findPath(int desx,int desy, std::vector<std::vector<cell*>> v);
    char getNextMove();
    int getx();
    int gety();
    void setx(int x);
    void sety(int y);
    void setPath(std::stack<char> p);

};

#endif // TAXICAR_H
