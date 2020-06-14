#include "selection.h"

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

    painter.drawPixmap(box[0].x-25, box[0].y-25 ,50, 50,
            QPixmap(":/pics/imgs/炮塔1.1.png"));
    painter.drawPixmap(box[1].x-25, box[1].y-25 ,50, 50,
            QPixmap(":/pics/imgs/炮塔2.png"));
    painter.drawPixmap(box[2].x-25, box[2].y-25 ,50, 50,
            QPixmap(":/pics/imgs/炮塔3.png"));


}
void Selection::Draw2(QPainter &painter) const{

}
int Selection::checkbox(int x,int y){
    Point p(x,y);
    for(int i=0;i<4;i++){
        if(box[i].is_include(p,25)){
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


