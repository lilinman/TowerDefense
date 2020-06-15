#include "selection.h"
#include"mainwindow.h"
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
void Selection::Draw1(QPainter &painter) const{

    painter.setPen(QPen(QColor(0, 160, 230), 5));
    painter.drawEllipse(QPointF(mx, my), range, range);

    painter.drawPixmap(box[0].x-imgSIZE, box[0].y-imgSIZE ,2*imgSIZE,2*imgSIZE,
            QPixmap(":/pics/imgs/炮塔1待买.png"));

    painter.drawPixmap(box[1].x-imgSIZE, box[1].y-imgSIZE ,2*imgSIZE,2*imgSIZE,
            QPixmap(":/pics/imgs/炮塔2待买.png"));

    painter.drawPixmap(box[2].x-imgSIZE, box[2].y-imgSIZE ,2*imgSIZE,2*imgSIZE,
            QPixmap(":/pics/imgs/炮塔3待买.png"));


}
void Selection::Draw2(QPainter &painter,BaseTower *tower) const{
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    painter.drawEllipse(QPointF(mx, my), tower->get_Range(), tower->get_Range());//画出攻击范围

    //在上下显示升级或删去防御塔
    painter.drawPixmap(box[1].x-imgSIZE, box[1].y-imgSIZE ,2*imgSIZE,2*imgSIZE,
            QPixmap(tower->get_Imgpath()));

    painter.drawPixmap(box[3].x-imgSIZE, box[3].y-imgSIZE ,2*imgSIZE,2*imgSIZE,
            QPixmap(tower->get_Imgpath()));

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


