#ifndef TOWER1_H
#define TOWER1_H

#include"basetower.h"

class Tower1:public BaseTower
{
public:
    Tower1(int x,int y);
    //实现虚函数
    void upGrade();
    void attack(vector<Enemy *>);
    void set_Bullet(int,int,bool);
    ~Tower1();
};

#endif // TOWER1_H
