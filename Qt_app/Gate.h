#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsRectItem>

class Gate:public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Gate();
public slots:
    void moveDown();
};

#endif // GATE_H
