#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include"chooselevelscreen.h"

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = nullptr);
    ~MainScreen();

    //重写paintEvent事件 画背景图
    void paintEvent(QPaintEvent *);

    chooseLevelScreen * chooseScene=nullptr;
private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H
