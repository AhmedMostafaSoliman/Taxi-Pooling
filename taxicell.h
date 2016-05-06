#include <QLabel>

class TaxiCell : public QLabel
{
    Q_OBJECT

public:
    enum State {Pavement, Road};

    TaxiCell (QWidget *parent = 0) : QLabel (parent),
        currentState (Road)
    {
        ImageUpd();
    }

    State getState() { return currentState; }

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

        int w=128,h=128;

        switch (currentState)
        {
            case Pavement: setPixmap(pavPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
            case Road: setPixmap(roadPixmap.scaled(w,h,Qt::KeepAspectRatio)); break;
        }
    }

    State currentState;
};
