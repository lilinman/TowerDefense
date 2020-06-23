#include "flowerbullet.h"

flowerBullet::flowerBullet(int x,int y,int id,Enemy *e):Bullet(x,y,id,e)
{

}
void flowerBullet::Move(double d){
    position_x-=d;
    position_y-=d;
    set_WH(get_Width()+2*d,get_Height()+2*d);
}
