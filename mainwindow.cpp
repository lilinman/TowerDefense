#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //配置主场景
    move(posX,posY);//窗口位置
    setFixedSize(SIZEwid,SIZEhei);//窗口大小
    //设置图标
    setWindowIcon(QIcon(":/pics/imgs/怪兽2.png"));
    //设置标题
    setWindowTitle("主场景");
    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //播放背景音乐
    QMediaPlayer *bgm1 = new QMediaPlayer;
    bgm1->setMedia(QUrl("qrc:/sound/sound/bgm1.mp3"));
    bgm1->setVolume(15);
    bgm1->play();



    //开始按钮
    MyPushButton *startButton= new MyPushButton(400,200,":/pics/imgs/play按钮.png");
    startButton->setParent(this);
    startButton->move(this->width()*0.5-(startButton->width()/2)-20,this->height()*0.7);

    //选择关卡场景
    ChooseScene = new ChooseLevelScene;

    //监听选择关卡信号 返回
    connect(ChooseScene,&ChooseLevelScene::chooseBack,this,[=](){
        ChooseScene->hide();
         this->show();
    });

    connect(ChooseScene,&ChooseLevelScene::StopMuisc,this,[=](){
        bgm1->pause();
    });

    connect(ChooseScene,&ChooseLevelScene::PlayMuisc,this,[=](){
        bgm1->play();
    });

    connect(startButton,&MyPushButton::clicked,[=]{
        //弹起特效
        startButton->zoom1();
        startButton->zoom2();

        QMediaPlayer *button1 = new QMediaPlayer;
        button1->setMedia(QUrl("qrc:/sound/sound/Button4.mp3"));
        button1->setVolume(80);
        button1->play();

        QTimer::singleShot(300,this,[=]{ //延时
            //隐藏自己 显示选择关卡场景、
            this->hide();
            ChooseScene->show();
        });
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{


    QPainter painter(this);     //创建画家类
    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿

    painter.drawPixmap(0, 0, imgSIZE*per_WIDTH, imgSIZE*per_HEIGHT,
        QPixmap(":/pics/imgs/界面1.png"));

}
