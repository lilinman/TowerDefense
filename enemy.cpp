#include "enemy.h"

Enemy::Enemy(Point pointarr[],int len,int x, int y, int id) :
    Object(x,y),id(id)

{
    for(int i = 0; i < len; i++)     //路径数组
        waypoint.push_back(pointarr[i]);

    //确定不同怪物
    switch (id)
    {
    case 1: //1红色小怪物
        hp = 50;
        set_WH(70,70);
        set_Imgpath(":/pics/imgs/1红色小怪物.png");
        break;
    case 2: //2粉色小怪物
        hp = 120;
        set_WH(85,100);
        set_Imgpath(":/pics/imgs/2粉色小怪物.png");
        break;
    case 3: //3蓝色小怪物
        hp = 650;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/3蓝色小怪物.png");
        break;
    case 4://4绿色小怪物
        hp = 310;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/4绿色小怪物.png");
        break;
    case 5: //5黄色小怪物
        hp = 200;
        set_WH(64,64);
        set_Imgpath(":/pics/imgs/5黄色小怪物.png");
        break;
    default:
        break;
    }
}

void Enemy::Draw(QPainter& painter) const{
    painter.drawPixmap(position_x, position_y, width, height,
        QPixmap(ImgPath));

}
//设定路径点移动
bool Enemy::Move()
{

    if(waypoint.empty())
        return true;//走到终点 删除

    if (waypoint[0].y > position_y) //下
    {
         position_y += e_speed;
        return false;
    }

    if (waypoint[0].x < position_x) //左
    {
         position_x -= e_speed;
        return false;
    }

    if (waypoint[0].x> position_x) //右
    {
         position_x += e_speed;
        return false;
    }

    if (waypoint[0].y < position_y) //上
    {
         position_y -= e_speed;
        return false;
    }

    if(waypoint[0].y==position_y&&waypoint[0].x==position_x){
 
        waypoint.erase(waypoint.begin());//到达节点 删除
    }

    return false;
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
