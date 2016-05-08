#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "cell.h"
#include "taxi.h"
#include "delaythread.h"
#include "customer.h"
#include <vector>
#include "grid.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int numRows=20;
    int numCols=20;
    void startSimulation();
    void addTaxi(int x,int y);
    void addCustomer(int curx,int cury,int desx,int desy);
    int startx;
    int starty;
    bool f=0;
    DelayThread * thread;
    std::map<int,std::pair<int,int>>cellMap;
private:
    std::vector<Taxi *>taxis;
    Ui::MainWindow *ui;
    //cell* cells[numRows][numCols];
    std::vector<std::vector<cell*>> *cells;
    std::queue<Customer *> customers;
    QGridLayout* layout;
public slots:
    void onWakeUp();
    void onCellClick(int c);
    void resizeEvent(QResizeEvent *event);

};

#endif // MAINWINDOW_H
