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
    int range=60;
    int pattern;
public:
    int checkbox(int x,int y);
    void Draw1(QPainter &painter) const;
    void Draw2(QPainter &painter,BaseTower *) const;
    bool get_isshow()const;
    void set_isshow(bool b);
    void set_pattern(int );
    int  get_pattern()const;
};

#endif // SELECTION_H
