#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnImg);

    int posX; //行
    int posY; //列
    bool flag; //正反的判断

    //改变标志的方法
    void changFlag();
    QTimer * timer1;  //正面翻反面的定时器
    QTimer * timer2;  //反面翻正面的定时器
    int min=1;
    int max=8;

    //执行动画 标志
    bool isAnimation=false;

    bool isWin=false;
signals:

public slots:
};

#endif // MYCOIN_H
