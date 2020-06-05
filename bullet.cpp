#include "bullet.h"
#include <QtCore/qmath.h>
#include "enemy.h"
#include "mainwindow.h"
Bullet::Bullet(int x,int y,int id,Enemy *t)
    :Object(x,y),target(t)
{
    switch (id)
    {
    case 11: //绿瓶炮弹1
        set_WH(40,40);
        set_Imgpath(":/pics/imgs/绿瓶炮弹1.png");
        break;
    }
    
}
void Bullet::Move()
{
    if(target!=NULL){

    direction=qAtan((double)(position_y-(target->get_Y()+target->get_Height()/2))
                              /(position_x-(target->get_X()+target->get_Width()/2)));
    position_x -= (int) (qCos(direction) * 20);
    position_y -= (int) (qSin(direction) * 20);
    }

}

void Bullet::Draw(QPainter &painter) const{
    painter.drawPixmap(position_x, position_y, width, height,
                       QPixmap(ImgPath));
}

bool Bullet::shoot()
{
    Point tarPoint(target->get_X()+target->get_Width()/2,
                   target->get_Y()+target->get_Height()/2);

    if(tarPoint.is_include(Point(position_x,position_y),20))
    {
        return true;
    }
    else
        return false;
}

bool Bullet::inborder(){
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

