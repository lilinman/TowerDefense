#ifndef ENEMY_H
#define ENEMY_H

#include<QString>
#include<vector>
using namespace std;
#include "point.h"
#include"object.h"
#include<QPainter>
#include <QMediaPlayer>
//敌人类
class Enemy: public Object
{
private:
    int isdeleted=0;                                //实现消失动画
    QMediaPlayer *player=new QMediaPlayer;          //不同敌人消失时的叫声
    int price;                                      //价格
    int hp;                                         //生命值
    int OriginHp;                                   //原来生命值 用于画出血量条
    int id;                                         //序号
    vector<Point> waypoint;                         //移动路径
    int e_speed;                                    //实时移动速度
    int Speed;                                      //标准速度
    bool isAttacked=false;                          //是否被攻击
    bool isAttackedBy3=false;                       //是否被3号塔攻击
public:
    Enemy(vector<Point> pointar,int x,int y,int id);
    void Draw(QPainter &painter);
    //一系列get/set函数
    int get_isdeleted()const;
    void set_isdeleted(int);
    int get_Price()const;
    bool get_isAttacked()const;
    void set_isAttacked(bool);
    int get_Ohp()const;
    void set_Ohp(int);
    bool get_isAtBy3()const;
    void set_isAtBy3(bool);
    void Move();
    int get_Id() const;
    int get_Hp() const;
    void set_Hp(int a);
    void set_espeed(int);
    int get_espeed()const;
    int get_Speed()const;
    vector<Point> getway() const;
    ~Enemy();

};

#endif // ENEMY_H
