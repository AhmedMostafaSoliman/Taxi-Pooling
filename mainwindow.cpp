#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QGridLayout;

    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            TaxiCell* cell = new TaxiCell (this);
            cells[i][j] = cell;
            layout->addWidget(cell, i, j);
        }
    }

     cells[1][0]->setState(TaxiCell :: Pavement);
     cells[1][1]->setState(TaxiCell :: Pavement);
     cells[1][2]->setState(TaxiCell :: Pavement);
     cells[2][1]->setState(TaxiCell :: Pavement);
     cells[3][1]->setState(TaxiCell :: Pavement);



     layout->setSpacing(0);
     ui->widget->setLayout(layout);

}

MainWindow::~MainWindow()
{
    delete ui;
}
