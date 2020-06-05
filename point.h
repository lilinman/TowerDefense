#ifndef POINT_H
#define POINT_H
//坐标
struct Point
{
public:
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
    bool is_include(Point b,int n){    //判断点是否在周围
        if(b.x>x-n&&b.x<x+n&&b.y>y-n&&b.y<y+n)
            return true;
        else
            return false;
    }
};

#endif // POINT_H
