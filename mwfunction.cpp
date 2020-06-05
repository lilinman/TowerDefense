#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTime>
#include<QTimer>
#include"enemy.h"
#include"basetower.h"
#include"bullet.h"
void MainWindow::initalGame(){
//实现不同关卡初始化
//防御塔坑 怪物路径vector





}

bool MainWindow::CreatTower(int mx,int my)
{
    vector<Point> towerPosition={
        Point(6,7),Point(6,10),
        Point(9,13),Point(12,13),
        Point(16,10),Point(22,10),
        Point(24,5)
    };
    //遍历防御塔坑位置 创造防御塔
    for(auto tp=towerPosition.begin(); tp != towerPosition.end(); tp++){
        if ((mx < (tp->x+2)*imgSIZE) && (mx >=tp->x*imgSIZE) && (my<(tp->y+2)*imgSIZE) &&(my>=tp->y*imgSIZE))
        {
                TowerVec.push_back(new BaseTower(tp->x*imgSIZE,tp->y*imgSIZE,1));
                return true;
        }
    }
    return false;
}

void MainWindow::CreatEnemy(Point waypoint[], int len, int x, int y,int id)
{
    EnemyVec.push_back(new Enemy(waypoint,len,x,y,id));//新建敌人
}

void MainWindow::CreatEnemyWave(){
    Point  Path[]={
                    Point(21*positionSIZE,11*positionSIZE),//第一个节点
                    Point(6*positionSIZE,11*positionSIZE),//第二个节点
                    Point(6*positionSIZE,34*positionSIZE),//第三个节点
                    Point(21*positionSIZE,34*positionSIZE),//第四个节点
                    Point(21*positionSIZE,44*positionSIZE),//第五个节点
                    Point(43*positionSIZE,44*positionSIZE),//第六个节点
                    Point(43*positionSIZE,34*positionSIZE),//第七个节点
                    Point(57*positionSIZE,34*positionSIZE),//8
                    Point(57*positionSIZE,20*positionSIZE),//9
                    Point(83*positionSIZE,20*positionSIZE),//10
                    Point(83*positionSIZE,8*positionSIZE),//11
                    Point(95*positionSIZE,8*positionSIZE)//终点
                   };

    Point startpoint(21*positionSIZE,0);//起点

    if(count>=0&&count<=5)
       CreatEnemy(Path,12,startpoint.x,startpoint.y,1);
    if(count>=6&&count<=12)
       CreatEnemy(Path,12,startpoint.x,startpoint.y,2);
    count++;

}

void MainWindow::Tower_creatbullet(){
//    if(TowerVec.empty())
//        return;
//    for(auto tower:TowerVec){
//        int ex=tower->get_X()+tower->get_Width()/2;
//        int ey=tower->get_Y()+tower->get_Height()/2;
//        if (tower->get_Target()==NULL)   //目标敌人为空
//        {
//            for(auto enemy:EnemyVec)
//            {
//                int px=enemy->get_X()+enemy->get_Width()/2;//敌人中心点坐标
//                int py=enemy->get_Y()+enemy->get_Height()/2;
//                //在攻击范围内
//                if((ex-px)*(ex-px)+(ey-py)*(ey-py)<=tower->get_Range()*tower->get_Range())
//                {
//                    tower->set_Target(enemy);//设置防御塔的目标敌人
//                    if(tower->get_Bullet()==NULL)//如果现在子弹为空 新建子弹及子弹目标敌人
//                        tower->set_Bullet(new Bullet(ex,ey,));
//                }
//            }
//        }
//    }
//    for(auto e=TowerVec.begin();e!=TowerVec.end();e++)
//    {   //防御塔中心点坐标
//        BaseTower *tower=e;
//        int ex=(*e)->get_X()+(*e)->get_Width()/2;
//        int ey=(*e)->get_Y()+(*e)->get_Height()/2;
        
        
//    }
}
