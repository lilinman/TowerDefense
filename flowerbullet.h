#ifndef FLOWERBULLET_H
#define FLOWERBULLET_H

#include<bullet.h>

//太阳花类子弹 继承自Bullet
class flowerBullet:public Bullet
{
public:
    flowerBullet(int x,int y,int id,Enemy *e);
    void Move(double d);  //自己实现移动

};

#endif // FLOWERBULLET_H
