#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QResizeEvent>
#include <QSignalMapper>


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

    (*cells)[3][4]->setState(cell :: Pavement);
    (*cells)[3][15]->setState(cell :: Pavement);
    (*cells)[15][4]->setState(cell :: Pavement);
    (*cells)[15][15]->setState(cell :: Pavement);

     layout->setSpacing(0);
     thread =new DelayThread(this);
     connect(thread,SIGNAL(wakeUp()),this,SLOT(onWakeUp()));
     thread->start();

     ui->widget->setLayout(layout);
     startSimulation();
}


void MainWindow::startSimulation()
{
    addTaxi(0,0);
}

void MainWindow::onCellClick(int c){
    int x=cellMap[c].first;
    int y=cellMap[c].second;
    if(ui->CustomerRadioButton->isChecked()){
        if(firstStep){
            if((*cells)[x][y]->isPavement())
            {
                (*cells)[x][y]->setState(cell:: Customer);
                startx=x;
                starty=y;
                firstStep=0;
            }
        }else{
            if((*cells)[x][y]->isPavement()){
                addCustomer(startx,starty,x,y);
                firstStep=1;
            }
        }
    }else if(ui->PavementRadioButton->isChecked()){
        if(allTaxisAreVacant()&&(*cells)[x][y]->isRoad()){
           (*cells)[x][y]->setState(cell:: Pavement);
        }
    }else if(ui->RoadRadioButton->isChecked()){
        if(allTaxisAreVacant()&&(*cells)[x][y]->isPavement()){
           (*cells)[x][y]->setState(cell:: Road);
        }
    }else if(ui->taxiRadioButton->isChecked()){
        if((*cells)[x][y]->isRoad()){
            addTaxi(x,y);
        }
    }
}

bool MainWindow::allTaxisAreVacant(){
    for(auto i:taxis){
        if(i->isOccupied()) return 0;
    }
    return 1;
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
                curpath=taxis[i]->findPath(curcustomer->getCurrentX(),curcustomer->getCurrentY(),0);
                if(bestpath.size()==0 && curpath.size()>0)
                {
                    bestpath=curpath;
                    bestTaxi=i;
                }
                else if(bestpath.size()>curpath.size() && curpath.size()>0)
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



void MainWindow::on_CustomerRadioButton_toggled(bool checked)
{
    if(!firstStep){
        (*cells)[startx][starty]->setState(cell::Pavement);
    }
    firstStep=true;
}
