#include "mycoin.h"
#include<QDebug>
MyCoin::MyCoin(QString btnImg) 
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret){
        qDebug()<<"图片加载失败！";
        return;
    }
    
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    //监听正面翻反面的信号
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果翻完了,将min重置
        if(this->min>this->max){
            this->min=1;
            isAnimation=false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果翻完了,将max重置
        if(this->min>this->max){
            this->max=8;
            isAnimation=false;
            timer2->stop();
        }
    });
}

void MyCoin::changFlag(){
    if(this->flag&&!this->isWin){
        this->flag=false;
        //开启正面翻反面的定时器
        timer1->start(30);
        isAnimation=true;
    }
    else if(!this->flag&&!this->isWin){
        this->flag=true;
        //开启反面翻正面的定时器
        timer2->start(30);
        isAnimation=true;
    }
}
