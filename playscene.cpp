#include "playscene.h"

#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include"mypushbtn.h"
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
PlayScene::PlayScene(int levelNum){
    this->levelIndex=levelNum;

    //初始化游戏场景
    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Logo.png"));
    //设置标题
    setWindowTitle("金币翻翻翻");
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

    //胜利图片的初始化
    QLabel * winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());
    //胜利音效的加载
    QSound * winMus=new QSound(":/res/LevelWinSound.wav");

    //准备返回按钮的点击音效
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

    //创建当前所在关卡的文本
    QLabel * label=new QLabel;
    label->setParent(this);
    //给文本添加字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str =QString("Level:%1").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str);
    label->setGeometry(30,this->height()-60,120,50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    //准备金币的翻转音效
    QSound * flipMus=new QSound(":/res/ConFlipSound.wav");
    //显示金币背景图案
    for (int i=0;i<4;i++) {        //行
        for (int j=0;j<4;j++) {    //列
            //绘制背景图片
            QLabel * label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            //创建金币
            QString str;
            if(this->gameArray[i][j]==1){
                //此处现实金币
                str=":/res/Coin0001.png";
            }else {
                //此处实现银币
                str=":/res/Coin0008.png";
            }

            //生成金币
            MyCoin * coin =new MyCoin(str);
            //给金币属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j]; //1正0反
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //将金币放入到金币的二维数组中 以便后期维护
            coins[i][j]=coin;

            //点击金币,进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                if(!this->isWin){
                    //如果没有在执行翻转动画,则翻面
                    if(coin->isAnimation==false){
                        flipMus->play();
                        coin->changFlag();
                        this->gameArray[i][j]=!this->gameArray[i][j];
                    };
                    //延时一段时间再翻转周围金币
                    QTimer::singleShot(300,this,[=](){
                        //右侧金币翻转
                        if(coin->posX<3&&coins[i+1][j]->isAnimation==false){
                            flipMus->play();
                            coins[i+1][j]->changFlag();
                            this->gameArray[i+1][j]=!this->gameArray[i+1][j];
                        };
                        //左侧金币翻转
                        if(coin->posX>0&&coins[i-1][j]->isAnimation==false){
                            flipMus->play();
                            coins[i-1][j]->changFlag();
                            this->gameArray[i-1][j]=!this->gameArray[i-1][j];
                        };
                        //上侧金币翻转
                        if(coin->posY>0&&coins[i][j-1]->isAnimation==false){
                            flipMus->play();
                            coins[i][j-1]->changFlag();
                            this->gameArray[i][j-1]=!this->gameArray[i][j-1];
                        };
                        //下侧金币翻转
                        if(coin->posY<3&&coins[i][j+1]->isAnimation==false){
                            flipMus->play();
                            coins[i][j+1]->changFlag();
                            this->gameArray[i][j+1]=!this->gameArray[i][j+1];
                        };

                        //判断是否胜利
                        this->isWin=true;
                        for (int m=0;m<4;m++) {
                            for (int n=0;n<4;n++) {
                                if(this->gameArray[m][n]==0){

                                    this->isWin=false;
                                    break;
                                }

                            }
                        }
                        if(this->isWin==true){

                            //将每个金币的胜利标志改为true,再次点击将不执行操作
                            for (int i=0;i<4;i++) {
                                for (int j=0;j<4;j++) {
                                    this->coins[i][j]->isWin=true;
                                }
                            }

                            //播放胜利音效
                            winMus->play();

                            //将胜利的图片移动下来
                            QPropertyAnimation * animation=new QPropertyAnimation(winLabel,"geometry");
                            //设置时间间隔
                            animation->setDuration(1000);
                            //设置开始位置
                            animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                            //设置结束位置
                            animation->setEndValue(QRect(winLabel->x(),winLabel->y()+164,winLabel->width(),winLabel->height()));
                            //设置返回曲线
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            animation->start();
                    }
                });
                }
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
