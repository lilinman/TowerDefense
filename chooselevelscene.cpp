#include "chooselevelscene.h"
#include"mainwindow.h"
#include<QMenuBar>
#include<mypushbutton.h>
#include <QMouseEvent>  //鼠标事件
#include<QLabel>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡信息
    //配置主场景
    move(400,120);//窗口位置
    setFixedSize(SIZEwid,SIZEhei);//窗口大小
    //设置图标
    setWindowIcon(QIcon(":/pics/imgs/怪兽2.png"));
    //设置标题
    setWindowTitle("选择关卡");

    QMenuBar *bar=menuBar();
    QMenu *startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    MyPushButton *backButton= new MyPushButton(80,80,":/pics/imgs/草莓.png");
    backButton->setParent(this);
    backButton->move(800,400);
    connect(backButton,&MyPushButton::clicked,[=]{
        //弹起特效
        backButton->zoom1();
        backButton->zoom2();
        QTimer::singleShot(300,this,[=]{
            emit chooseBack();
        });
    });

    //创建选择关卡按钮
    for(int i=0;i<3;i++){
        MyPushButton *menuButton = new MyPushButton(90,90,":/pics/imgs/芒果.png");
        menuButton->setParent(this);
        menuButton->move(200+i*180,200);

        //监听每个按钮的点击
        connect(menuButton,&MyPushButton::clicked,[=](){
            menuButton->zoom1();
            menuButton->zoom2();
            QTimer::singleShot(300,this,[=]{ //延时

                //创建游戏场景
                this->hide();//自己隐藏
                GameScene = new PlayScene(i+1);
                GameScene->show();

                //监听游戏页面信号
                connect(GameScene,&PlayScene::chooseBacklevel,this,[=](){
                    this->show();
                    GameScene->close();
                });

            });

        });

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuButton->width()+10,menuButton->height()+10);
        label->setText(QString::number(i+1));
        label->setFont(QFont("Microsoft YaHei",20,75));
        label->move(200+i*180,200);
        //设置lable上的文字对齐方式
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter );//水平居中和垂直居中
        //设置让鼠标进行穿透
        label->setAttribute((Qt::WA_TransparentForMouseEvents));
    }



}
void ChooseLevelScene::paintEvent(QPaintEvent *)
{


    QPainter painter(this);     //创建画家类
    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿

    painter.drawPixmap(0, 0, imgSIZE*per_WIDTH, imgSIZE*per_HEIGHT,
        QPixmap(":/pics/imgs/背景.png"));


//    DrawMapArr(painter);        //画出地图
//    DrawTowerpos(painter);
//    DrawTower(painter);
//    DrawEnemy(painter);
//    DrawBullet(painter);

}
