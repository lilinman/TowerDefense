#include "tower3.h"

#include"mainwindow.h"
#include<QDebug>
#include<flowerbullet.h>
Tower3::Tower3(int x,int y):BaseTower(x,y)
{
    price =180;
    double rate=1.8;
    TowerLevel=1;
    bulletspeed=15;
    bulletId=31;
    damege=10;
    range=120;
    set_WH(rate*imgSIZE,rate*imgSIZE);
    set_Imgpath(":/pics/imgs/炮塔3.1.png");
    upgradePath=":/pics/imgs/炮塔2.1可升级.png";
    NOupgradePath=":/pics/imgs/炮塔2.1不可升级.png";
    sellPath=":/pics/imgs/炮塔2.1拆塔.png";

}

void Tower3::bulletingSound(){
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sound/sound/fire1.mp3"));
    player->setVolume(2);
    player->play();
}
void Tower3::upGrade()
{
    if(TowerLevel==3) //顶级退出
        return;

    switch (TowerLevel) {
    case 1:
        damege=15;
        range=180;
        set_Imgpath(":/pics/imgs/炮塔3.2.png");
        upgradePath=":/pics/imgs/炮塔2.2可升级.png";
        NOupgradePath=":/pics/imgs/炮塔2.2不可升级.png";
        sellPath=":/pics/imgs/炮塔2.2拆塔.png";
        TowerLevel++;
        break;
    case 2:
        sellPath=":/pics/imgs/炮塔2.3拆塔.png";
        damege=20;
        range=220;
        set_Imgpath(":/pics/imgs/炮塔3.3.png");
        TowerLevel++;
    default:
        break;
    }
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sound/sound/upgrade.mp3"));
    player->setVolume(25);
    player->play();


}
void Tower3::attack(vector<Enemy *> EnemyVec){

    bullet->Move(ebuspeed);


    int ex=position_x+width/2;//防御塔中心点坐标
    int ey=position_y+height/2;

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
                e->set_Hp(e->get_Hp()-damege);
            }
            else
            {
                e->set_isAtBy3(false);
            }
        }
    }

    return;
}

void Tower3::set_Bullet(int ex,int ey,bool b){

    if(b){
        ebuspeed=range/bulletspeed;
        set_isbulleting(true);
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
