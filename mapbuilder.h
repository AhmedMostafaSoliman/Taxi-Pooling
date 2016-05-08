#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include <QMainWindow>

namespace Ui {
class MapBuilder;
}

class MapBuilder : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapBuilder(QWidget *parent = 0);
    ~MapBuilder();

private:
    Ui::MapBuilder *ui;
};

#endif // MAPBUILDER_H
