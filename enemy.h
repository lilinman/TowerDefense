#ifndef ENEMY_H
#define ENEMY_H

#include<QString>
#include<vector>
using namespace std;
#include "point.h"
#include"object.h"
#include<QPainter>
//敌人类
class Enemy: virtual public Object
{
private:
    int hp;                 //生命值
    int id;                 //序号
    vector<Point> waypoint;//移动路径
    int e_speed=10;            //移动速度
    int counter=0;
public:
    Enemy(Point pointar[],int len,int x,int y,int id);
    void Draw(QPainter &painter) const;
    void Move();
    int get_Id() const;
    int get_Hp() const;
    void set_Hp(int a);
    vector<Point> getway() const;

};

#endif // ENEMY_H
