#include "mapbuilder.h"
#include "ui_mapbuilder.h"

MapBuilder::MapBuilder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapBuilder)
{
    ui->setupUi(this);
}

MapBuilder::~MapBuilder()
{
    delete ui;
}
