#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>     //画家
#include <QMouseEvent>  //鼠标事件
#include <Qtimer>       //定时器
#include <QLabel>
#include<vector>
#include<QString>
#include<iostream>
using namespace std;
#include"enemy.h"
#include"basetower.h"
#include"towerpos.h"
#include "mypushbutton.h"
#include"chooselevelscene.h"
const int positionSIZE=10;
const int imgSIZE=30; //图片缩放比例
const int per_WIDTH=35;//35*30画面宽
const int per_HEIGHT=20;//20*30画面高
const int SIZEwid=imgSIZE*per_WIDTH;
const int SIZEhei=per_HEIGHT*imgSIZE;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:

    void paintEvent(QPaintEvent *);

public:
    ChooseLevelScene *ChooseScene = NULL;//设置选择场景指针
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
