#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QGridLayout;
    cells=std::vector<std::vector<cell*>>(numRows,std::vector<cell*>(numCols));

    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            cell* tcell = new cell (this);
            cells[i][j] = tcell;
            tcell->setScaledContents(1);
            layout->addWidget(tcell, i, j);
        }
    }
     cells[1][1]->setState(cell :: Pavement);
     cells[1][2]->setState(cell :: Pavement);
     cells[2][1]->setState(cell :: Pavement);
     cells[3][1]->setState(cell :: Pavement);
     cells[7][7]->setState(cell:: Customer);

     layout->setSpacing(0);
     thread =new DelayThread(this);
     connect(thread,SIGNAL(wakeUp()),this,SLOT(onWakeUp()));
     thread->start();

     ui->widget->setLayout(layout);
     startSimulation();
}

void MainWindow::startSimulation()
{
    int x=0,y=0;
    taxis.push_back(new Taxi(x,y));
    cells[x][y]->setState(cell :: Taxi);
    customers.push(new Customer(10,10,1,1));
    cells[10][10]->setState(cell:: Customer);
    taxis[0]->setPath(taxis[0]->findPath(10,10,cells));
}

void MainWindow::onWakeUp()
{
    for(auto i:taxis)
    {
        char dir=i->getNextMove();
        if(dir== 'r')
        {
            cells[i->getx()][i->gety()]->setState(cell :: Road);
            i->sety(i->gety()+1);
            i->move();
            cells[i->getx()][i->gety()]->setState(cell :: Taxi);
        }
        else if(dir == 'l')
        {
            cells[i->getx()][i->gety()]->setState(cell :: Road);
            i->sety(i->gety()-1);
            i->move();
            cells[i->getx()][i->gety()]->setState(cell :: Taxi);

        }
        else if(dir == 'u')
        {
            cells[i->getx()][i->gety()]->setState(cell :: Road);
            i->setx(i->getx()-1);
            i->move();
            cells[i->getx()][i->gety()]->setState(cell :: Taxi);

        }
        else if(dir == 'd')
        {
            cells[i->getx()][i->gety()]->setState(cell :: Road);
            i->setx(i->getx()+1);
            i->move();
            cells[i->getx()][i->gety()]->setState(cell :: Taxi);
        }
        /*
        */
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTaxi(Taxi * t)
{
    taxis.push_back(t);
}

/*void MainWindow::resizeEvent(QResizeEvent *event)
{

    QSize oldSize = event->oldSize();
    QSize actualSize = event->size();

    if(ui->label->isVisible())
    {

    double width = actualSize.width() / (double)oldSize.width(),
    height = actualSize.height() / (double)oldSize.height();

    cells[0][0]->resize(ui->label->size().width() * width,
                      ui->label->size().height() * height);
    }
}*/
