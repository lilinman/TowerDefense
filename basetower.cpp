#include "basetower.h"
#include"enemy.h"
#include"mainwindow.h"
#include<QDebug>
//构造函数
BaseTower::BaseTower(int x,int y): Object(x,y){

}

void BaseTower::Draw(QPainter& painter)const{

    painter.drawPixmap(position_x, position_y, width, height,
                       QPixmap(ImgPath));
//    if(target!=NULL)
//        painter.drawRect(target->get_X(),target->get_Y(),100,100);
}

int BaseTower::get_TowerLevel() const{
    return TowerLevel;
}
int BaseTower::get_Hp()const{
    return Hp;
}

void BaseTower::set_Hp(int n){
    Hp=n;
}

void BaseTower::set_TowerLevel(int n){
    TowerLevel=n;
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

int BaseTower::get_BulletID()const{
    return bulletId;
}
void BaseTower::set_BulletID(int n){
    bulletId=n;
}
BaseTower::~BaseTower(){
     //qDebug()<<"删除BaseTower";
}
