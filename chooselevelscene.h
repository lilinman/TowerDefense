#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

#include "playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);//画图事件
    PlayScene *GameScene = NULL;
signals:
    //返回信号
    void StopMuisc();
    void chooseBack();
public slots:
};

#endif // CHOOSELEVELSCENE_H
