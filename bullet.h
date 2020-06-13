#ifndef BULLET_H
#define BULLET_H
#include"object.h"
#include<QPainter>
#include "point.h"

class Enemy;
class Bullet: virtual public Object
{
protected:
    Enemy *target=NULL;  //目标敌人
    double direction;  //方向
public:
    Bullet(int x,int y,int id,Enemy *e);
    bool shoot();            //是否打到敌人
    bool inborder();        //判断是否在窗口内
    void Draw(QPainter &painter) const;
    void Move();
    Enemy* get_target()const;
    void set_target(Enemy *e) ;
};

#endif // BULLET_H
