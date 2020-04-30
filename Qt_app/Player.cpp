#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "Gate.h"

Player::Player(QGraphicsItem *parent): QGraphicsRectItem(parent){

}

void Player::moveEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + this->rect().width() < 800)
        setPos(x()+10,y());
    }
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
        if (pos().x() + this->rect().width() < 800)
        setPos(x()+10,y());
    }
    qDebug()<<acc_dat;
}
void Player::makeSpawn()
{
    Gate *gate = new Gate();
    scene()->addItem(gate);
}
