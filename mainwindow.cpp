#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerId1 = startTimer(120);
    timerId2 = startTimer(1800);
    timerId3 = startTimer(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
        int mx=event->x();
        int my=event->y();
        if(CreatTower(mx,my))
            return;
}

void MainWindow::paintEvent(QPaintEvent *)
{

    move(400,120);//窗口位置
    setFixedSize(SIZEwid,SIZEhei);//窗口大小
    QPainter painter(this);     //创建画家类
    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿
    DrawMapArr(painter);        //画出地图
    DrawTower(painter);
    DrawEnemy(painter);

}

void MainWindow::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);
    int id = e->timerId();
    if (inGame)
    {

        if(id == timerId2)
            CreatEnemyWave();

        if(id == timerId1)
        {
            //upd_bullet=false;
            repaint();
        }

    }

}
