#ifndef TOWER2_H
#define TOWER2_H
#include"basetower.h"

class Tower2:public BaseTower
{
public:
    Tower2(int,int);
    void upGrade();
    void attack();
    void set_Bullet(int,int,bool);
    ~Tower2();
};

#endif // TOWER2_H
