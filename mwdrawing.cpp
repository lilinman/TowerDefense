#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTime>
#include<QTimer>
#include"enemy.h"
#include"basetower.h"

void MainWindow::DrawTower(QPainter& painter)
{
    for(auto e=TowerVec.begin();e!=TowerVec.end();e++)
               (*e)->Draw(painter);
}

void MainWindow::DrawEnemy(QPainter& painter)
{
    if(EnemyVec.empty())
        return;
    for(auto e=EnemyVec.begin();e!=EnemyVec.end();e++)
        if((*e)->get_Hp()>0)
               (*e)->Draw(painter);

    for (auto e = EnemyVec.begin(); e != EnemyVec.end(); e++){
      //if(!upd_bullet)
        if((*e)->Move()||(*e)->get_Hp()<=0) //怪物走到终点 或没血
        {
            delete *e;
            EnemyVec.erase(e);         //怪物走到终点则删除这个怪物
            break;
        }

    }

}
void MainWindow::DrawMapArr(QPainter& painter)
{
    painter.drawPixmap(0, 0, imgSIZE*per_WIDTH, imgSIZE*per_HEIGHT,
        QPixmap(":/pics/imgs/背景.png"));
    //地图数组
    int Map[per_HEIGHT][per_WIDTH] =
    {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 4, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,1,1,1,1,0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 1,1,1,1,1,1,0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,0,0,0,0,0,
        0, 0, 0, 1, 1, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,0,0,0,0,0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,0,0,0,0,0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,0,0,0,0,0,
        0, 0, 0, 1, 1, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 1, 1, 0, 9, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 6, 0,0,0,0,0,0,0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 9, 0, 0, 9, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
    };
    for (int j = 0; j < per_HEIGHT; j++)
        for (int i = 0; i < per_WIDTH; i++)
        {
            switch (Map[j][i])
            {
            case 1:     /*地面*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE, imgSIZE,
                    QPixmap(":/pics/imgs/地砖2.png"));
                break;
            case 2:     /*蓝色云1*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*3, imgSIZE*2,
                    QPixmap(":/pics/imgs/蓝色云1.png"));
                break;
            case 3:     /*蓝色云2*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*4, imgSIZE*2,
                    QPixmap(":/pics/imgs/蓝色云2.png"));
                break;
            case 4:     /*粉色云*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*3, imgSIZE*2,
                    QPixmap(":/pics/imgs/粉色云.png"));
                break;
            case 5:     /*热气球*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*4.5, imgSIZE*5.5,
                    QPixmap(":/pics/imgs/热气球.png"));
                break;
            case 6:     /*热气球*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*6, imgSIZE*8,
                    QPixmap(":/pics/imgs/热气球.png"));
                break;
            case 9:
//                QPen blackline((Qt::black),2.5);
//                painter.drawRect(i*imgSIZE, j*imgSIZE, imgSIZE*2 , imgSIZE*2);
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*2, imgSIZE*2,
                    QPixmap(":/pics/imgs/云朵炮台.png"));
                break;
            }
        }

}
