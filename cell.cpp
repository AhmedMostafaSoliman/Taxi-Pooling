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
    QPixmap taxiPixmap(":/images/taxi.png");
    QPixmap customerPixmap(":/images/customer.png");


    int w=128,h=128;

    switch (currentState)
    {
        case Pavement: setPixmap(pavPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
        case Road: setPixmap(roadPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
        case Taxi:  setPixmap(taxiPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
        case Customer:  setPixmap(customerPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;

    }
}
