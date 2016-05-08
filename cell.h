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
    int  getCellWidth();
    int  getCellHeight();
    void setState(State newState);
    bool isRoad();
    bool isPavement();
    void rotateLabel(bool clockwise);
    void ImageUpd(double w,double h);

private:
    double current_width,current_height;
    State currentState;
    QPixmap roadPixmap;
    QPixmap pavPixmap;
    QPixmap taxiPixmap;
    QPixmap customerPixmap;
    QPixmap occupiedTaxiPixmap;
    QPixmap vacantTaxiPixmap;
    QPixmap reservedTaxiPixmap;

signals:
   void clicked();
protected:
   void mousePressEvent(QMouseEvent*);

};

#endif // CELL_H
