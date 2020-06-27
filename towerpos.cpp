#include "towerpos.h"
#include"mainwindow.h"
TowerPos:: TowerPos(Point p):Object(p.x,p.y),selectbox(new Selection(get_Cpoint().x+8,get_Cpoint().y+5))
{
      set_WH(2*imgSIZE,2*imgSIZE);
      HasTower=false;
      myTower=NULL;

}
void TowerPos::Draw(QPainter &painter){
     painter.setBrush(Qt::NoBrush);//没什么意义为了不出警告
}

Selection* TowerPos::get_selectbox()const{
    return selectbox;
}
Point TowerPos::get_Cpoint()const{
      //返回中心点
      return Point(position_x+30,position_y+30);
}

bool TowerPos::get_hasTower()const{
       return HasTower;
}
BaseTower* TowerPos::get_myTower()const{
       return myTower;
}
void TowerPos::set_hasTower(bool b){
       HasTower=b;
}
void TowerPos::set_myTower(BaseTower* m){
       myTower=m;
}
