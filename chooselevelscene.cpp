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
    move(posX,posY);//窗口位置
    setFixedSize(SIZEwid,SIZEhei);//窗口大小
    //设置图标
    setWindowIcon(QIcon(":/pics/imgs/怪兽2.png"));
    //设置标题
    setWindowTitle("选择关卡");

    MyPushButton *backButton= new MyPushButton(60,60,":/pics/imgs/草莓.png");
    backButton->setParent(this);
    backButton->move(900,450);
    connect(backButton,&MyPushButton::clicked,[=]{
        //弹起特效
        backButton->zoom1();
        backButton->zoom2();

        QMediaPlayer *button2 = new QMediaPlayer;
        button2->setMedia(QUrl("qrc:/sound/sound/Button3.mp3"));
        button2->setVolume(50);
        button2->play();

        QTimer::singleShot(300,this,[=]{
            emit chooseBack();
        });
    });





    //创建选择关卡按钮
    for(int i=0;i<3;i++){
        MyPushButton *menuButton = new MyPushButton(90,90,":/pics/imgs/芒果.png");
        menuButton->setParent(this);
        menuButton->move(210+i*260,250);

        //监听每个按钮的点击
        connect(menuButton,&MyPushButton::clicked,[=](){
            menuButton->zoom1();
            menuButton->zoom2();

            QMediaPlayer *button1 = new QMediaPlayer;
            button1->setMedia(QUrl("qrc:/sound/sound/Button4.mp3"));
            button1->setVolume(80);
            button1->play();

            QTimer::singleShot(300,this,[=]{ //延时
                //创建游戏场景
                this->hide();//自己隐藏
                emit StopMuisc();
                GameScene = new PlayScene(i+1);
                GameScene->show();

                //监听游戏页面信号
                connect(GameScene,&PlayScene::chooseBacklevel,this,[=](){
                    this->show();
                    emit PlayMuisc();
                    delete GameScene;
                    GameScene=NULL;
                });

            });

        });

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuButton->width()+10,menuButton->height()+10);
        label->setText(QString::number(i+1));
        label->setFont(QFont("Microsoft YaHei",20,75));
        label->move(210+i*260,245);
        //设置lable上的文字对齐方式
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter );//水平居中和垂直居中
        //设置让鼠标进行穿透
        label->setAttribute((Qt::WA_TransparentForMouseEvents));
    }
    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(245,222,197));
    QFont ft1("方正粗黑宋简体");
    ft1.setPixelSize(50);
    ft1.setBold(true);

    QLabel *label = new QLabel;
    label->setParent(this);
    label->setFixedSize(400,180);
    label->setText(QString("选择关卡:"));
    label->setFont(ft1);
    label->move(130,60);
    label->setPalette(pa);

}
void ChooseLevelScene::paintEvent(QPaintEvent *)
{


    QPainter painter(this);     //创建画家类
    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿

    painter.drawPixmap(0, 0, imgSIZE*per_WIDTH, imgSIZE*per_HEIGHT,
        QPixmap(":/pics/imgs/选择关卡背景.jpg"));

    for(int i=0;i<3;i++){
        painter.drawPixmap(220+i*253, 200, 180, 180,
            QPixmap(":/pics/imgs/小熊.png"));
        }


//    DrawMapArr(painter);        //画出地图
//    DrawTowerpos(painter);
//    DrawTower(painter);
//    DrawEnemy(painter);
//    DrawBullet(painter);

}
