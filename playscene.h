#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelNum);
    int levelIndex;  //记录所选关卡

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    int gameArray[4][4]; //二维数组 维护关卡的具体数据
    MyCoin * coins[4][4]; //金币数组 用于保存金币属性
    bool isWin=false; //判断是否胜利的标志
signals:
    void chooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
