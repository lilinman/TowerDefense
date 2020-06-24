#ifndef TOWER2_H
#define TOWER2_H
#include"basetower.h"

class Tower2:public BaseTower
{
public:
    Tower2(int,int);
    void upGrade();
    void attack(vector<Enemy *>);
    void set_Bullet(int,int,bool);
    void bulletingSound();
    ~Tower2();

private:
    int cutSpeed;
    int tarNum;

};

#endif // TOWER2_H
