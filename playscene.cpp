#include "playscene.h"
#include "mainwindow.h"
#include<QDebug>
#include<QLabel>
#include<QPalette>
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
    timerId2 = startTimer(1500);
    timerId3 = startTimer(50);

    QMediaPlayer *bgm = new QMediaPlayer;
    bgm->setMedia(QUrl("qrc:/sound/sound/bgm2.mp3"));
    bgm->setVolume(5);

    //返回按钮
    MyPushButton *backButton= new MyPushButton(40,40,":/pics/imgs/草莓.png");
    backButton->setParent(this);
    backButton->move(700,20);
    connect(backButton,&MyPushButton::clicked,[=]{
        //弹起特效
        backButton->zoom1();
        backButton->zoom2();

        bgm->pause();
        QTimer::singleShot(200,this,[=]{
            emit chooseBacklevel();
        });
    });

    InitalGame();//初始化游戏

    manegeLable();//初始化标签

    bgm->play();

}
void PlayScene::manegeLable(){
    //金钱标签
    moneylable->setText(QString::number(this->money));
    moneylable->setGeometry(150,15,200,50);
    QFont ft("Microsoft YaHei");
    ft.setPixelSize(25);
    ft.setBold(true);
    moneylable->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::yellow);
    moneylable->setPalette(pa);

    //敌人波数标签
    QString str1=QString("第 %1 / %2 波怪物").arg(this->wave).arg(this->totalwave);
    wavelable->setText(str1);
    QFont ft1("Microsoft YaHei");
    ft1.setPixelSize(20);
    ft1.setBold(true);
    wavelable->setGeometry(SIZEwid/2-100,15,250,50);
    wavelable->setFont(ft1);
    wavelable->setPalette(pa);

    //玩家生命值标签
    playerlable->setText(QString::number(this->playerhp));
    playerlable->setGeometry(SIZEwid-90,15,50,50);
    playerlable->setFont(ft);
    playerlable->setPalette(pa);

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
    DrawEnemy(painter);
    DrawTowerpos(painter);
    DrawTower(painter);
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
