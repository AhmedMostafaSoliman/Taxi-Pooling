#ifndef CELL_H
#define CELL_H
#include <QLabel>

class cell : public QLabel
{
    Q_OBJECT
public:
    enum State {Pavement, Road , Taxi ,Customer};
    cell (QWidget *parent = 0) ;
    State getState();
    bool isRoad();
    bool isPavement();
    void setState(State newState);
    void rotateLabel(bool clockwise);
private:
    void ImageUpd();
    State currentState;
};

#endif // CELL_H
