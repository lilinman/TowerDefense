#include "object.h"
#include<QDebug>
Object::Object(int x, int y): position_x(x),position_y(y){}

int Object::get_Height() const{
    return height;
}
int Object::get_Width() const {
    return width;
}
int Object::get_X()const {
    return position_x;
}
int Object::get_Y()const {
    return position_y;
}
QString Object::get_Imgpath()const {
    return ImgPath;
}
void Object::set_WH(int a,int b){
    height=b,width=a;
}
void Object::set_Imgpath(QString s){
    ImgPath=s;
}

Object::~Object(){
   //qDebug()<<"删除object";
}
