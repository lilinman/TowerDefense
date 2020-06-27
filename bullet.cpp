#include "bullet.h"
#include <QtCore/qmath.h>
#include "enemy.h"
#include "mainwindow.h"
Bullet::Bullet(int x,int y,int id,Enemy *t)
    :Object(x,y),target(t)
{   //设置三种子弹图片路径
    switch (id)
    {
    case 11: //炮弹1
        set_WH(30,30);
        set_Imgpath(":/pics/imgs/草莓.png");
        break;
    case 21:
        set_WH(30,30);
        set_Imgpath(":/pics/imgs/芒果.png");
        break;
    case 31:
        set_WH(0,0);
        set_Imgpath(":/pics/imgs/冰淇淋攻击效果.png");
        break;
    }
    
}
void Bullet::Move(double d)  //移动子弹d个距离
{
    if(target==NULL)
        return;

    int ey=(target->get_Y()+target->get_Height()/2);
    int ex=target->get_X()+target->get_Width()/2;

    if(ex==position_x){
        if(ey<position_y){
            position_y -= (int)d;
        }
        else
            position_y+=(int)d;
        return;
    }

    direction=qAtan((double)(position_y-ey)
                              /(position_x-ex));
    if(ex<position_x){
        position_x -= (int) (qCos(direction) * d);
        position_y -= (int) (qSin(direction) * d);

    }
    if(ex>position_x){
        position_x += (int) (qCos(direction) * d);
        position_y += (int) (qSin(direction) * d);
    }
    return;
}

void Bullet::Draw(QPainter &painter){
    painter.drawPixmap(position_x, position_y, width, height,
                       QPixmap(ImgPath));
}

bool Bullet::shoot()
{
    if(target==NULL)
        return true;
    Point tarPoint(target->get_X()+target->get_Width()/2,
                   target->get_Y()+target->get_Height()/2);

    if(tarPoint.is_include(Point(position_x,position_y),20))  //在目标敌人中心点15范围内视为击中
    {
        return true;
    }
    else
        return false;
}

bool Bullet::inborder(){      //在游戏界面内
    if(position_x>0&&position_x<=SIZEwid&&position_y>0&&position_y<=SIZEhei)
        return true;
    else
        return false;
}

Enemy* Bullet::get_target()const{
    return target;
}

void Bullet::set_target(Enemy* e){
    target=e;
}
Bullet::~Bullet(){

}
