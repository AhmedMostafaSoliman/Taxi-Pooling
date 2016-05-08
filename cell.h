#ifndef CELL_H
#define CELL_H
#include <QLabel>

class cell : public QLabel
{
    Q_OBJECT
public:
    enum State {Pavement, Road , VacantTaxi ,OccupiedTaxi, ReservedTaxi, Customer};
    cell (QWidget *parent = 0) ;
    State getState();
    bool isRoad();
    bool isPavement();
    void setState(State newState);
    void rotateLabel(bool clockwise);
    int  getCellWidth();
    int  getCellHeight();
    void ImageUpd(double w,double h);

private:
    double current_width,current_height;
    State currentState;
    QPixmap roadPixmap;
    QPixmap pavPixmap;
    QPixmap taxiPixmap;
    QPixmap customerPixmap;
};

#endif // CELL_H
