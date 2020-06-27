#include "basetower.h"
#include"enemy.h"
#include"mainwindow.h"
#include<QDebug>
//防御塔抽象类
BaseTower::BaseTower(int x,int y): Object(x,y){

}

void BaseTower::Draw(QPainter& painter){

    if(isbulleting){                                               //实现发射子弹时动画效果
        painter.drawPixmap(position_x, position_y-5, width, height,
                           QPixmap(ImgPath));
        this->set_WH(this->get_Width(),this->get_Height()-5);
        isbulleting=false;
        bulletingSound();                                          //播放发射子弹音频
    }

    else{
        painter.drawPixmap(position_x, position_y, width, height,
                           QPixmap(ImgPath));
    }
    //画出消失效果
    if(isdeleted>=1)
    {
        QString str=QString(":/pics/imgs/塔效果%1.png").arg(this->isdeleted);
        painter.drawPixmap(position_x-85, position_y-90, 250, 250,
                           QPixmap(str));
        isdeleted++;
    }
}
int BaseTower::get_isdeleted()const{
    return isdeleted;
}
void BaseTower::set_isdeleted(int n){
    isdeleted=n;
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

Bullet* BaseTower::get_Bullet()const{
    return bullet;
}

int BaseTower::get_BulletID()const{
    return bulletId;
}
void BaseTower::set_BulletID(int n){
    bulletId=n;
}
void BaseTower::set_isbulleting(bool b){
    isbulleting=b;
}
bool BaseTower::get_isbulleting()const{
    return isbulleting;
}
int BaseTower::get_SellPrice()const{
    return sellPrice;
}
int BaseTower::get_UpgradePrice()const{
    return upgradePrice;
}
QString BaseTower::get_upPath() const{
    return upgradePath;
}
QString BaseTower::get_NoupPath() const{
    return NOupgradePath;
}
QString BaseTower::get_sellPath() const{
    return sellPath;
}
int BaseTower::get_Price()const{
    return price;
}
bool BaseTower::get_ShowUpgrade()const{
    return showUpgrade;
}
void BaseTower::set_ShowUpgrade(bool b){
    showUpgrade=b;
}
BaseTower::~BaseTower(){
    //qDebug()<<"删除BaseTower";
}
