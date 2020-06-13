#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTime>
#include<QTimer>
#include"enemy.h"
#include"basetower.h"
#include"bullet.h"
#include"towerpos.h"
void MainWindow::InitalGame(){
//实现不同关卡初始化
//防御塔坑 怪物路径vector
    vector<Point> towerPosition={
        Point(6,7),Point(6,10),
        Point(11,12),
        Point(16,10),Point(22,10),
        Point(24,5)
    };
    //初始化塔坑
    for(auto tp=towerPosition.begin();tp!=towerPosition.end();tp++)
    {
        TposVec.push_back(new TowerPos(Point(tp->x*imgSIZE,tp->y*imgSIZE)));

    }

}
void MainWindow::Checkenemy(){
    for(auto e =EnemyVec.begin();e!=EnemyVec.end();e++)
    {
        if((*e)->get_Hp()<=0){
            for(auto bt:TowerVec){
                if(bt->get_Bullet()!=NULL){
                    if(bt->get_Bullet()->get_target()==(*e)){
                        delete bt->get_Bullet();
                        bt->set_Bullet(NULL);
                    }
                }
                if(bt->get_Target()==(*e)){
                    bt->set_Target(NULL);
                }
            }
            delete (*e);
            EnemyVec.erase(e);
        }
        //以后对生命值减少进行优化
        else if((*e)->getway().empty())
        {//怪物到达终点
            playerhp--;
            delete (*e);
            EnemyVec.erase(e);
        }
    }
}
bool MainWindow::CreatTower(int mx,int my)
{

    //遍历防御塔坑位置 创造防御塔
    for(auto tp:TposVec){

        if (tp->get_Cpoint().is_include(Point(mx,my),30)
                &&!tp->get_hasTower() //没有塔
                &&!tp->get_selectbox()->get_isshow())//没有选择框
        {
            tp->get_selectbox()->set_pattern(1);//模式为1
            tp->get_selectbox()->set_isshow(true);//选择框显示
            return true;
        }

        if (tp->get_Cpoint().is_include(Point(mx,my),30)
                &&tp->get_hasTower()                //有塔
                &&!tp->get_selectbox()->get_isshow())//没有选择框
        {
            tp->get_selectbox()->set_pattern(2);//模式为2
            tp->get_selectbox()->set_isshow(true);//选择框显示
            return true;
        }

        if(tp->get_selectbox()->get_isshow()&&!tp->get_hasTower())//有选择框 没有塔 选择建塔
        {
            int id=tp->get_selectbox()->checkbox(mx,my);  //选择框循环 返回选择结果
            if(id!=0){                                 //id不为0 选中建立防御塔
                TowerVec.push_back(new BaseTower(tp->get_X(),tp->get_Y(),id));
                tp->set_hasTower(true);
                tp->set_myTower(TowerVec.back());
                tp->get_selectbox()->set_isshow(false);//选择框消失
                return true;
            }
        }

        }

//        if (tp->get_Cpoint().is_include(Point(mx,my),30)&&!tp->get_hasTower())
//        {

//                TowerVec.push_back(new BaseTower(tp->get_X(),tp->get_Y(),1));
//                tp->set_hasTower(true);
//                tp->set_myTower(TowerVec.back());
//                return true;
//        }
//
//    vector<Point> towerPosition={
//        Point(6,7),Point(6,10),
//        Point(9,13),Point(12,13),
//        Point(16,10),Point(22,10),
//        Point(24,5)
//    };
//    //遍历防御塔位置 创造防御塔
//    for(auto tp=towerPosition.begin(); tp != towerPosition.end(); tp++){
//        if ((mx < (tp->x+2)*imgSIZE) && (mx >=tp->x*imgSIZE) && (my<(tp->y+2)*imgSIZE) &&(my>=tp->y*imgSIZE)){
//                TowerVec.push_back(new BaseTower(tp->x*imgSIZE,tp->y*imgSIZE,1));
//        }
//    }
    return false;
}

void MainWindow::CreatEnemy(Point waypoint[], int len, int x, int y,int id)
{
    EnemyVec.push_back(new Enemy(waypoint,len,x,y,id));//新建敌人
}

void MainWindow::CreatEnemyWave(){
    Point  Path[]={
                    Point(21*positionSIZE,11*positionSIZE),//第一个节点
                    Point(7*positionSIZE,11*positionSIZE),//第二个节点
                    Point(7*positionSIZE,34*positionSIZE),//第三个节点
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

 void MainWindow::Tower_creatbullet()
 {
     if(TowerVec.empty())
         return;
     for(auto tower:TowerVec)
     {
         int ex=tower->get_X()+tower->get_Width()/2;//防御塔中心点坐标
         int ey=tower->get_Y()+tower->get_Height()/2;

         if (tower->get_Target()!=NULL)   //目标敌人为空
         {
             int px=tower->get_Target()->get_X()+tower->get_Target()->get_Width()/2;//敌人中心点坐标
             int py=tower->get_Target()->get_Y()+tower->get_Target()->get_Height()/2;
             //在范围外
             if((ex-px)*(ex-px)+(ey-py)*(ey-py)>tower->get_Range()*tower->get_Range())//判断是否在范围内
                 tower->set_Target(NULL);
         }

         if(tower->get_Target()==NULL){
             if(!EnemyVec.empty())//不为空就寻找最近的敌人
             for(auto enemy:EnemyVec)
             {
                 int flag=0;
                 int px=enemy->get_X()+enemy->get_Width()/2;//敌人中心点坐标
                 int py=enemy->get_Y()+enemy->get_Height()/2;

                 //在攻击范围内
                 if((ex-px)*(ex-px)+(ey-py)*(ey-py)<=tower->get_Range()*tower->get_Range())
                 {

                     tower->set_Target(enemy);//设置防御塔的目标敌人
                     flag=1;
                     if(tower->get_Bullet()==NULL)//如果现在子弹为空 新建子弹及子弹目标敌人
                         tower->set_Bullet(new Bullet(ex,ey,tower->get_BulletID(),enemy));
                     break;
                 }
                 if(!flag){//如果攻击范围内没有敌人，消去子弹
                     delete tower->get_Bullet();
                     tower->set_Bullet(NULL);
                 }
             }
         }
         //现在目标敌人不为空，攻击
         if(tower->get_Bullet()!=NULL)
         {
             tower->attack();
         }
     }

     Checkenemy();//检查敌人
}
