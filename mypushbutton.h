#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //构造函数 参数一 正常显示的图片的路径
    MyPushButton(int,int,QString normalImg);
    //保存图片路径
    QString normalImgPath;
    //弹跳特效
    void zoom1();//向下弹跳
    void zoom2();//向上条
    void setPath( int ,int ,QString);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
