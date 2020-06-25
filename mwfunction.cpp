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

bool PlayScene::spendMoney(int n){
    if(n<=money){
        money-=n;
        moneylable->setText(QString::number(this->money));
        return true;
    }
    else
        return false;
}

void PlayScene::Checkenemy(){

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
            //金钱变化
            money+=(*e)->get_Price();
            moneylable->setText(QString::number(this->money));//刷新金币
            delete (*e);
            EnemyVec.erase(e);
            if(e==EnemyVec.end()) break;
        }

        else if((*e)->getway().empty())
        {//怪物到达终点
            playerhp--;       //生命值减少
            playerlable->setText(QString::number(this->playerhp));//刷新金币
            delete (*e);
            EnemyVec.erase(e);
            if(e==EnemyVec.end()) break;
        }
    }
}

void PlayScene::CheckTower(){

    //qDebug()<<"执行checktower";
    for(auto e =TowerVec.begin();e!=TowerVec.end();e++){
        if((*e)->get_Hp()<=0){
            money+=(*e)->get_SellPrice();                     //拆塔
            moneylable->setText(QString::number(this->money));//刷新金币

            QMediaPlayer *player = new QMediaPlayer;          //拆塔音效
            player->setMedia(QUrl("qrc:/sound/sound/soldTower.mp3"));
            player->setVolume(30);
            player->play();

            delete (*e);
            TowerVec.erase(e);
            if(e==TowerVec.end()) break;
        }
    }
    //qDebug()<<"执行完checktower";
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
            if(id==2)                                     //点击升级
            {
                if(spendMoney(tp->get_myTower()->get_UpgradePrice()))//判断钱是否足够
                    tp->get_myTower()->upGrade();            //防御塔升级
                else
                {
                    QMediaPlayer *player = new QMediaPlayer;          //错误音乐
                    player->setMedia(QUrl("qrc:/sound/sound/error.mp3"));
                    player->setVolume(30);
                    player->play();
                }
            }
            if(id==4){
                tp->get_myTower()->set_Hp(0);
                tp->set_hasTower(false);//无塔
                tp->set_myTower(NULL);
            }
            tp->get_selectbox()->set_isshow(false);         //选择框消失
            if(tp->get_myTower()!=NULL)
                tp->get_myTower()->set_ShowUpgrade(true);       //显示可否升级
            return true;
        }

        if(tp->get_selectbox()->get_isshow()&&!tp->get_hasTower())//有选择框 没有塔 选择建塔
        {
            int id=tp->get_selectbox()->checkbox(mx,my);  //选择框循环 返回选择结果
            switch (id) {
            case 1:                                       //创造防御塔1
                tower = new Tower1(tp->get_X()+3,tp->get_Y()-5);
                break;
            case 2:                                       //创造防御塔2
                tower = new Tower2(tp->get_X()+3,tp->get_Y()-5);
                break;
            case 3:                                       //创造防御塔3
                tower = new Tower3(tp->get_X()+3,tp->get_Y()-5);
            default:
                break;
            }
            if(id>=1&&id<=3) {  //价钱足够创建了防御塔 添到序列
                if(spendMoney(tower->get_Price())){

                    TowerVec.push_back(tower);
                    tp->set_hasTower(true);                   //设置坑位有塔
                    //qDebug()<<"has tower";
                    tp->set_myTower(TowerVec.back());         //设置坑位的塔
                    QMediaPlayer *player = new QMediaPlayer;
                    player->setMedia(QUrl("qrc:/sound/sound/butTower.mp3"));
                    player->setVolume(30);
                    player->play();

                }
                else
                {
                    QMediaPlayer *player = new QMediaPlayer;          //错误音乐
                    player->setMedia(QUrl("qrc:/sound/sound/error.mp3"));
                    player->setVolume(30);
                    player->play();
                }

            }
            tp->get_selectbox()->set_isshow(false);
            return true;
        }


        if (tp->get_Cpoint().is_include(Point(mx,my),30)//在坑位选择范围内
                &&(!tp->get_hasTower())                      //没有塔
                &&(!tp->get_selectbox()->get_isshow()))      //没有选择框
        {
            QMediaPlayer *player = new QMediaPlayer;
            player->setMedia(QUrl("qrc:/sound/sound/Button6.mp3"));
            player->setVolume(200);
            player->play();


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
            QMediaPlayer *player = new QMediaPlayer;
            player->setMedia(QUrl("qrc:/sound/sound/Button6.mp3"));
            player->setVolume(200);
            player->play();

            //qDebug()<<"2 pattern";
            tp->get_myTower()->set_ShowUpgrade(false);      //不显示是否升级
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

void PlayScene::CreatEnemy(int id)
{
    Point startpoint[3]={                      //起点
                                               Point(32*positionSIZE,12*positionSIZE),
                                               Point(13*positionSIZE,30*positionSIZE),
                                               Point(16*positionSIZE,7*positionSIZE)
                        };

    EnemyVec.push_back(new Enemy(Path,startpoint[Level-1].x,startpoint[Level-1].y,id));//新建敌人
}

void PlayScene::CreatEnemyWave(){



    if(EnemyVec.empty()&&count>0&&count>=totalCount)//如果敌人为空 则下一波 是最后一波时显示游戏胜利
    {
        if(wave!=totalwave){
            wave++;
            QString str1=QString("第 %1 / %2 波怪物").arg(this->wave).arg(this->totalwave);
            wavelable->setText(str1);//刷新波数
            count=-2;
        }
        else
            inGame=0;
    }
    if(Level==1){
        switch (wave) {
        case 1:
            totalCount=4;
            if(count>=0&&count<=5){
                CreatEnemy(1);
            }
            break;
        case 2:
            totalCount=4;
            if(count>=0&&count<=2){
                CreatEnemy(1);
            }
            if(count>=3&&count<=4){
                CreatEnemy(2);
            }
            break;
        case 3:
            totalCount=4;
            if(count>=0&&count<=3){
                CreatEnemy(2);
            }
            if(count>=3&&count<=4){
                CreatEnemy(6);
            }
            break;
        default:
            break;
        }
    }
    if(Level==2)
    {
        switch (wave) {
        case 1:
            totalCount=4;
            if(count>=0&&count<=4){
                CreatEnemy(5);
            }
            break;
        case 2:
            totalCount=4;
            if(count>=0&&count<=2){
                CreatEnemy(1);
            }
            if(count>=3&&count<=4){
                CreatEnemy(6);
            }
            break;
        case 3:
            totalCount=4;
            if(count>=0&&count<=3){
                CreatEnemy(2);
            }
            if(count>=3&&count<=4){
                CreatEnemy(6);
            }
        case 4:
            totalCount=6;
            if(count>=0&&count<=3){
                CreatEnemy(7);
            }
            if(count>=3&&count<=4){
                CreatEnemy(8);
            }
            break;
        default:
            break;
        }
    }
        if(Level==3)
        {
            switch (wave) {
            case 1:
                totalCount=4;
                if(count>=0&&count<=2){
                    CreatEnemy(1);
                }
                if(count>=3&&count<=4){
                    CreatEnemy(6);
                }
                break;
            case 2:
                totalCount=4;
                if(count>=0&&count<=2){
                    CreatEnemy(2);
                }
                if(count>=3&&count<=4){
                    CreatEnemy(7);
                }
                break;
            case 3:
                totalCount=6;
                if(count>=0&&count<=3){
                    CreatEnemy(3);
                }
                if(count>=3&&count<=6){
                    CreatEnemy(8);
                }
                break;
            case 4:
                totalCount=7;
                if(count>=0&&count<=3){
                    CreatEnemy(4);
                }
                if(count>=3&&count<=7){
                    CreatEnemy(9);
                }
                break;
            case 5:
                totalCount=3;
                if(count>=0&&count<=3){
                    CreatEnemy(10);
                }
                break;

            default:
                break;
            }
    }

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

        if (tower->get_Target()!=NULL)   //目标敌人不为空
        {
            int px=tower->get_Target()->get_X()+tower->get_Target()->get_Width()/2;//敌人中心点坐标
            int py=tower->get_Target()->get_Y()+tower->get_Target()->get_Height()/2;
            //在范围外
            if((ex-px)*(ex-px)+(ey-py)*(ey-py)>tower->get_Range()*tower->get_Range())//判断是否在范围内
                tower->set_Target(NULL);
        }

        if(tower->get_Target()==NULL){
            if(!EnemyVec.empty())      //不为空就寻找最近的敌人
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
                    if(!flag){                       //如果攻击范围内没有敌人，消去子弹
                        delete tower->get_Bullet();
                        tower->set_Bullet(ex,ey,false);//设置为NULL
                    }
                }
        }
        //现在目标敌人不为空，攻击
        if(tower->get_Bullet()!=NULL)
        {
            tower->attack(EnemyVec);
        }
    }

    Checkenemy();//检查敌人
}

