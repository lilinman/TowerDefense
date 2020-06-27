#include "tower3.h"

#include"mainwindow.h"
#include<QDebug>
#include<flowerbullet.h>
Tower3::Tower3(int x,int y):BaseTower(x,y)
{
    price =180;
    upgradePrice=280;
    sellPrice=144;
    double rate=1.8;
    TowerLevel=1;
    bulletspeed=15;
    bulletId=31;
    damege=8;
    range=140;
    set_WH(rate*imgSIZE,rate*imgSIZE);
    set_Imgpath(":/pics/imgs/炮塔3.1.png");
    upgradePath=":/pics/imgs/炮塔2.1可升级.png";
    NOupgradePath=":/pics/imgs/炮塔2.1不可升级.png";
    sellPath=":/pics/imgs/炮塔2.1拆塔.png";

}

void Tower3::bulletingSound(){

    player->setMedia(QUrl("qrc:/sound/sound/fire1.mp3"));
    player->setVolume(20);
    player->play();

}
void Tower3::upGrade()
{
    if(TowerLevel==3) //顶级退出
        return;

    switch (TowerLevel) {
    case 1:
        upgradePrice=360;
        sellPrice=368;
        damege=10;
        range=170;
        set_Imgpath(":/pics/imgs/炮塔3.2.png");
        upgradePath=":/pics/imgs/炮塔2.2可升级.png";
        NOupgradePath=":/pics/imgs/炮塔2.2不可升级.png";
        sellPath=":/pics/imgs/炮塔2.2拆塔.png";
        TowerLevel++;
        break;
    case 2:
        upgradePrice=0;
        sellPrice=656;
        sellPath=":/pics/imgs/炮塔2.3拆塔.png";
        damege=12;
        range=210;
        set_Imgpath(":/pics/imgs/炮塔3.3.png");
        TowerLevel++;
    default:
        break;
    }

}
void Tower3::attack(vector<Enemy *> EnemyVec){


    int ex=position_x+width/2;//防御塔中心点坐标
    int ey=position_y+height/2;

    if(bullet==NULL)
    {
        for(auto e:EnemyVec)//遍历敌人如果没有在攻击范围内删除效果
        {
            int px=e->get_X()+e->get_Width()/2;
            int py=e->get_Y()+e->get_Height()/2;
            if((ex-px)*(ex-px)+(ey-py)*(ey-py)>range*range)
            {

                 e->set_isAtBy3(false);
            }
        }
        return;
    }

    if((bullet->get_X()-ex)*(bullet->get_X()-ex)+
            (bullet->get_Y()-ey)*(bullet->get_Y()-ey)>=range*range)  //达到目标大小
    {
        target=NULL;
        delete bullet;
        bullet=NULL;


        for(auto e:EnemyVec)//实现攻击所有范围内敌人
        {
            int px=e->get_X()+e->get_Width()/2;//敌人中心点坐标
            int py=e->get_Y()+e->get_Height()/2;
            if((ex-px)*(ex-px)+(ey-py)*(ey-py)<range*range)//在范围内
            {
                e->set_isAttacked(true);
                e->set_isAtBy3(true);
                e->set_Hp(e->get_Hp()-damege);   //减少敌人血量
            }
            else
            {
                e->set_isAtBy3(false);
            }
        }
    }

    else
    {
        bullet->Move(ebuspeed);//移动子弹
    }

    return;
}

void Tower3::set_Bullet(int ex,int ey,bool b){

    if(b){
        ebuspeed=range/bulletspeed;
        set_isbulleting(true);//动画效果
        this->set_WH(this->get_Width(),this->get_Height()+5);
        bullet = new flowerBullet(ex,ey,bulletId,NULL); //子弹类型不同
    }
    else
        bullet=NULL;
}

Tower3::~Tower3()
{
    //qDebug()<<"删除Tower2";
}
