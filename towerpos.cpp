#include "towerpos.h"
#include"mainwindow.h"
TowerPos:: TowerPos(Point p):Object(p.x,p.y),selectbox(new Selection(get_Cpoint().x+8,get_Cpoint().y+5))
{
      set_WH(2*imgSIZE,2*imgSIZE);
      set_Imgpath(":/pics/imgs/地砖3.png");
      HasTower=false;
      myTower=NULL;

}
void TowerPos::Draw(QPainter &painter) const{
    painter.drawPixmap(position_x, position_y, width, height,
        QPixmap(ImgPath));

    if(selectbox->get_isshow()){
        if(selectbox->get_pattern()==1)
            selectbox->Draw1(painter);
        else if(selectbox->get_pattern()==2)
        {
            selectbox->Draw2(painter,this->myTower);}
    }
}
Selection* TowerPos::get_selectbox()const{
    return selectbox;
}
Point TowerPos::get_Cpoint()const{

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
int TowerPos::get_X() const{
    return position_x;
}
int TowerPos::get_Y() const{
    return position_y;
}
