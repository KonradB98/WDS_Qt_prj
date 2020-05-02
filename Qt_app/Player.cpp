#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "Gate.h"

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    //Ustaw grafike
    setPixmap(QPixmap(":/game_img/plr.png"));

}
void Player::accMove(QList<float> acc_dat)
{
    const float Threshold = 0.5;
    float x_d = acc_dat.at(0);
    if(x_d>Threshold){
        if (pos().x() > 0)
        setPos(x()-10,y());
    }
    else if (x_d<-Threshold){
        if (pos().x() + 100< 800)
        setPos(x()+10,y());
    }
    //qDebug()<<acc_dat;
}
void Player::makeSpawn()
{
    Gate *gate = new Gate();
    scene()->addItem(gate);
}
