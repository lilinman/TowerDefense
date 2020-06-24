#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTime>
#include<QDebug>
#include<QTimer>
#include"mainwindow.h"
#include"playscene.h"
void PlayScene::DrawTower(QPainter& painter)
{
    //qDebug()<<"执行画塔";
    if(TowerVec.empty())
        return;
    for(auto e : TowerVec)
    {
        e->Draw(painter);
        if(e->get_ShowUpgrade()&&e->get_TowerLevel()!=3){
            if(e->get_UpgradePrice()<=money)
                painter.drawPixmap(e->get_X()+18,e->get_Y()-imgSIZE,imgSIZE,imgSIZE,
                                   QPixmap(":/pics/imgs/可升级.png"));
        }
    }

}

void PlayScene::DrawTowerpos(QPainter& painter){
    //qDebug()<<"执行画塔坑";
    for(auto tp:TposVec)
    {
        tp->Draw(painter);
        if(tp->get_selectbox()->get_isshow()){
            if(tp->get_selectbox()->get_pattern()==1)
                tp->get_selectbox()->Draw1(painter,money);
            else if(tp->get_selectbox()->get_pattern()==2)
            {
                tp->get_selectbox()->Draw2(painter,tp->get_myTower(),money);
            }
        }
    }
}

void PlayScene::DrawEnemy(QPainter& painter)
{
    //qDebug()<<"执行画敌人";
    if(EnemyVec.empty())
        return;
    for(auto e:EnemyVec)
    {
        e->Draw(painter);

        if(!update_bullet)
            e->Move();
    }
}

void PlayScene::DrawBullet(QPainter& painter){
    //qDebug()<<"执行画子弹";
    for(auto t:TowerVec){
        if(t->get_Bullet()!=NULL)
            t->get_Bullet()->Draw(painter);
    }
}

void PlayScene::DrawMapArr(QPainter& painter)
{

    painter.drawPixmap(0, 0,SIZEwid,SIZEhei,
                       QPixmap(":/pics/imgs/背景.png"));
    //地图数组
    int Map[per_HEIGHT][per_WIDTH] =
    {// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27
     /*0*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     /*1*/  0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
     /*2*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     /*3*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     /*4*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0,
     /*5*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     /*6*/  0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     /*7*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     /*8*/  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
     /*9*/  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
     /*10*/  0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 6, 0,
     /*11*/  0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 9, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
     /*12*/  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
     /*13*/  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
     /*14*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     /*15*/  2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     /*16*/  0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,
     /*17*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    };
    for (int j = 0; j < per_HEIGHT; j++)
        for (int i = 0; i < per_WIDTH; i++)
        {
            switch (Map[j][i])
            {
            case 1:     /*地面*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE, imgSIZE,
                                   QPixmap(":/pics/imgs/地砖4.png"));
                break;
            }
        }

}
