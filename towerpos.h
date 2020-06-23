#ifndef TOWERPOS_H
#define TOWERPOS_H
#include<QPainter>
#include "point.h"
#include"basetower.h"
#include"selection.h"
#include"object.h"
class TowerPos: public Object
{
public:
    TowerPos(Point p);
private:
    bool HasTower;
    BaseTower* myTower;
    Selection* selectbox;

public:
     void Draw(QPainter &painter);
    int get_X() const;
    int get_Y() const;
    Point get_Cpoint()const;
    bool get_hasTower()const;
    BaseTower* get_myTower()const;
    void set_hasTower(bool);
    void set_myTower(BaseTower*);
    Selection* get_selectbox()const;
    //void set_selectionbox(Selection*);
};

#endif // TOWERPOS_H
