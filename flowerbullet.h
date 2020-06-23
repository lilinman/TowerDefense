#ifndef FLOWERBULLET_H
#define FLOWERBULLET_H

#include<bullet.h>
class flowerBullet:public Bullet
{
public:
    flowerBullet(int x,int y,int id,Enemy *e);
    void Move(double d);  //自己实现移动
};

#endif // FLOWERBULLET_H
