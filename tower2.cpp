#include "tower2.h"

#include"mainwindow.h"
#include<QDebug>
Tower2::Tower2(int x,int y):BaseTower(x,y)
{
    double rate=1.8;
    TowerLevel=1;
    bulletspeed=10;
    bulletId=21;
    cutSpeed=3;
    tarNum=1;
    damege=5;
    range=100;
    set_WH(rate*imgSIZE,rate*imgSIZE);
    set_Imgpath(":/pics/imgs/炮塔2.1.png");

}

void Tower2::upGrade()
{
    if(TowerLevel==3) //顶级退出
        return;

    switch (TowerLevel) {
    case 1:
        bulletspeed=9;
        damege=7;
        cutSpeed=5;
        tarNum=2;
        range=150;
        set_Imgpath(":/pics/imgs/炮塔2.2.png");
        TowerLevel++;
        break;
    case 2:
        bulletspeed=7;
        damege=10;
        cutSpeed=7;
        tarNum=3;
        range=200;
        set_Imgpath(":/pics/imgs/炮塔2.3.png");
        TowerLevel++;
    default:
        break;

    }

}
void Tower2::attack(vector<Enemy *> EnemyVec){

    int ex=get_X()+get_Width()/2;//防御塔中心点坐标
    int ey=get_Y()+get_Height()/2;

    if(bullet->get_target()==NULL)
        return;
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
