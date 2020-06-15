#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTime>
#include<QTimer>
#include<QDebug>
#include"enemy.h"
#include"basetower.h"
#include"bullet.h"
#include"towerpos.h"
#include"playscene.h"
#include"tower1.h"
#include"tower2.h"
#include"tower3.h"
void PlayScene::InitalGame(){
//实现不同关卡初始化
//防御塔坑 怪物路径vector
    vector<Point> towerPosition={
        Point(5,10),
        Point(1,8),Point(13,9),
        Point(9,7),Point(17,7),
        Point(9,10),Point(17,10),
        Point(13,4),Point(21,10),Point(25,8)
    };
    //初始化塔坑
    for(auto tp=towerPosition.begin();tp!=towerPosition.end();tp++)
    {
        TposVec.push_back(new TowerPos(Point(tp->x*imgSIZE,tp->y*imgSIZE)));

    }

}
void PlayScene::Checkenemy(){
    //qDebug()<<"执行Checkenemy";
    for(auto e =EnemyVec.begin();e!=EnemyVec.end();e++)
    {
        if((*e)->get_Hp()<=0){
            //遍历防御塔 设置目标敌人是他的为空
            for(auto bt:TowerVec){
                if(bt->get_Bullet()!=NULL){
                    if(bt->get_Bullet()->get_target()==(*e)){
                        delete bt->get_Bullet();
                        bt->set_Bullet(0,0,false);
                    }
                }
                if(bt->get_Target()==(*e)){
                    bt->set_Target(NULL);
                }
            }
            delete (*e);
            EnemyVec.erase(e);
            if(e==EnemyVec.end()) break;
        }
        //以后对生命值减少进行优化
        else if((*e)->getway().empty())
        {//怪物到达终点
            playerhp--;
            delete (*e);
            EnemyVec.erase(e);
            if(e==EnemyVec.end()) break;
        }
    }
}

void PlayScene::CheckTower(){

    for(auto e =TowerVec.begin();e!=TowerVec.end();e++){
         if((*e)->get_Hp()<=0){
             delete (*e);
             TowerVec.erase(e);
             if(e==TowerVec.end()) break;
         }
    }
}

bool PlayScene::CreatTower(int mx,int my)
{
     //qDebug()<<"执行CreatTower";
    //遍历防御塔坑位置 创造防御塔
    for(auto tp:TposVec){

        BaseTower *tower;

        if(tp->get_selectbox()->get_isshow()&&tp->get_hasTower())//有选择框 有塔 选择升级或删塔
        {
            int id=tp->get_selectbox()->checkbox(mx,my);  //选择框循环 返回选择结果
            if(id==2) //点击升级
            {
                tp->get_myTower()->upGrade();//防御塔升级
            }
            if(id==4){
               //遍历防御塔删除对应塔
                tp->get_myTower()->set_Hp(0);
                tp->set_hasTower(false);//无塔
                tp->set_myTower(NULL);
            }
            tp->get_selectbox()->set_isshow(false);//选择框消失
            return true;
        }

        if(tp->get_selectbox()->get_isshow()&&!tp->get_hasTower())//有选择框 没有塔 选择建塔
        {
            int id=tp->get_selectbox()->checkbox(mx,my);  //选择框循环 返回选择结果
            switch (id) {
            case 1:                                        //创造防御塔1
               tower = new Tower1(tp->get_X()+3,tp->get_Y()-5);
                break;
            case 2:
               tower = new Tower2(tp->get_X()+3,tp->get_Y()-5);
                break;
            case 3:
               tower = new Tower3(tp->get_X()+3,tp->get_Y()-5);
            default:
                break;
            }
            if(id!=0&&id!=4) {                            //创建了防御塔 添到序列
                TowerVec.push_back(tower);
                tp->set_hasTower(true);                   //设置坑位有塔
                //qDebug()<<"has tower";
                tp->set_myTower(TowerVec.back());         //设置坑位的塔
            }
            tp->get_selectbox()->set_isshow(false);
            return true;
        }


        if (tp->get_Cpoint().is_include(Point(mx,my),30)//在坑位选择范围内
                &&(!tp->get_hasTower())                      //没有塔
                &&(!tp->get_selectbox()->get_isshow()))      //没有选择框
        {
             //qDebug()<<"1 pattern";
            tp->get_selectbox()->set_pattern(1);             //设置模式为1购买模式
            for(auto tp1:TposVec)                            //以防出现遍历的先后造成选择框显示错误问题
                if(tp1->get_selectbox()->get_isshow())
                {
                    tp1->get_selectbox()->set_isshow(false);
                    return true;
                }
            tp->get_selectbox()->set_isshow(true);           //选择框显示
            return true;
        }

        if (tp->get_Cpoint().is_include(Point(mx,my),30)    //在坑位选择范围内
                &&tp->get_hasTower()                        //有塔
                &&!tp->get_selectbox()->get_isshow())       //没有选择框
        {
            //qDebug()<<"2 pattern";
            tp->get_selectbox()->set_pattern(2);            //模式为2 升级或删除模式
            for(auto tp1:TposVec)                            //以防出现遍历的先后造成选择框显示错误问题
                if(tp1->get_selectbox()->get_isshow())
                {
                    tp1->get_selectbox()->set_isshow(false);
                    return true;
                }
            tp->get_selectbox()->set_isshow(true);          //选择框显示
            return true;
        }
    }

    return false;
}

void PlayScene::CreatEnemy(Point waypoint[], int len, int x, int y,int id)
{
    EnemyVec.push_back(new Enemy(waypoint,len,x,y,id));//新建敌人
}

void PlayScene::CreatEnemyWave(){
    int pathNUM=12;
    Point  Path[]={

                    Point(13*positionSIZE,46*positionSIZE),//第二个节点
                    Point(13*positionSIZE,30*positionSIZE),//第三个节点
                    Point(28*positionSIZE,30*positionSIZE),
                    Point(28*positionSIZE,46*positionSIZE),//第四个节点
                    Point(44*positionSIZE,46*positionSIZE),//第五个节点
                    Point(44*positionSIZE,6*positionSIZE),//第六个节点
                    Point(60*positionSIZE,6*positionSIZE),//第七个节点
                    Point(60*positionSIZE,46*positionSIZE),//8
                    Point(76*positionSIZE,46*positionSIZE),//9
                    Point(76*positionSIZE,30*positionSIZE),//10
                    Point(92*positionSIZE,30*positionSIZE),//11
                    Point(92*positionSIZE,46*positionSIZE),//11
                    Point(104*positionSIZE,46*positionSIZE),//11
                   };

    Point startpoint(4*positionSIZE,46*positionSIZE);//起点

    if(count>=0&&count<=5)
        CreatEnemy(Path,pathNUM,startpoint.x,startpoint.y,1);
     if(count>=6&&count<=12)
        CreatEnemy(Path,pathNUM,startpoint.x,startpoint.y,2);

     count++;

 }

void PlayScene::Tower_creatbullet()
 {
     if(TowerVec.empty())
         return;

     //qDebug()<<"执行Tower_creatbullet";

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
                         tower->set_Bullet(ex,ey,true);//新建子弹
                     break;
                 }
                 if(!flag){//如果攻击范围内没有敌人，消去子弹
                     delete tower->get_Bullet();
                     tower->set_Bullet(ex,ey,false);//设置为NULL
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
