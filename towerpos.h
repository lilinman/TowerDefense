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
    bool HasTower;         //是否有塔
    BaseTower* myTower;    //位置上的塔
    Selection* selectbox;  //位置上的选择框

public:
    void Draw(QPainter &painter);
    Point get_Cpoint()const;
    bool get_hasTower()const;
    BaseTower* get_myTower()const;
    void set_hasTower(bool);
    void set_myTower(BaseTower*);
    Selection* get_selectbox()const;

};

#endif // TOWERPOS_H
