#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer
{
public:
    Customer(int curx=0,int cury=0,int desx=0, int desy=0);
    int getCurrentX() {return this->curx;}
    int getCurrentY() {return this->cury;}
    int getDestinationX() {return this->desx;}
    int getDestinationY() {return this->desy;}

private:
    int curx,cury;
    int desx,desy;
};

#endif // CUSTOMER_H
