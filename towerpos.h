#ifndef TOWERPOS_H
#define TOWERPOS_H
#include "point.h"
#include"basetower.h"
class TowerPos
{
public:
    TowerPos(Point p);
private:
    bool HasTower;
    Point position;
    BaseTower* myTower;
private:
    Point get_Cpoint()const;
    bool get_hasTower()const;
    BaseTower* get_myTower()const;
    void set_hasTower(bool);
    void set_myTower(BaseTower*);
};

#endif // TOWERPOS_H
