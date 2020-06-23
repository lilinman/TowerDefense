#ifndef BASETOWER_H
#define BASETOWER_H


#include<QString>
#include "point.h"
#include"object.h"
#include<QPainter>
#include<vector>
#include<bullet.h>
using namespace std;
//class Enemy;

//防御塔基类
class BaseTower:public Object
{
public:
    BaseTower(int x,int y);

protected:
    bool isbulleting=false;
    int buyPrice=0;
    int sellPrice;
    int upgradePrice;
    int Hp=10;               //防御塔生命值
    int TowerLevel;
    int bulletId;
    int damege;
    int range;              //防御塔的射程
    double bulletspeed;
    double ebuspeed=0;
    double counter = 0;        //用于控制发射子弹的速度
    Enemy *target=NULL;     //目标敌人
    Bullet *bullet=NULL;         //子弹

public:
    virtual void upGrade() = 0;//纯虚函数 不同的炮塔实现啊不同的升级 攻击功能
    virtual void attack(vector<Enemy *>) = 0;
    virtual void set_Bullet(int,int,bool) = 0;//纯虚函数 实现不同子弹
    void Draw(QPainter &painter);
    int get_TowerLevel() const;
    void set_TowerLevel(int );
    int get_Hp()const;
    void set_Hp(int);
    Enemy *get_Target() const;
    void set_Target(Enemy *t);
    int get_Damege() const;
    void set_Damege(int) ;
    int get_Range() const;
    void set_Range(int);
    int get_BulletID()const;
    void set_BulletID(int);
    void set_isbulleting(bool);
    bool get_isbulleting()const;
    Bullet * get_Bullet()const;

    virtual ~BaseTower();

};
#endif // BASETOWER_H
