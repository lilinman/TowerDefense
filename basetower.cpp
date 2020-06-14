#include "basetower.h"
#include"enemy.h"
BaseTower::BaseTower(int x,int y,int id):
    Object(x,y),id(id){
    switch (id) {
    case 1:
        bulletId=11;
        damege=10;
        range=150;
        t_speed=5;
        set_WH(30,30);
        set_Imgpath(":/pics/imgs/炮塔1.1.png");
        break;
    case 2:
        bulletId = 21;
        damege=10;
        range=200;
        t_speed=5;
        set_WH(60,60);
        set_Imgpath(":/pics/imgs/炮塔2.png");
        break;
    case 3:
        bulletId = 31;
        damege=10;
        range=150;
        t_speed=5;
        set_WH(60,60);
        set_Imgpath(":/pics/imgs/炮塔3.png");
        break;

    }
}
void BaseTower::Draw(QPainter& painter){

    painter.drawPixmap(position_x, position_y, width, height,
                       QPixmap(ImgPath));
    if(target!=NULL)
        painter.drawRect(target->get_X(),target->get_Y(),100,100);
}

void  BaseTower::attack(){
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

void BaseTower::set_Target(Enemy *t){
    target=t;
}

Enemy *BaseTower::get_Target() const{
    return target;
}

int BaseTower::get_Damege() const{
    return damege;
}
void BaseTower::set_Damege(int d) {
    damege=d;
}
int BaseTower::get_Range() const{
    return range;
}
void BaseTower::set_Range(int r){
    range=r;
}
int BaseTower::get_speed()const{
    return t_speed;
}
Bullet* BaseTower::get_Bullet()const{
    return bullet;
}
void BaseTower::set_Bullet(Bullet *b){
    bullet=b;
}
int BaseTower::get_BulletID()const{
    return bulletId;
}
void BaseTower::set_BulletID(int n){
    bulletId=n;
}
