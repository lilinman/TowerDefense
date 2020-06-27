#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>     //画家
#include <QMouseEvent>  //鼠标事件
#include <Qtimer>       //定时器
#include <QLabel>
#include<vector>
#include<QString>
#include<iostream>
#include<QMediaPlaylist>
using namespace std;
#include"enemy.h"
#include"basetower.h"
#include"towerpos.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int Level);

private:

    int victory=3;                     //胜利
    int Level;                         //不同关卡
    int Map[18][28]={{0}};             //总地图
    int money;                         //金币
    int wave=0;                        //实时波数
    int totalwave ;                    //总波数
    int playerhp=10;                   //玩家生命值
    int count = -2;                    //敌人计数器
    const int totalCount=9;            //默认每波10个敌人
    int timerId1;                      //第1个时间控制器，刷新重画
    int timerId2;                      //第2个 刷新敌人
    int timerId3;                      //第3个 刷新子弹
    bool inGame=true;                  //正在游戏
    bool isPaused=false;               //是否暂停
    bool isDouble=false;               //是否倍速
    bool update_bullet;                //是否正在刷新子弹，如果是，敌人不移动
    vector<Point> Path;                //路径
    vector<Enemy*> EnemyVec;           //怪物数组
    vector<BaseTower*> TowerVec;       //防御塔数组
    vector<TowerPos *> TposVec;        //防御塔坑数组
    QLabel *moneylable= new QLabel(this);      //金币标签
    QLabel *wavelable= new QLabel(this);       //波数标签
    QLabel *playerlable= new QLabel(this);     //玩家生命值标签
    QLabel *resultLabel=new QLabel(this);      //结果标签
    QMediaPlayer *button = new QMediaPlayer;   //按键时音效
    QMediaPlayer *eaten = new QMediaPlayer;    //被吃时音效
    QMediaPlayer *finalwave = new QMediaPlayer;//结果音效
    QMediaPlayer *bgm = new QMediaPlayer;         //背景音乐
    QMediaPlaylist *gameList = new QMediaPlaylist;//播放列表

protected:
    void InitalGame();                       //游戏初始化
    void checkResult();                      //最后显示胜利或失败
    void manegeLable();                      //初始化标签
    bool spendMoney(int);                    //金币判断
    void Checkenemy();                       //检查敌人
    void CheckTower();                       //检查防御塔
    bool CreatTower(int mx,int my);          //创造或升级或拆防御塔 判断点击
    void Tower_creatbullet();                //创造子弹
    void CreatEnemyWave();                   //创造一波敌人
    void CreatEnemy(int id);                 //创造一个敌人
    void DrawEnemy(QPainter&);               //画出怪物
    void DrawTower(QPainter&);               //画出防御塔
    void DrawMapArr(QPainter&);              //画出地图
    void DrawBullet(QPainter&);              //画出子弹
    void DrawSelectionbox(QPainter&);        //画出选择框
    void timerEvent(QTimerEvent *e);         //计时器事件
    void paintEvent(QPaintEvent *);          //画图事件
    void mousePressEvent(QMouseEvent *event);//鼠标事件


signals:

    chooseBacklevel();//返回关卡选择

public slots:
};

#endif // PLAYSCENE_H
