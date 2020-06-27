#include "tower1.h"
#include"mainwindow.h"
#include<QDebug>
#include<QTimer>
#include<QSlider>
#include<QMediaPlaylist>
Tower1::Tower1(int x,int y): BaseTower(x,y)
{
   //初始化参数
    price=100;
    upgradePrice=180;
    sellPrice=80;
    double rate=1.8;
    bulletspeed=9;
    TowerLevel=1;
    bulletId=11;
    damege=10;
    range=120;
    set_WH(rate*imgSIZE,rate*imgSIZE);
    set_Imgpath(":/pics/imgs/炮塔1.1.png");
    upgradePath=":/pics/imgs/炮塔1.1可升级.png";
    NOupgradePath=":/pics/imgs/炮塔1.1不可升级.png";
    sellPath=":/pics/imgs/炮塔1.1拆塔.png";

}
void Tower1::bulletingSound(){

      player->setMedia(QUrl("qrc:/sound/sound/Bullet1.mp3"));
      player->setVolume(40);
      player->play();

}
void Tower1::upGrade()
{
    if(TowerLevel==3) //顶级退出
        return;
    //升级
    switch (TowerLevel) {
    case 1:
        damege=15;
        upgradePrice=260;
        sellPrice=224;
        bulletspeed=8;
        range=150;
        set_Imgpath(":/pics/imgs/炮塔1.2.png");
        upgradePath=":/pics/imgs/炮塔1.2可升级.png";
        NOupgradePath=":/pics/imgs/炮塔1.2不可升级.png";
        sellPath=":/pics/imgs/炮塔1.2拆塔.png";
        TowerLevel++;
        break;
    case 2:
        damege=20;
        upgradePrice=0;
        sellPrice=432;
        bulletspeed=7;
        range=180;
        sellPath=":/pics/imgs/炮塔1.3拆塔.png";
        set_Imgpath(":/pics/imgs/炮塔1.3.png");
        TowerLevel++;
    default:
        break;
    }


}
void Tower1::attack(vector<Enemy *> EnemyVec){
    for(auto e:EnemyVec){
        e->set_Hp(e->get_Hp());        //没什么意义为了让他不出警告
    }
    if(bullet==NULL)
        return;

    bullet->Move(ebuspeed);
    if(bullet->shoot()||bullet->get_target()->get_Hp()<=0)//如果目标敌人已经没有血也更新
    {
        bullet->get_target()->set_Hp(bullet->get_target()->get_Hp()-this->damege);//如果击中减少敌人血量
        bullet->get_target()->set_isAttacked(true);//被攻击

        if(bullet->get_target()==this->target) //如果目标敌人和子弹的目标敌人是同一个 删除
        {
            target=NULL;
            delete bullet;
            bullet=NULL;
        }
        else                                   //不是同一个创建新子弹
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

void Tower1::set_Bullet(int ex,int ey,bool b){


    if(b){
        int px=this->get_Target()->get_X()+this->get_Target()->get_Width()/2;//敌人中心点坐标
        int py=this->get_Target()->get_Y()+this->get_Target()->get_Height()/2;
        double dis=sqrt((ex-px)*(ex-px)+(ey-py)*(ey-py));
        ebuspeed=dis/bulletspeed;                                          //根据当前距离计算子弹移动的速度

        set_isbulleting(true);    //实现动画效果
        this->set_WH(this->get_Width(),this->get_Height()+5);
        bullet = new Bullet(ex,ey,bulletId,target);
    }
    else
        bullet=NULL;
}

Tower1::~Tower1()
{
    //qDebug()<<"删除Tower1";
}
