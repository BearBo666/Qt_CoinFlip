#ifndef CHOOSELEVELSCREEN_H
#define CHOOSELEVELSCREEN_H

#include <QMainWindow>
#include"playscene.h"

class chooseLevelScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelScreen(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //游戏场景的指针
    PlayScene * playScene=NULL;
signals:
    //用于告诉主场景 点了返回
    void chooseSceneBack();
public slots:
};

#endif // CHOOSELEVELSCREEN_H
