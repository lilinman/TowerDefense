#ifndef BASETOWER_H
#define BASETOWER_H


#include<QString>
#include "point.h"
#include"object.h"
#include<QPainter>
#include<vector>
#include<bullet.h>
#include <QMediaPlayer>
using namespace std;

//防御塔基类 抽象类 继承自object
class BaseTower:public Object
{
public:
    BaseTower(int x,int y);

protected:
    QMediaPlayer *player=new QMediaPlayer;   //发出子弹时的音效
    int price;                               //初始价格
    bool showUpgrade=true;                   //是否可升级
    bool isbulleting=false;                  //正在发出子弹（实现动画效果）
    int sellPrice;                           //拆除可得金币
    int upgradePrice;                        //升级所需金币
    int Hp=10;                               //防御塔生命值
    int TowerLevel;                          //等级
    int bulletId;                            //子弹序号
    int damege;                              //子弹伤害
    int range;                               //射程
    double bulletspeed;                      //子弹打到敌人所需单位时间
    double ebuspeed=0;                       //子弹移动速度 结合bulletspped计算每次移动距离
    int isdeleted=0;                         //用于实现消失效果
    Enemy *target=NULL;                      //防御塔目标敌人（和子弹目标敌人不同）
    Bullet *bullet=NULL;                     //子弹
    QString upgradePath;                     //可升级的图片路径
    QString NOupgradePath;                   //不可升级的图片路径
    QString sellPath;                        //拆塔的图片路径

public:
    virtual void bulletingSound() = 0;       //播放子弹音效 子类实现
    virtual void upGrade() = 0;              //不同的炮塔实现不同的升级功能
    virtual void attack(vector<Enemy *>) = 0;//攻击方式
    virtual void set_Bullet(int,int,bool) = 0;//实现不同子弹
    void Draw(QPainter &painter);             //基类实现画图函数
    //系列get/set函数
    int get_isdeleted()const;
    void set_isdeleted(int);
    void set_Target(Enemy *t);
    int get_TowerLevel() const;
    void set_TowerLevel(int );
    int get_Hp()const;
    void set_Hp(int);
    Enemy *get_Target() const;
    int get_Damege() const;
    void set_Damege(int) ;
    int get_Range() const;
    void set_Range(int);
    int get_BulletID()const;
    void set_BulletID(int);
    void set_isbulleting(bool);
    bool get_isbulleting()const;
    Bullet * get_Bullet()const;
    int get_SellPrice()const;
    int get_UpgradePrice()const;
    int get_Price()const;
    bool get_ShowUpgrade()const;
    void set_ShowUpgrade(bool);
    QString get_upPath() const;
    QString get_NoupPath() const;
    QString get_sellPath() const;
    virtual ~BaseTower();

};
#endif // BASETOWER_H
