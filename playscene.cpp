#include "playscene.h"
#include "mainwindow.h"
#include<QDebug>
#include<QLabel>
#include<QPalette>
#include<QMediaPlaylist>
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
    timerId2 = startTimer(1200);
    timerId3 = startTimer(50);

    QMediaPlayer *bgm = new QMediaPlayer;
    QMediaPlaylist *gameList = new QMediaPlaylist;//播放列表
    gameList->addMedia(QUrl("qrc:/sound/sound/bgm2.mp3"));
    gameList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgm->setPlaylist(gameList);
    bgm->setVolume(5);

    //返回按钮
    MyPushButton *backButton= new MyPushButton(55,55,":/pics/imgs/返回.png");
    backButton->setParent(this);
    backButton->move(850,2);
    connect(backButton,&MyPushButton::clicked,[=]{
        //弹起特效
        backButton->zoom1();
        backButton->zoom2();
        QMediaPlayer *button2 = new QMediaPlayer;
        button2->setMedia(QUrl("qrc:/sound/sound/Button3.mp3"));
        button2->setVolume(50);
        button2->play();

        bgm->pause();

        QTimer::singleShot(200,this,[=]{
            emit chooseBacklevel();
        });
    });

    MyPushButton *pauseButton= new MyPushButton(55,55,":/pics/imgs/暂停.png");
    pauseButton->setParent(this);
    pauseButton->move(795,2);
    connect(pauseButton,&MyPushButton::clicked,[=]{
        QMediaPlayer *button2 = new QMediaPlayer;
        button2->setMedia(QUrl("qrc:/sound/sound/Button3.mp3"));
        button2->setVolume(50);
        button2->play();

        //切换图片
        if(isPaused){
            pauseButton->setPath(55,55,":/pics/imgs/暂停.png");
            isPaused=false;
        }
        else{
            pauseButton->setPath(55,55,":/pics/imgs/继续.png");
            isPaused=true;
        }
    });

    MyPushButton *doubleButton= new MyPushButton(85,85,":/pics/imgs/一倍速.png");
    doubleButton->setParent(this);
    doubleButton->move(705,-10);
    connect(doubleButton,&MyPushButton::clicked,[=]{

        QMediaPlayer *button2 = new QMediaPlayer;
        button2->setMedia(QUrl("qrc:/sound/sound/Button3.mp3"));
        button2->setVolume(50);
        button2->play();

        //切换图片
        if(isDouble){
            doubleButton->setPath(85,85,":/pics/imgs/一倍速.png");
            isDouble=false;
            timerId1 = startTimer(120);
            timerId2 = startTimer(1200);
            timerId3 = startTimer(50);
        }
        else{
            doubleButton->setPath(85,85,":/pics/imgs/二倍速.png");
            isDouble=true;
            timerId1 = startTimer(120*0.6);
            timerId2 = startTimer(1200*0.6);
            timerId3 = startTimer(50*0.6);
        }
    });

    InitalGame();//初始化游戏

    manegeLable();//初始化标签

    bgm->play();

}
void PlayScene::manegeLable(){
    //金钱标签
    moneylable->setText(QString::number(this->money));
    moneylable->setGeometry(260,5,200,50);
    QFont ft("Verdana");
    ft.setPixelSize(25);
    ft.setBold(true);
    moneylable->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(245,222,197));
    moneylable->setPalette(pa);

    QPalette pa1;
    pa1.setColor(QPalette::WindowText,QColor(205,102,29));

    //敌人波数标签
    QString str1=QString(" %1 / %2 波怪物").arg(this->wave).arg(this->totalwave);
    wavelable->setText(str1);
    QFont ft1("方正粗黑宋简体");
    ft1.setPixelSize(25);
    ft1.setBold(true);
    wavelable->setGeometry(SIZEwid/2-80,0,250,70);
    wavelable->setFont(ft1);
    wavelable->setPalette(pa1);

    //玩家生命值标签
    playerlable->setText(QString::number(this->playerhp));
    playerlable->setGeometry(376,5,50,50);
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
    DrawTower(painter);
    DrawSelectionbox(painter);
    DrawBullet(painter);


}

void PlayScene::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);
    int id = e->timerId();

    if (inGame&&(!isPaused))
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