void PlayScene::InitalGame(){
    //实现不同关卡初始化
    //防御塔坑 怪物路径vector

    int tmpMap1[per_HEIGHT][per_WIDTH]=
    {
        // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27
        /*0*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*1*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*2*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*3*/  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        /*4*/  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        /*5*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 8, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        /*6*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        /*7*/  0, 0, 0, 0, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 1, 1, 0, 0, 0, 0,
        /*8*/  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        /*9*/  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
       /*10*/  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
       /*11*/  0, 0, 0, 0, 1, 1, 8, 0, 0, 0, 8, 0, 0, 8, 0, 0, 8, 0, 0, 0, 8, 0, 1, 1, 0, 0, 6, 0,
       /*12*/  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
       /*13*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
       /*14*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
       /*15*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       /*16*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       /*17*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    };


    int tmpMap2[per_HEIGHT][per_WIDTH]=
    {
        // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*0*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*1*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*2*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*3*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*4*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 8, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*5*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*6*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0,
        /*7*/  0, 0, 0, 1, 1, 1, 1, 1, 1, 8, 0, 1, 1, 0, 0, 1, 1, 8, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        /*8*/  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        /*9*/  0, 0, 0, 0, 0, 8, 0, 1, 1, 0, 0, 1, 1, 8, 0, 1, 1, 0, 0, 1, 1, 8, 0, 0, 0, 0, 0, 0,
        /*10*/  0, 0, 0, 0, 0, 0, 0, 1, 1, 8, 0, 1, 1, 0, 0, 1, 1, 8, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        /*11*/  0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        /*12*/  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        /*13*/  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        /*14*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*15*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*16*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*17*/

    };

    int tmpMap3[per_HEIGHT][per_WIDTH]=
    {
        // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*0*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*1*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*2*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        /*3*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        /*4*/  0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 1, 1, 0, 0, 0, 0,
        /*5*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        /*6*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        /*7*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 8, 0, 1, 1, 0, 0, 0, 0,
        /*8*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        /*9*/  0, 0, 0, 0, 1, 1, 8, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        /*10*/  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 6, 0,
        /*11*/  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 0, 1, 1, 0, 0, 0, 0,
        /*12*/  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        /*13*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        /*14*/  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        /*15*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*16*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /*17*/
    };

    vector<Point>Path1={
        Point(32*positionSIZE,18*positionSIZE),
        Point(16*positionSIZE,18*positionSIZE),
        Point(16*positionSIZE,50*positionSIZE),
        Point(88*positionSIZE,50*positionSIZE),
        Point(88*positionSIZE,18*positionSIZE),
        Point(72*positionSIZE,18*positionSIZE),
        Point(72*positionSIZE,12*positionSIZE),
    };

    vector<Point>Path2={
        Point(28*positionSIZE,30*positionSIZE),
        Point(28*positionSIZE,50*positionSIZE),
        Point(44*positionSIZE,50*positionSIZE),
        Point(44*positionSIZE,10*positionSIZE),
        Point(60*positionSIZE,10*positionSIZE),
        Point(60*positionSIZE,50*positionSIZE),
        Point(76*positionSIZE,50*positionSIZE),
        Point(76*positionSIZE,30*positionSIZE),
        Point(92*positionSIZE,30*positionSIZE),
    };

    vector<Point>Path3={
        Point(88*positionSIZE,10*positionSIZE),
        Point(88*positionSIZE,54*positionSIZE),
        Point(16*positionSIZE,54*positionSIZE),
        Point(16*positionSIZE,30*positionSIZE),
        Point(56*positionSIZE,30*positionSIZE),
    };
    switch (Level) {
    case 1:
        for (int i = 0; i < per_HEIGHT; i++)
            for (int j = 0; j < per_WIDTH; j++)
                Map[i][j]=tmpMap1[i][j];
        for(auto p:Path1){
            Path.push_back(p);
        }
        money=640;
        totalwave=3;
        break;
    case 2:
        for (int i = 0; i < per_HEIGHT; i++)
            for (int j = 0; j < per_WIDTH; j++)
                Map[i][j]=tmpMap2[i][j];
        for(auto p:Path2){
            Path.push_back(p);
        }
        money=720;
        totalwave=4;
        break;
    case 3:
        for (int i = 0; i < per_HEIGHT; i++)
            for (int j = 0; j < per_WIDTH; j++)
                Map[i][j]=tmpMap3[i][j];
        for(auto p:Path3){
            Path.push_back(p);
        }
        money=560;
        totalwave=5;
        break;
    default:
        break;
    }

    count=-2;
    wave=1;
    //初始化塔坑
    for (int i = 0; i < per_HEIGHT; i++)
        for (int j = 0; j < per_WIDTH; j++)
        {
            if(Map[i][j]==8)
                TposVec.push_back(new TowerPos(Point(j*imgSIZE,i*imgSIZE)));
        }


}
