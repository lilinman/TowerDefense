#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //构造函数 参数一 正常显示的图片的路径 参数2 按下之后的图片路径
    MyPushButton(int,int,QString normalImg,QString pressImg = " ");
    //保存图片路径
    QString normalImgPath;
    QString pressImgPath;
    //弹跳特效
    void zoom1();//向下弹跳
    void zoom2();//向上条

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
