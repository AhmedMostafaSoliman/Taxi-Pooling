#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer
{
public:
    Customer(int curx,int cury,int desx , int desy);
    int getCurrentX() {return this->curx;}
    int getCurrentY() {return this->cury;}
    int getDestinationX() {return this->desx;}
    int getDestinationY() {return this->desy;}

private:
    int curx,cury;
    int desx,desy;
};

#endif // CUSTOMER_H
