#include "selection.h"
#include"mainwindow.h"
#include<QPixmap>
Selection::Selection(int x,int y)
{
     mx=x;
     my=y;
     isshow=false;
     box.push_back(Point(x-range,y));
     box.push_back(Point(x,y-range));
     box.push_back(Point(x+range,y));
     box.push_back(Point(x,y+range));

}
void Selection::Draw1(QPainter &painter,int money) const{

    painter.setPen(QPen(QColor(0, 160, 230), 5));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(mx, my-5), range, range);

    QPixmap p[3];

    if(money>=price1)
        p[0].load(":/pics/imgs/炮塔1可买.png");
    else
        p[0].load(":/pics/imgs/炮塔1不可买.png");
    if(money>=price2)
    {
        p[1].load(":/pics/imgs/炮塔2可买.png");
        p[2].load(":/pics/imgs/炮塔3可买.png");
    }
    else
    {
        p[1].load(":/pics/imgs/炮塔2不可买.png");
        p[2].load(":/pics/imgs/炮塔3不可买.png");
    }
    for(int i=0;i<3;i++)
    {
        painter.drawPixmap(box[i].x-imgSIZE, box[i].y-imgSIZE ,2*imgSIZE,2*imgSIZE,p[i]);
    }

}
void Selection::Draw2(QPainter &painter,BaseTower *tower,int money) const{
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(mx, my), tower->get_Range(), tower->get_Range());//画出攻击范围

    //在上下显示升级或删去防御塔
    QPixmap p1,p2;
    if(tower->get_TowerLevel()==3)
        p1.load(":/pics/imgs/顶级.png");
    else if(tower->get_UpgradePrice()<=money){
        p1.load(tower->get_upPath());
    }
    else {
        p1.load(tower->get_NoupPath());
    }

    p2.load(tower->get_sellPath());

    painter.drawPixmap(box[1].x-imgSIZE, box[1].y-imgSIZE ,2*imgSIZE,2*imgSIZE,p1);

    painter.drawPixmap(box[3].x-imgSIZE, box[3].y-imgSIZE ,2*imgSIZE,2*imgSIZE,p2);

}
int Selection::checkbox(int x,int y){
    Point p(x,y);
    for(int i=0;i<4;i++){
        if(box[i].is_include(p,20)){
             return i+1;
        }
    }
    return 0;
}
bool Selection::get_isshow()const{
    return isshow;
}
void Selection::set_isshow(bool b)
{
    isshow=b;
}

void Selection::set_pattern(int n){
    pattern=n;
}
int  Selection::get_pattern()const{
    return pattern;
}


