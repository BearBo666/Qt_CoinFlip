#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "mypushbtn.h"
#include<QPainter>
#include<QTimer>
#include<QSound>

MainScreen::MainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    //配置主场景
    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Logo.png"));
    //设置标题
    setWindowTitle("金币翻翻翻");
    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound * startMus=new QSound(":/res/TapButtonSound.wav");
    //Start按钮的实现
    MyPushBtn *startBtn=new MyPushBtn(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.32,this->height()*0.7);

    //实例化选择关卡的场景
    chooseScene=new chooseLevelScreen;
    //监听选择关卡页面的返回按钮的信号
    connect(chooseScene,&chooseLevelScreen::chooseSceneBack,this,[=](){
        //隐藏选择关卡场景，显示主场景
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());
        this->show();
    });

    //监听Start按钮的点击事件
    connect(startBtn,&MyPushBtn::clicked,[=](){
        startMus->play();
        //按钮弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延迟0.5s以便能看到动画
        QTimer::singleShot(500,this,[=](){
            //将自身隐藏
            this->hide();
            //进入到关卡选择的场景
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
            });
        });
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上的图标
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
