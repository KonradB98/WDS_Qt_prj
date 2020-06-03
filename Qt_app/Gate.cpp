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
#include "finishwin.h"

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
            if(game->health->getHealth()>0)
                game->health->decrease();
            // Usun ze sceny bramke
            if(game->health->getHealth()==0){
                game->tim1->stop();
                Finishwin *window = new Finishwin;
                connect(this,SIGNAL(sigGameOver(int)),window,SLOT(gameOver_slt(int)));
                int pts = game->score->getScore();
                emit sigGameOver(pts);
                window->show();
               // qDebug() << game->score->getScore();
                //QThread::msleep(2000);
                //delete game;
            }

            scene()->removeItem(this);

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
        if(game->health->getHealth()>0)
            game->score->increase();
        //Usun ze sceny
        scene()->removeItem(this);
        //Usun obiekt ze stosu
        delete this;
       // qDebug()<<"Delete gate!";
    }

}
