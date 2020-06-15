#include "playscene.h"
#include "mainwindow.h"
#include<QDebug>
PlayScene::PlayScene(int level)
{
    Level=level;
    //配置
    move(posX,posY);//窗口位置
    setFixedSize(SIZEwid,SIZEhei);//窗口大小
    //设置图标
    setWindowIcon(QIcon(":/pics/imgs/怪兽2.png"));
    //设置标题
    setWindowTitle("游戏页面");

    timerId1 = startTimer(120);
    timerId2 = startTimer(1800);
    timerId3 = startTimer(50);

    //返回按钮
    MyPushButton *backButton= new MyPushButton(40,40,":/pics/imgs/草莓.png");
    backButton->setParent(this);
    backButton->move(700,20);
    connect(backButton,&MyPushButton::clicked,[=]{
        //弹起特效
        backButton->zoom1();
        backButton->zoom2();
        QTimer::singleShot(200,this,[=]{
            emit chooseBacklevel();
        });
    });

    InitalGame();//初始化游戏

}
void PlayScene::mousePressEvent(QMouseEvent *event){
       //qDebug()<<"执行鼠标点击事件"<<endl;
        int mx=event->x();
        int my=event->y();
        if(CreatTower(mx,my))
            return;
}

void PlayScene::paintEvent(QPaintEvent *)
{

    QPainter painter(this);     //创建画家类
    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿
    DrawMapArr(painter);        //画出地图
    DrawTowerpos(painter);
    DrawTower(painter);
    DrawEnemy(painter);
    DrawBullet(painter);

}

void PlayScene::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);
    int id = e->timerId();
    if (inGame)
    {
        if(id == timerId2)
            CreatEnemyWave();

        if(id == timerId1)
        {
            update_bullet=false;
            Checkenemy();
            CheckTower();
            repaint();
        }
        if(id==timerId3)
        {
            update_bullet=true;
            Tower_creatbullet();
            repaint();
        }

    }

}
