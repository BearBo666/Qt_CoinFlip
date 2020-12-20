#include "chooselevelscreen.h"
#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbtn.h"
#include<QTimer>
#include<QLabel>
#include<QSound>

chooseLevelScreen::chooseLevelScreen(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Logo.png"));
    //设置标题
    setWindowTitle("选择关卡");
    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu= bar->addMenu("开始");

    //创建退出的菜单项
    QAction * quitAction= startMenu->addAction("退出");

    //点击退出，退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //准备返回音效
    QSound * backMus=new QSound(":/res/BackButtonSound.wav");
    //返回按钮
    MyPushBtn * backBtn=new MyPushBtn(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //点击返回
    connect(backBtn,&MyPushBtn::clicked,[=](){
        backMus->play();
        emit this->chooseSceneBack();
    });

    //创建关卡的按钮
    for (int i=0;i<20;i++) {
        MyPushBtn * menuBtn=new MyPushBtn(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,150+i/4*70);

        connect(menuBtn,&MyPushBtn::clicked,[=](){

             //进入游戏场景
             this->hide();
             playScene=new PlayScene(i+1);
             playScene->setGeometry(this->geometry());
             playScene->show();
             connect(playScene,&PlayScene::chooseSceneBack,[=](){
                 this->setGeometry(playScene->geometry());
                 this->show();
                 delete playScene;
                 playScene=nullptr;
             });
        });

        //设置关卡按钮上的数字
        QLabel * label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height()); //设置固定大小
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,150+i/4*70);  //移动
        label->setAlignment(Qt::AlignCenter); //设置对齐方式
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//对标签设置鼠标击穿事件，不然标签会覆盖按钮
    }
}

void chooseLevelScreen::paintEvent(QPaintEvent *){
    //设置背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //设置标题图片
    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()-pix.width(),30,pix.width(),pix.height(),pix);
}
