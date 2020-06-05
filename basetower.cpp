#include "basetower.h"

BaseTower::BaseTower(int x,int y,int id):
    Object(x,y),id(id){
    switch (id) {
    case 1://绿瓶
        damege=10;
        range=200;
        t_speed=5;
        set_WH(60,70);
        set_Imgpath(":/pics/imgs/绿瓶1.png");
        break;
    }
}
void BaseTower::Draw(QPainter& painter){

    painter.drawPixmap(position_x, position_y, width, height,
                       QPixmap(ImgPath));
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
Bullet* BaseTower::get_bullet()const{
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
void BaseTower::del_Bullet(){
    delete bullet;
    bullet=NULL;
}
