#ifndef TILES_H
#define TILES_H

#include <QDialog>
#include <QList>
#include <QPushButton>

class tiles{
public:
    int row;
    int column;
    int pic;
    friend class page3;

    QPushButton* button;  // اشاره‌گر به دکمه مرتبط در رابط کاربری
    //QList<tiles*> neighbors;
    QList<tiles*> neighbors;       // همسایه‌های فاصله 1
    QList<tiles*> neighborsDist2;  // همسایه‌های فاصله 2
    QList<tiles*> neighborsDist3;  // همسایه‌های فاصله 3
    bool visited;
    int distance;

    //tiles() : row(0), column(0), pic(0), button(nullptr), visited(false) {} //members initializer list
};

#endif // TILES_H
