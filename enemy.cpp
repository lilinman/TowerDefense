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
        hp = 50;
        set_WH(70,70);
        set_Imgpath(":/pics/imgs/怪兽2.png");
        break;
    case 2:
        hp = 120;
        set_WH(70,70);
        set_Imgpath(":/pics/imgs/怪兽1.png");
        break;
    case 3:
        hp = 650;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪兽3.png");
        break;
    case 4:
        hp = 310;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/怪兽4.png");
        break;
    default:
        break;
    }
}

void Enemy::Draw(QPainter &painter) const{
    painter.drawPixmap(position_x, position_y, width, height,
        QPixmap(ImgPath));
}
//设定路径点移动
void Enemy::Move()
{

    if(waypoint.empty())
        return ;//走到终点

    if (waypoint[0].y > position_y) //下
    {
         position_y += e_speed;
        return ;
    }

    if (waypoint[0].x < position_x) //左
    {
         position_x -= e_speed;
        return ;
    }

    if (waypoint[0].x> position_x) //右
    {
         position_x += e_speed;
        return ;
    }

    if (waypoint[0].y < position_y) //上
    {
         position_y -= e_speed;
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
vector<Point> Enemy::getway() const{
    return waypoint;
}
Enemy::~Enemy(){
     //qDebug()<<"删除enemy";
}
