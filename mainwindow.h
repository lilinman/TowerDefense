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
#include <QMediaPlayer>
using namespace std;
#include"enemy.h"
#include"basetower.h"
#include"towerpos.h"
#include "mypushbutton.h"
#include"chooselevelscene.h"
const int positionSIZE=10;
const int posX=400;
const int posY=150;
const int imgSIZE=40; //图片缩放比例
const int per_WIDTH=28;//30*30画面宽
const int per_HEIGHT=18;//20*30画面高
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
