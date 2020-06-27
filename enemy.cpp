#include "enemy.h"
#include<QDebug>
Enemy::Enemy(vector<Point> pointarr,int x, int y, int id) :
    Object(x,y),id(id)

{
    for(auto p:pointarr){
        waypoint.push_back(p);
    }
    //确定不同怪物
    switch (id)
    {
    case 1:
        price=24;
        OriginHp=15;
        hp = 15;
        Speed=10;
        e_speed=10;
        set_WH(70,70);
        set_Imgpath(":/pics/imgs/怪兽2.png");
        break;
    case 2:
        price=24;
        OriginHp=60;
        hp = 50;
        Speed=10;
        e_speed=10;
        set_WH(70,70);
        set_Imgpath(":/pics/imgs/怪兽1.png");
        break;
    case 3:
        price=32;
        OriginHp=70;
        hp = 70;
        Speed=13;
        e_speed=13;    
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪兽3.png");
        break;
    case 4:
        price=54;
        OriginHp=150;
        hp = 150;
        Speed=15;
        e_speed=15;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪兽4.png");
        break;
    case 5:
        price=24;
        OriginHp=30;
        hp = 30;
        Speed=10;
        e_speed=10;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪物1.png");
        break;
    case 6:
        price=38;
        OriginHp=70;
        hp = 70;
        Speed=10;
        e_speed=10;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪物2.png");
        break;
    case 7:
        price=64;
        OriginHp=180;
        hp = 180;
        Speed=15;
        e_speed=15;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪物3.png");
        break;
    case 8:
        price=68;
        OriginHp=180;
        hp = 180;
        Speed=13;
        e_speed=13;
        set_WH(80,80);
        set_Imgpath(":/pics/imgs/怪物4.png");
        break;
    case 9:
        price=98;
        OriginHp=220;
        hp = 220;
        Speed=15;
        e_speed=15;
        set_WH(80,80);
        set_Imgpath(":/pics/imgs/怪物5.png");
        break;
    case 10:
        price=124;
        OriginHp=300;
        hp = 300;
        Speed=15;
        e_speed=15;
        set_WH(100,100);
        set_Imgpath(":/pics/imgs/怪物5.png");
        break;
    case 11:
        price=124;
        OriginHp=90;
        hp = 80;
        Speed=12;
        e_speed=12;
        set_WH(100,100);
        set_Imgpath(":/pics/imgs/怪物4.png");
        break;
    case 12:
        price=124;
        OriginHp=90;
        hp = 90;
        Speed=12;
        e_speed=12;
        set_WH(100,100);
        set_Imgpath(":/pics/imgs/怪兽1.png");
        break;

    default:
        break;
    }
}

void Enemy::Draw(QPainter &painter){

    painter.drawPixmap(position_x, position_y, width, height,
                       QPixmap(ImgPath));
    if(e_speed!=Speed){     //被减速画出冰冻效果
        painter.drawPixmap(position_x, position_y+height*0.4, width, height*0.6,
                           QPixmap(":/pics/imgs/冰冻效果.png"));
    }
    if(isAttacked&&hp>=0)   //如果正在被攻击画出血量条
    {
        painter.setBrush(QColor(255,0,255));
        painter.drawRect(get_X()+8,get_Y()-10,45,5);
        painter.setBrush(QColor(0,255,0));
        painter.drawRect(get_X()+8,get_Y()-10,45*((double)hp/(double)OriginHp),5);
    }
    if(isAttackedBy3)  //在被塔3攻击画出效果
    {
        painter.drawPixmap(position_x, position_y+height*0.6, width, height*0.3,
                           QPixmap(":/pics/imgs/塔3效果.png"));
    }

    //画出消失效果
    if(isdeleted>=1)
    {
        QString str=QString(":/pics/imgs/敌人效果%1.png").arg(this->isdeleted);
        painter.drawPixmap(position_x-70, position_y-65, 200, 200,
                           QPixmap(str));
        isdeleted++;
    }

}
//设定路径点移动
void Enemy::Move()
{

    if(waypoint.empty())
        return ;//走到终点

    if (waypoint[0].y > position_y) //下
    {
        position_y += e_speed;
        if(position_y>waypoint[0].y)      //避免不是正好走到节点的bug
            position_y=waypoint[0].y;
        return ;
    }

    if (waypoint[0].x < position_x) //左
    {
        position_x -= e_speed;
        if(position_x<waypoint[0].x)
            position_x=waypoint[0].x;
        return ;
    }

    if (waypoint[0].x> position_x) //右
    {
        position_x += e_speed;
        if(position_x>waypoint[0].x)
            position_x=waypoint[0].x;
        return ;
    }

    if (waypoint[0].y < position_y) //上
    {
        position_y -= e_speed;
        if(position_y<waypoint[0].y)
            position_y=waypoint[0].y;
        return ;
    }

    if(waypoint[0].y==position_y&&waypoint[0].x==position_x){

        waypoint.erase(waypoint.begin());//到达节点 删除
    }

    return;
}
int  Enemy::get_isdeleted()const{
    return isdeleted;
}
void  Enemy::set_isdeleted(int n){
    isdeleted=n;
}
int Enemy::get_Id() const      //获取编号
{
    return id;
}

int Enemy::get_Hp() const     //获取生命值
{
    return hp;
}

void Enemy::set_Hp(int a){    //设置生命值
    hp=a;
}
int Enemy::get_espeed() const
{
    return e_speed;
}

void Enemy::set_espeed(int a){
    e_speed=a;
}
bool Enemy::get_isAttacked() const
{
    return isAttacked;
}

void Enemy::set_isAttacked(bool a){
    isAttacked=a;
}

bool Enemy::get_isAtBy3() const
{
    return isAttackedBy3;
}

void Enemy::set_isAtBy3(bool a){
    isAttackedBy3=a;
}

int Enemy::get_Speed()const{
    return Speed;
}
int Enemy::get_Ohp()const{
    return OriginHp;
}
int Enemy::get_Price()const{
    return price;
}
void Enemy::set_Ohp(int a){
    OriginHp=a;
}

vector<Point> Enemy::getway() const{
    return waypoint;
}
Enemy::~Enemy(){   //发出叫声
    //qDebug()<<"删除enemy";
    switch (id)
    {
    case 1:
    case 5:
        player->setMedia(QUrl("qrc:/sound/sound/enemy1.mp3"));
        break;
    case 2:
    case 6:
    case 12:
        player->setMedia(QUrl("qrc:/sound/sound/enemy2.mp3"));
        break;
    case 3:
    case 7:
        player->setMedia(QUrl("qrc:/sound/sound/enemy3.mp3"));
        break;
    case 4:
    case 8:
    case 11:
        player->setMedia(QUrl("qrc:/sound/sound/enemy4.mp3"));
        break;
    case 9:
        player->setMedia(QUrl("qrc:/sound/sound/enemy5.mp3"));
        break;
    case 10:
        player->setMedia(QUrl("qrc:/sound/sound/enemy5.mp3"));
        break;
    default:
        break;
    }
    player->setVolume(9);
    player->play();
}
