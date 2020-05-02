#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsPixmapItem> //Do graficznej reprezentacji obiektow

class Gate:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Gate(QGraphicsItem *parent=NULL);
public slots:
    void moveDown(); //Slot porusza bramka w dol i sprawdza kolizje z graczem
};

#endif // GATE_H
