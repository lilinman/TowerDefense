#include "bullet.h"
#include <QtCore/qmath.h>
#include "enemy.h"
#include "mainwindow.h"
Bullet::Bullet(int x,int y,int id,Enemy *t)
    :Object(x,y),target(t)
{
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
        set_WH(30,30);
        set_Imgpath(":/pics/imgs/西瓜.png");
        break;
    }
    
}
void Bullet::Move()
{
    if(target==NULL)
        return;

    int ey=(target->get_Y()+target->get_Height()/2);
    int ex=target->get_X()+target->get_Width()/2;

    if(ex==position_x){
        if(ey<position_y){
            position_y -= 15;
        }
        else
            position_y+=15;
        return;
    }

    direction=qAtan((double)(position_y-ey)
                              /(position_x-ex));
    if(ex<position_x){
        position_x -= (int) (qCos(direction) * 20);
        position_y -= (int) (qSin(direction) * 20);

    }
    if(ex>position_x){
        position_x += (int) (qCos(direction) * 20);
        position_y += (int) (qSin(direction) * 20);
    }
    return;
}

void Bullet::Draw(QPainter &painter) const{
    painter.drawPixmap(position_x, position_y, width, height,
                       QPixmap(ImgPath));
    if(target!=NULL)
         painter.drawRect(target->get_X(),target->get_Y(),90,90);
}

bool Bullet::shoot()
{
    if(target==NULL)
        return true;
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
Bullet::~Bullet(){

}
