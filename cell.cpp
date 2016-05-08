#include "cell.h"

cell::cell (QWidget *parent) : QLabel (parent),
    currentState (Road)
{
    ImageUpd();
}

cell::State cell::getState() { return currentState; }
bool cell::isRoad() { return currentState==cell::Road; }
bool cell::isPavement(){return currentState==cell::Pavement;}


void cell::setState(State newState)
{
    if (currentState != newState)
    {
        currentState = newState;
        ImageUpd();
    }
}

void cell::ImageUpd()
{
    QPixmap roadPixmap(":/images/road.jpg");
    QPixmap pavPixmap(":/images/pav.jpg");
    QPixmap customerPixmap(":/images/customer.png");
    QPixmap occupiedTaxiPixmap(":/images/taxi_occupied.png");
    QPixmap vacantTaxiPixmap(":/images/taxi_vacant.png");


    int w=128,h=128;

    switch (currentState)
    {
        case Pavement: setPixmap(pavPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
        case Road: setPixmap(roadPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
        case Customer:  setPixmap(customerPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
        case OccupiedTaxi: setPixmap(occupiedTaxiPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
        case VacantTaxi:setPixmap(vacantTaxiPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
    }
    //rotateLabel(true);
}

void cell::rotateLabel(bool clockwise)
{
    QMatrix rm;
    int angle;
    if(clockwise)
        angle=-90;
    else
        angle=90;
    rm.rotate(angle);
    setPixmap(this->pixmap()->transformed(rm));
}
