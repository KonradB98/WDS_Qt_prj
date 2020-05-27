#include "Gate.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <cstdlib> //rand()
#include <QList>
#include "Player.h"
#include "gamewin.h"
#include "mainwindow.h"
#include <QThread>

extern Gamewin *game;// Sprawdzanie kolizji w moveDown()
//extern QPointer<Gamewin> game;

Gate::Gate(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    //Ustaw losowa pozycje po lewej stronie sceny
    int rdn_pos = rand()%690;
    if(rdn_pos<10)
        rdn_pos +=100;
    setPos(rdn_pos,0);
    //Dodaj grafike z zasobowego folderu
    setPixmap(QPixmap(":/game_img/gt1.png"));
    // Polacz z timerem
    QTimer * timer = new QTimer(this);
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
            // zmniejsz wartosc zdrowia w przypadku kolizji
            game->health->decrease();
            // Usun ze sceny bramke
            scene()->removeItem(this);
            if(game->health->getHealth()==0){
                QThread::msleep(2000);
                delete game;
            }
            // Usun obiekt ze stosu
            delete this;

            return;
        }
    }

    //Jedz w dol
    setPos(x(),y()+6);
    if(pos().y()>600) //600 - wysokosc sceny
    {
        //powieksz wynik gry
        game->score->increase();
        //Usun ze sceny
        scene()->removeItem(this);
        //Usun obiekt ze stosu
        delete this;
       // qDebug()<<"Delete gate!";
    }
}
