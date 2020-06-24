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
    bool isshow;
    vector<Point> box;//移动路径
    int range=65;
    int pattern;
    int price1=100;
    int price2=180;
    int price3=180;
public:
    int checkbox(int x,int y);
    void Draw1(QPainter &painter,int money) const;
    void Draw2(QPainter &painter,BaseTower *,int money) const;
    bool get_isshow()const;
    void set_isshow(bool b);
    void set_pattern(int );
    int  get_pattern()const;
};

#endif // SELECTION_H
