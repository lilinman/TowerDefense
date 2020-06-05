#ifndef OBJECT_H
#define OBJECT_H

#include<QString>
class Object{

protected:
    int position_x,position_y;//位置坐标
    int width,height;    //大小尺寸
    QString ImgPath;     //图片路径
public:
    Object(int x,int y);
    int get_X() const;
    int get_Y() const;
    int get_Width() const;
    int get_Height() const;
    QString get_Imgpath() const;
    void set_Imgpath(QString s) ;
    void set_WH(int a,int b);

};

#endif // OBJECT_H
