#include "tower3.h"

#include"mainwindow.h"
#include<QDebug>
Tower3::Tower3(int x,int y):Object(x,y),BaseTower(x,y)
{
    double rate=1.8;
    TowerLevel=1;
    bulletId=31;
    damege=10;
    range=100;
    t_speed=5;
    set_WH(rate*imgSIZE,rate*imgSIZE);
    set_Imgpath(":/pics/imgs/炮塔3.1.png");

}

void Tower3::upGrade()
{
    if(TowerLevel==3) //顶级退出
        return;

    switch (TowerLevel) {
    case 1:
        range=150;
        set_Imgpath(":/pics/imgs/炮塔3.2.png");
        TowerLevel++;
        break;
    case 2:
        range=200;
        set_Imgpath(":/pics/imgs/炮塔3.3.png");
        TowerLevel++;
    default:
        break;
    }

}
void Tower3::attack(){
    if(bullet->get_target()==NULL)
        return;

    bullet->Move();
    if(bullet->shoot()||bullet->get_target()->get_Hp()<=0)//如果目标敌人已经没有血也更新
    {
        bullet->get_target()->set_Hp(bullet->get_target()->get_Hp()-this->damege);//如果击中减少敌人血量
        if(bullet->get_target()==this->target) //如果目标敌人是同一个
        {
            target=NULL;
            delete bullet;
            bullet=NULL;
        }
        else
        {
            int ex=position_x+width/2;//防御塔中心点坐标
            int ey=position_y+height/2;
            delete bullet;
            bullet=NULL;
            bullet=(new Bullet(ex,ey,bulletId,target));
        }

    }
    else if(!bullet->inborder()){
        int ex=position_x+width/2;//防御塔中心点坐标
        int ey=position_y+height/2;
        delete bullet;
        bullet=(new Bullet(ex,ey,bulletId,target));
    }
    return;
}

void Tower3::set_Bullet(int x,int y,bool b){

    if(b){
        bullet = new Bullet(x,y,bulletId,target);
    }
    else
        bullet=NULL;
}

Tower3::~Tower3()
{
    //qDebug()<<"删除Tower2";
}
