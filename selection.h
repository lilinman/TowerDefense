#ifndef SELECTION_H
#define SELECTION_H
#include<QPainter>
#include "point.h"
#include<vector>
#include"basetower.h"
using namespace std;
class Selection
{
public:
    Selection(int,int);
private:
    int  mx,my;
    bool isshow;      //是否显示
    vector<Point> box;//四个点的位置
    int range=65;     //大小
    int pattern;      //模式1，2
    int price1=100;   //防御塔1的原价
    int price2=180;   //防御塔2和3原价
public:
    int checkbox(int x,int y);                                //判断点击返回结果
    void Draw1(QPainter &painter,int money) const;            //画模式1
    void Draw2(QPainter &painter,BaseTower *,int money) const;//画模式2
    bool get_isshow()const;
    void set_isshow(bool b);
    void set_pattern(int );
    int  get_pattern()const;
};

#endif // SELECTION_H
