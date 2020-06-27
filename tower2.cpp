#include "tower2.h"

#include"mainwindow.h"
#include<QDebug>
Tower2::Tower2(int x,int y):BaseTower(x,y)
{
    price =180;
    upgradePrice=280;
    sellPrice=144;
    double rate=1.8;
    TowerLevel=1;
    bulletspeed=10;
    bulletId=21;
    cutSpeed=3;
    tarNum=1;
    damege=8;
    range=130;
    set_WH(rate*imgSIZE,rate*imgSIZE);
    set_Imgpath(":/pics/imgs/炮塔2.1.png");
    upgradePath=":/pics/imgs/炮塔2.1可升级.png";
    NOupgradePath=":/pics/imgs/炮塔2.1不可升级.png";
    sellPath=":/pics/imgs/炮塔2.1拆塔.png";

}
void Tower2::bulletingSound(){

    player->setMedia(QUrl("qrc:/sound/sound/Bullet2.mp3"));
    player->setVolume(35);
    player->play();
}
void Tower2::upGrade()
{
    if(TowerLevel==3) //顶级退出
        return;

    switch (TowerLevel) {
    case 1:
        upgradePrice=360;
        sellPrice=368;
        bulletspeed=9;
        damege=12;
        cutSpeed=5;
        tarNum=2;
        range=150;
        set_Imgpath(":/pics/imgs/炮塔2.2.png");
        upgradePath=":/pics/imgs/炮塔2.2可升级.png";
        NOupgradePath=":/pics/imgs/炮塔2.2不可升级.png";
        sellPath=":/pics/imgs/炮塔2.2拆塔.png";
        TowerLevel++;
        break;
    case 2:
        upgradePrice=0;
        sellPrice=656;
        bulletspeed=7;
        damege=15;
        cutSpeed=7;
        tarNum=3;
        range=180;
        sellPath=":/pics/imgs/炮塔2.3拆塔.png";
        set_Imgpath(":/pics/imgs/炮塔2.3.png");
        TowerLevel++;
    default:
        break;

    }

}
void Tower2::attack(vector<Enemy *> EnemyVec){

    int ex=get_X()+get_Width()/2;//防御塔中心点坐标
    int ey=get_Y()+get_Height()/2;

    if(bullet==NULL)
    {
        for(auto e:EnemyVec)//实现周边敌人减速功能
        {
            int px=e->get_X()+e->get_Width()/2;//敌人中心点坐标
            int py=e->get_Y()+e->get_Height()/2;
            if((ex-px)*(ex-px)+(ey-py)*(ey-py)>range*range)//在范围内 减速NUM个
            {

                e->set_espeed(e->get_Speed());//在范围外恢复正常速度
            }
        }
        return;
    }

    bullet->Move(ebuspeed);

    if(bullet->shoot()||bullet->get_target()->get_Hp()<=0)//如果目标敌人已经没有血也更新
    {
        bullet->get_target()->set_Hp(bullet->get_target()->get_Hp()-this->damege);//如果击中减少敌人血量
        bullet->get_target()->set_isAttacked(true);//设置敌人被攻击
        int num=0;

        for(auto e:EnemyVec)//实现周边敌人减速功能
        {
            int px=e->get_X()+e->get_Width()/2;//敌人中心点坐标
            int py=e->get_Y()+e->get_Height()/2;
            if((ex-px)*(ex-px)+(ey-py)*(ey-py)<range*range)//在范围内 减速NUM个
            {
                 num++;
                 if(e->get_espeed()!=e->get_Speed())  //如果已经被减速过
                     e->set_espeed(e->get_Speed()-cutSpeed-1);    //创造叠加效果 最多再减2
                 if(e->get_espeed()==e->get_Speed()-cutSpeed-1)
                      e->set_espeed(e->get_Speed()-cutSpeed-2);
                 else
                     e->set_espeed(e->get_Speed()-cutSpeed);   //第一次减速
            }
            else
                e->set_espeed(e->get_Speed());//在范围恢复正常速度
            if(num==tarNum) break;             //已经到目标敌人数量
        }

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

void Tower2::set_Bullet(int ex,int ey,bool b){


    if(b){
        int px=this->get_Target()->get_X()+this->get_Target()->get_Width()/2;//敌人中心点坐标
        int py=this->get_Target()->get_Y()+this->get_Target()->get_Height()/2;
        double dis=sqrt((ex-px)*(ex-px)+(ey-py)*(ey-py));
        ebuspeed=dis/bulletspeed;                             //设置子弹移动速度

        set_isbulleting(true);
        this->set_WH(this->get_Width(),this->get_Height()+5);
        bullet = new Bullet(ex,ey,bulletId,target);
    }
    else
        bullet=NULL;
}

Tower2::~Tower2()
{
    //qDebug()<<"删除Tower2";
}
