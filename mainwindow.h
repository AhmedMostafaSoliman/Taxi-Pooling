#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "taxicell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static const int numRows=5;
    static const int numCols=5;

private:
    Ui::MainWindow *ui;
    TaxiCell* cells[numRows][numCols];
    QGridLayout* layout;
};

#endif // MAINWINDOW_H
