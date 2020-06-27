#include "flowerbullet.h"

flowerBullet::flowerBullet(int x,int y,int id,Enemy *e):Bullet(x,y,id,e)
{

}
void flowerBullet::Move(double d){   //太阳花子弹移动
    position_x-=d;
    position_y-=d;
    set_WH(get_Width()+2*d,get_Height()+2*d);
}
