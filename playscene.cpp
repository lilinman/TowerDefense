#include "playscene.h"
#include "mainwindow.h"
#include<QDebug>
#include<QLabel>
#include<QPalette>
#include<QPropertyAnimation>
PlayScene::PlayScene(int level)
{
    Level=level;
    //配置
    move(posX,posY);//窗口位置
    setFixedSize(SIZEwid,SIZEhei);//窗口大小
    //设置图标
    setWindowIcon(QIcon(":/pics/imgs/怪兽2.png"));
    //计时器
    timerId1 = startTimer(120);
    timerId2 = startTimer(1200);
    timerId3 = startTimer(50);


    gameList->addMedia(QUrl("qrc:/sound/sound/bgm2.mp3"));
    gameList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgm->setPlaylist(gameList);
    bgm->setVolume(15);

    //返回按钮
    MyPushButton *backButton= new MyPushButton(55,55,":/pics/imgs/返回.png");
    backButton->setParent(this);
    backButton->move(850,2);
    connect(backButton,&MyPushButton::clicked,[=]{
        //弹起特效
        backButton->zoom1();
        backButton->zoom2();

        button->setMedia(QUrl("qrc:/sound/sound/Button3.mp3"));
        button->setVolume(60);
        button->play();

        bgm->pause();

        QTimer::singleShot(200,this,[=]{
            emit chooseBacklevel();
        });
    });

    //暂停按钮
    MyPushButton *pauseButton= new MyPushButton(55,55,":/pics/imgs/暂停.png");
    pauseButton->setParent(this);
    pauseButton->move(795,2);
    connect(pauseButton,&MyPushButton::clicked,[=]{

        button->setMedia(QUrl("qrc:/sound/sound/Button3.mp3"));
        button->setVolume(50);
        button->play();

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

    //二倍速按钮
    MyPushButton *doubleButton= new MyPushButton(85,85,":/pics/imgs/一倍速.png");
    doubleButton->setParent(this);
    doubleButton->move(705,-10);
    connect(doubleButton,&MyPushButton::clicked,[=]{

        QMediaPlayer *button2 = new QMediaPlayer;
        button2->setMedia(QUrl("qrc:/sound/sound/Button3.mp3"));
        button2->setVolume(60);
        button2->play();

        //切换图片 调整计时器
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

    //倒计时音效
    QMediaPlayer *start = new QMediaPlayer;
    start->setMedia(QUrl("qrc:/sound/sound/count.mp3"));
    start->setVolume(75);
    start->play();
}
void PlayScene::checkResult(){

    if(victory==3)
        return;

    //qDebug()<<"游戏胜利";
    QPixmap pix;
    if(victory==1){
       pix.load(":/pics/imgs/胜利.png");
       button->setMedia(QUrl("qrc:/sound/sound/success.mp3"));   //成功音效
       button->setVolume(50);
       button->play();
    }
    else {
        pix.load(":/pics/imgs/失败.png");
        button->setMedia(QUrl("qrc:/sound/sound/gameover.mp3"));  //失败音效
        button->setVolume(55);
        button->play();
    }

    //结果标签
    resultLabel->setGeometry(0,0,pix.width(),pix.height());
    resultLabel->setPixmap(pix);
    resultLabel->move(this->width()*0.5-pix.width()*0.5,-pix.height());
    //移动
    QPropertyAnimation *animation = new QPropertyAnimation(resultLabel,"geometry");
    //设置时间
    animation->setDuration(1000);
    animation->setStartValue(QRect(resultLabel->x(),resultLabel->y(),resultLabel->width(),resultLabel->height()));
    animation->setEndValue(QRect(resultLabel->x(),100,resultLabel->width(),resultLabel->height()));
    animation->setEasingCurve(QEasingCurve ::OutBounce);
    animation->start();

    inGame=0;  //结束游戏
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

    if(inGame==0)    //结束时点击无用
        return;

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
    DrawEnemy(painter);         //画敌人
    DrawTower(painter);         //画塔
    DrawSelectionbox(painter);  //画塔坑
    DrawBullet(painter);        //画子弹


}

void PlayScene::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);
    int id = e->timerId();
    if (inGame&&(!isPaused))  //结束暂停时不更新
    {
        if(id == timerId2)
            CreatEnemyWave();

        if(id == timerId1)
        {
            update_bullet=false;
            Checkenemy();
            CheckTower();
            repaint();
            checkResult();
        }
        if(id==timerId3)
        {
            update_bullet=true;
            Tower_creatbullet();
            repaint();
        }

    }
    else if(isPaused)   //暂停时可以操作防御塔
    {

        if(id == timerId1)
        {
            update_bullet=false;
            CheckTower();
            repaint();
        }
    }

}
