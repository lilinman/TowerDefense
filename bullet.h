#ifndef BULLET_H
#define BULLET_H
#include"object.h"
#include<QPainter>
#include "point.h"

//继承自object类
class Enemy;
class Bullet: public Object
{
protected:
    Enemy *target=NULL;                     //目标敌人
    double direction;                       //方向
public:
    Bullet(int x,int y,int id,Enemy *e);
    void Draw(QPainter &painter);           //画图
    bool shoot();                           //是否打到敌人
    bool inborder();                        //判断是否在窗口内
    virtual void Move(double d);            //不同的子弹需自己实现移动
    void set_target(Enemy *e);
    Enemy* get_target()const;

    ~Bullet();
};

#endif // BULLET_H
