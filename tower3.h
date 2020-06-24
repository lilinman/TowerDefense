#ifndef TOWER3_H
#define TOWER3_H
#include"basetower.h"

class Tower3:public BaseTower
{
public:
    Tower3(int,int);
    void upGrade();
    void attack(vector<Enemy *>);
    void set_Bullet(int,int,bool);
    void bulletingSound();
    ~Tower3();
};

#endif // TOWER3_H
