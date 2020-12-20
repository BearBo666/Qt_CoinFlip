#ifndef MYPUSHBTN_H
#define MYPUSHBTN_H

#include <QPushButton>

class MyPushBtn : public QPushButton
{
    Q_OBJECT
public:
    //构造函数 参数：正常显示的图片的路径 按下后显示的图片的路径
    MyPushBtn(QString normalImg,QString pressImg="");
    //保存用户传入的默认显示路径，以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    //弹跳的特效
    void zoom1(); // 向下跳
    void zoom2(); // 向上跳

    //重写按钮的按下与释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYPUSHBTN_H
