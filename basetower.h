#ifndef BASETOWER_H
#define BASETOWER_H


#include<QString>
#include "point.h"
#include"object.h"
#include<QPainter>
#include<vector>
#include<bullet.h>
using namespace std;
class Enemy;
class BaseTower: virtual public Object
{
public:
    BaseTower(int x,int y,int id);

protected:
    int bulletId;
    int damege;
    int range;              //防御塔的射程
    int id;
    int t_speed;
    int counter = 0;        //用于控制发射子弹的速度
    Enemy *target=NULL;     //目标敌人
    Bullet *bullet=NULL;         //子弹

public:
    Enemy *get_Target() const;
    void set_Target(Enemy *t);
    void CreatBullet();             //新建子弹
    void Draw(QPainter& painter) ;
    int get_speed()const;
    int get_Damege() const;
    void set_Damege(int) ;
    int get_Range() const;
    void set_Range(int);
    Bullet* get_bullet()const;
    void set_Bullet(Bullet *);
    int get_BulletID()const;
    void set_BulletID(int);
    void del_Bullet();
};
#endif // BASETOWER_H
