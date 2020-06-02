#include "Health.h"
#include <QFont>
#include <QtWidgets>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    //Inicjuj wartosc zdrowia na 3
    health = 3;

    // Rysuj text
    //setPlainText(QString("Health: ❤️ ") + QString::number(health)); // Health: 3
    setPlainText(QString(" 💗 ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("OldEnglish",22));
}

void Health::decrease(){
    --health;
    setPlainText(QString(" 💗 ") + QString::number(health)); // Health: 2
}

int Health::getHealth(){
    return health;
}
