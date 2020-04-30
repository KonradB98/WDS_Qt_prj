#include "gamewin.h"
#include "ui_gamewin.h"
#include <QDebug>
#include <QTimer>

Gamewin::Gamewin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gamewin)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    // 0---------->800(x)
    // |
    // |
    // |
    //600(y)

    ui->game->setScene(scene);
    ui->game->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->game->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->game->setFixedSize(800,600);

    // Stworz obiekt klasy Player
    player = new Player();
    connect(this,SIGNAL(passData(QList<float>)),player,SLOT(accMove(QList<float>))); //Polacz gracza z danymi z akcelerometru
    player->setRect(0,0,100,100); //Wymiary wstepne
    player->setPos(scene->width()/2-player->rect().width()/2,scene->height()-player->rect().height());//center pos
    player->setFlag(QGraphicsItem::ItemIsFocusable); //Ustaw odpowiednia flage i focus, aby mozna bylo sterowac obiektem
    player->setFocus();
    scene->addItem(player); // dodaj gracza do sceny

    //---------------Timery-------------//
    QTimer * tim1 = new QTimer();
    QObject::connect(tim1,SIGNAL(timeout()),player,SLOT(makeSpawn()));
    tim1->start(4000);
}

Gamewin::~Gamewin()
{
    delete ui;
}
//Slot odbier dane z akcelerometru od mainwindow, slot emituje sygnal dla gracza (player) ktory odbiera dane z akcelerometru
void Gamewin::getControlData(QList<float> acc_dat)
{
    emit passData(acc_dat);
}
