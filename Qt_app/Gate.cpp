#include "Gate.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <cstdlib> //rand()
#include <QList>
#include "Player.h"
#include "gamewin.h"
#include "mainwindow.h"

extern Gamewin *game;

Gate::Gate()
{
    //Ustaw losowa pozycje po lewej stronie sceny
    setPos(rand()%650,0);
    if(this->rect().x()<50)
        setPos(x()+150,0);
    // Rysuj bramke
    setRect(0,0,50,100);

    // Polacz z timerem
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(moveDown()));

    timer->start(50);
}

void Gate::moveDown()
{

    //Lista obiektow do detekcji kolzji z graczem
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        //Jesli jednym z obiektow jest gracz zniszcz bramke
        if (typeid(*(colliding_items[i])) == typeid(Player)){

            // Usun ze sceny bramke
            scene()->removeItem(this);

            // Usun obiekt ze stosu
            delete this;

            return;
        }
    }

    //Jedz w dol
    setPos(x(),y()+8);
    if(pos().y()>600) //600 - wysokosc sceny
    {
        //Usun ze sceny
        scene()->removeItem(this);
        //Usun obiekt ze stosu
        delete this;
        qDebug()<<"Delete gate!";
    }
}
