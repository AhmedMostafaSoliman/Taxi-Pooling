#ifndef CELL_H
#define CELL_H
#include <QLabel>

class cell : public QLabel
{
    Q_OBJECT

public:
    enum State {Pavement, Road , Taxi ,Customer};

    cell (QWidget *parent = 0) : QLabel (parent),
        currentState (Road)
    {
        ImageUpd();
    }

    State getState() { return currentState; }
    bool isRoad() { return currentState==cell::Road; }

    void setState(State newState)
    {
        if (currentState != newState)
        {
            currentState = newState;
            ImageUpd();
        }
    }

private:
    void ImageUpd()
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

    State currentState;
};

#endif // TAXICAR_H
