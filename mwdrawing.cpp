#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTime>
#include<QDebug>
#include<QTimer>
#include"mainwindow.h"
#include"playscene.h"

//各类画图函数实现

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

void PlayScene::DrawSelectionbox(QPainter& painter){
    for(auto tp:TposVec)
    {

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
        if(!update_bullet&&!isPaused)
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


    QString str1=QString(":/pics/imgs/蛋糕%1.png").arg(this->playerhp); //终点蛋糕路径
    Point p(0,0);//终点坐标

    //每个关卡不同
    if(Level==1){
        painter.drawPixmap(0, 0,SIZEwid,SIZEhei,
                           QPixmap(":/pics/imgs/关卡1背景.jpg"));
        for (int j = 0; j < per_HEIGHT; j++)
            for (int i = 0; i < per_WIDTH; i++)
            {
                switch (Map[j][i])
                {
                case 1:     /*地面*/
                    painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE-10, imgSIZE-10,
                                       QPixmap(":/pics/imgs/地砖4.png"));
                    break;
                case 8:
                    painter.drawPixmap(i * imgSIZE+10, j * imgSIZE+10, imgSIZE*2-20, imgSIZE*2-20,
                                       QPixmap(":/pics/imgs/地砖5.png"));
                    break;
                case 9:
                    p.x=i;
                    p.y=j;
                    break;
                }
            }
        painter.drawPixmap(p.x*imgSIZE-10,p.y*imgSIZE-5,imgSIZE*2+10,imgSIZE*2+10,QPixmap(str1));
    }

    if(Level==2){
        painter.drawPixmap(0, 0,SIZEwid,SIZEhei,
                           QPixmap(":/pics/imgs/关卡2背景.jpg"));
        for (int j = 0; j < per_HEIGHT; j++)
            for (int i = 0; i < per_WIDTH; i++)
            {
                switch (Map[j][i])
                {
                case 1:     /*地面*/
                    painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE-10, imgSIZE-10,
                                       QPixmap(":/pics/imgs/地砖6.png"));
                    break;
                case 8:
                    painter.drawPixmap(i * imgSIZE+10, j * imgSIZE+10, imgSIZE*2-20, imgSIZE*2-20,
                                       QPixmap(":/pics/imgs/地砖7.png"));
                    break;
                case 9:
                    p.x=i;
                    p.y=j;
                    break;
                }
            }
        painter.drawPixmap(p.x*imgSIZE,p.y*imgSIZE,imgSIZE*2+30,imgSIZE*2+30,QPixmap(str1));
    }

    if(Level==3){
        painter.drawPixmap(0, 0,SIZEwid,SIZEhei,
                           QPixmap(":/pics/imgs/关卡3背景.jpg"));
        for (int j = 0; j < per_HEIGHT; j++)
            for (int i = 0; i < per_WIDTH; i++)
            {
                switch (Map[j][i])
                {
                case 1:     /*地面*/
                    painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE-10, imgSIZE-10,
                                       QPixmap(":/pics/imgs/地砖4.png"));
                    break;
                case 8:
                    painter.drawPixmap(i * imgSIZE+10, j * imgSIZE+10, imgSIZE*2-20, imgSIZE*2-20,
                                       QPixmap(":/pics/imgs/地砖8.png"));
                    break;
                case 9:
                    p.x=i;
                    p.y=j;
                    break;
                }
            }
        painter.drawPixmap(p.x*imgSIZE,p.y*imgSIZE,imgSIZE*2+30,imgSIZE*2+30,QPixmap(str1));
    }

    painter.drawPixmap(0,0, SIZEwid , 88,
                       QPixmap(":/pics/imgs/菜单栏.png"));

    painter.drawPixmap(200,-5, 70 , 70,
                       QPixmap(":/pics/imgs/金币.png"));
    painter.drawPixmap(325,7, 48 , 48,
                       QPixmap(":/pics/imgs/桃心.png"));




}
