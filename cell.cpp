#include "cell.h"
#include <QDebug>

cell::cell (QWidget *parent) : QLabel (parent),
    currentState (Road)
{
    roadPixmap= QPixmap(":/images/road.jpg");
    pavPixmap = QPixmap(":/images/pav.jpg");
    taxiPixmap = QPixmap(":/images/taxi.png");
    customerPixmap = QPixmap(":/images/customer.png");
    occupiedTaxiPixmap = QPixmap(":/images/occupied_taxi.png");
    vacantTaxiPixmap = QPixmap(":/images/taxi.png");
    reservedTaxiPixmap = QPixmap(":/images/reserved_taxi.png");
    current_width=128,current_height=128;
    ImageUpd(current_width,current_height);
}

void cell::ImageUpd(double w,double h)
{
    current_height=h,current_width=w;
    switch (currentState)
    {
        case Pavement: setPixmap(pavPixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
        case Road: setPixmap(roadPixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
        case Customer:  setPixmap(customerPixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
        case OccupiedTaxi: setPixmap(occupiedTaxiPixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
        case VacantTaxi:setPixmap(vacantTaxiPixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
        case ReservedTaxi: setPixmap(reservedTaxiPixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
    }
}

void cell::setState(State newState)
{
    if (currentState != newState)
    {
        currentState = newState;
        ImageUpd(current_width,current_height);
    }
}


void cell::rotateLabel(bool clockwise)
{
    QMatrix rm;
    int angle;
    if(clockwise) angle=-90;
    else angle=90;
    rm.rotate(angle);
    setPixmap(this->pixmap()->transformed(rm));
}

int cell::getCellHeight() {return current_height;}
int cell::getCellWidth() { return current_width;}
cell::State cell::getState() { return currentState; }
bool cell::isRoad() { return currentState==cell::Road; }
bool cell::isPavement(){return currentState==cell::Pavement;}

