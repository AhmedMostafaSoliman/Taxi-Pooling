#ifndef TAXICAR_H
#define TAXICAR_H
#include <stack>
#include <queue>
#include <vector>
#include "cell.h"
#include "grid.h"
#include "customer.h"
class Taxi
{
    int x,y;
    bool occupied;
    std::stack<char>path;
    char orientation;
    int customerLocationx;
    int customerLocationy;
    int customerDestinationx;
    int customerDestinationy;

public:
    Taxi(int x=0,int y=0);
    bool isOccupied();
    void move();
    std::stack<char>findPath(int desx,int desy);

    int getx();
    int gety();
    void setx(int x);
    void sety(int y);
    void setCustomer(int curx,int cury,int desx,int desy);
    void setPath(std::stack<char> p);

};

#endif // TAXICAR_H
