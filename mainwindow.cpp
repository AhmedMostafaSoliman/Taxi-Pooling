#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QResizeEvent>
#include <QSignalMapper>:


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QGridLayout;

    QSignalMapper* signalMapper = new QSignalMapper (this) ;

    cells=Grid::getgrid();
    int counter=0;
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            cellMap[counter]={i,j};
            cell* tcell = new cell (this);
            (*cells)[i][j] = tcell;
            connect(tcell,SIGNAL(clicked()),signalMapper,SLOT(map()));
            signalMapper -> setMapping (tcell, counter) ;

            tcell->setScaledContents(1);
            tcell->setMinimumSize(1,1);
            layout->addWidget(tcell, i, j);
            counter++;
        }
    }

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(onCellClick(int))) ;

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
}

void MainWindow::onCellClick(int c){
    int x=cellMap[c].first;
    int y=cellMap[c].second;
    if(!f){
        if((*cells)[x][y]->isPavement())
        {
            (*cells)[x][y]->setState(cell:: Customer);
            startx=x;
            starty=y;
            f=1;
        }
    }else{
        if((*cells)[x][y]->isPavement()){
            addCustomer(startx,starty,x,y);
            f=0;
        }
    }
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

        //qDebug()<<curcustomer->getCurrentX()<<" y "<<curcustomer->getCurrentY()<<" "<<bestTaxi;//<<std::endl;
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
        (*cells)[x][y]->setState(cell:: VacantTaxi);
    }
}

void MainWindow::addCustomer(int curx,int cury,int desx,int desy)
{
    customers.push(new Customer(curx,cury,desx,desy));
}

void MainWindow::resizeEvent(QResizeEvent *event){

    QSize oldSize = event->oldSize();
    QSize actualSize = event->size();
    double mul = actualSize.height()*1.0/oldSize.height();
    if(mul <=0) mul=1;

    qDebug()<<"mul"<<mul;
    for (int i = 0; i < numCols; i++)
        for (int j = 0; j < numRows; j++)
                (*cells)[i][j]->ImageUpd((*cells)[i][j]->getCellWidth()/mul , (*cells)[i][j]->getCellHeight()/mul);

    qDebug()<<"new cell width"<<(*cells)[0][0]->getCellWidth()/mul<<"new cell height"<< (*cells)[0][0]->getCellHeight()/mul;

}


