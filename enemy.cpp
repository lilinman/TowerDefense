#include "enemy.h"
#include<QDebug>
Enemy::Enemy(Point pointarr[],int len,int x, int y, int id) :
    Object(x,y),id(id)

{
    for(int i = 0; i < len; i++)     //路径数组
        waypoint.push_back(pointarr[i]);

    //确定不同怪物
    switch (id)
    {
    case 1:
        OriginHp=20;
        Speed=10;
        e_speed=10;
        hp = 20;
        set_WH(70,70);
        set_Imgpath(":/pics/imgs/怪兽2.png");
        break;
    case 2:
        OriginHp=80;
        hp = 80;
        Speed=10;
        e_speed=10;
        set_WH(70,70);
        set_Imgpath(":/pics/imgs/怪兽1.png");
        break;
    case 3:
        OriginHp=200;
        Speed=15;
        e_speed=15;
        hp = 200;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪兽3.png");
        break;
    case 4:
        OriginHp=300;
        hp = 300;
        Speed=10;
        e_speed=10;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪兽4.png");
        break;
    default:
        break;
    }
}

void Enemy::Draw(QPainter &painter){
    painter.drawPixmap(position_x, position_y, width, height,
                       QPixmap(ImgPath));
    if(e_speed!=Speed){
        painter.drawPixmap(position_x, position_y+height*0.4, width, height*0.6,
                           QPixmap(":/pics/imgs/冰冻效果.png"));
    }
    if(isAttacked)   //如果正在被攻击画出血量条
    {
        painter.setBrush(QColor(255,0,255));
        painter.drawRect(get_X(),get_Y()-10,50,6);
        painter.setBrush(QColor(0,255,0));
        painter.drawRect(get_X(),get_Y()-10,50.0*((double)hp/(double)OriginHp),6);
    }
    if(isAttackedBy3)  //在被塔3攻击画出效果
    {
        painter.drawPixmap(position_x, position_y+height*0.6, width, height*0.3,
                           QPixmap(":/pics/imgs/塔3效果.png"));
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
        if(position_y>waypoint[0].y)
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
void Enemy::set_Ohp(int a){
    OriginHp=a;
}

vector<Point> Enemy::getway() const{
    return waypoint;
}
Enemy::~Enemy(){
    //qDebug()<<"删除enemy";
}
