#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class Player:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
public slots:
    void moveEvent(QKeyEvent * event);
    void accMove(QList<float> acc_dat);
};

#endif // PLAYER_H
