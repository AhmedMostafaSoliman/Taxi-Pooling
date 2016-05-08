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

    cells=Grid::getgrid();

    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            cell* tcell = new cell (this);
            (*cells)[i][j] = tcell;
            tcell->setScaledContents(1);
            layout->addWidget(tcell, i, j);
        }
    }
     (*cells)[10][10]->setState(cell :: Pavement);
     (*cells)[5][2]->setState(cell :: Pavement);
     (*cells)[2][1]->setState(cell :: Pavement);
     (*cells)[3][1]->setState(cell :: Pavement);
    (*cells)[1][1]->setState(cell :: Pavement);
    (*cells)[5][5]->setState(cell :: Pavement);
    (*cells)[17][11]->setState(cell :: Pavement);
    (*cells)[13][8]->setState(cell :: Pavement);
   (*cells)[8][13]->setState(cell :: Pavement);

     layout->setSpacing(0);
     thread =new DelayThread(this);
     connect(thread,SIGNAL(wakeUp()),this,SLOT(onWakeUp()));
     thread->start();

     ui->widget->setLayout(layout);
     startSimulation();
}

void MainWindow::startSimulation()
{
    addTaxi(15,15);
    addTaxi(0,0);
    addTaxi(8,7);
    addCustomer(10,10,1,1);
    addCustomer(5,2,1,1);
    addCustomer(3,1,1,1);
    addCustomer(5,5,17,11);
    addCustomer(13,8,8,13);
}

void MainWindow::onWakeUp()
{
    while(!customers.empty())
    {
        Customer * curcustomer=customers.front();
        int bestTaxi=-1;
        std::stack<char>curpath,bestpath;
        for(int i=0;i<taxis.size();i++)
        {
            if(!taxis[i]->isOccupied())
            {
                curpath=taxis[i]->findPath(curcustomer->getCurrentX(),curcustomer->getCurrentY());
                if(bestpath.size()==0)
                {
                    bestpath=curpath;
                    bestTaxi=i;
                }
                else if(bestpath.size()>curpath.size())
                {
                    bestpath=curpath;
                    bestTaxi=i;
                }
            }
        }

        qDebug()<<curcustomer->getCurrentX()<<" y "<<curcustomer->getCurrentY()<<" "<<bestTaxi;//<<std::endl;
        if(bestTaxi!=-1)
        {
            customers.pop();
            taxis[bestTaxi]->setPath(bestpath);
            taxis[bestTaxi]->setCustomer(curcustomer->getCurrentX(),curcustomer->getCurrentY(),curcustomer->getDestinationX(),curcustomer->getDestinationY());
        }
        else
        {
            break;
        }
    }

    for(auto t:taxis)
    {
        t->move();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTaxi(int x,int y)
{
    if((*cells)[x][y]->isRoad())
    {
        taxis.push_back(new Taxi(x,y));
        (*cells)[x][y]->setState(cell:: Taxi);
    }
}

void MainWindow::addCustomer(int curx,int cury,int desx,int desy)
{
    if((*cells)[curx][cury]->isPavement() && (*cells)[desx][desy]->isPavement())
    {
        customers.push(new Customer(curx,cury,desx,desy));
        (*cells)[curx][cury]->setState(cell:: Customer);
    }
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
