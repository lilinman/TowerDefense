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
using namespace std;
#include"enemy.h"
#include"basetower.h"
#include"towerpos.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int Level);
    int Level;
    int Map[18][28]={{0}};             //总地图
private:
    vector<Point> Path;                //路径
    vector<Enemy*> EnemyVec;           //怪物数组
    vector<BaseTower*> TowerVec;       //防御塔数组
    vector<TowerPos *> TposVec;        //防御塔坑数组
    bool inGame=true;
    bool isPaused=false;
    bool isDouble=false;
    int playerhp=10;
    QLabel *playerlable= new QLabel(this);
    int a=10;
    int count = 0;                   //敌人计数器
    int totalCount=0;
    int timerId1;                    //第1个时间控制器，刷新
    int timerId2;                    //第2个 刷新敌人
    int timerId3;                    //第3个 刷新子弹
    bool update_bullet;
    int money;
    QLabel *moneylable= new QLabel(this);
    int wave=0;
    QLabel *wavelable= new QLabel(this);
    int totalwave;
protected:
    void manegeLable();
    bool spendMoney(int);//金币判断
    void Checkenemy();
    void CheckTower();
    void InitalGame();//游戏初始化
    bool CreatTower(int mx,int my);
    void Tower_creatbullet();
    void CreatEnemyWave();
    void timerEvent(QTimerEvent *e);
    void DrawEnemy(QPainter&);            //画出怪物
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);//鼠标事件
    void DrawTower(QPainter&);
    void DrawMapArr(QPainter&);             //用于画出地图函数
    void DrawBullet(QPainter&);
    void DrawSelectionbox(QPainter&);
    void CreatEnemy(int id);
signals:

    chooseBacklevel();//返回关卡选择

public slots:
};

#endif // PLAYSCENE_H
