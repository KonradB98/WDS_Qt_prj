#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem *parent = NULL);
public slots:
    void accMove(QList<float> acc_dat); //Slot porusza postacia przy pomocy danych z akcelerometru

    void makeSpawn(); //Slot spawnuje bramki (przeszkody)
};

#endif // PLAYER_H
