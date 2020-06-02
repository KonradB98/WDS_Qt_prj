#include "gamewin.h"
#include "ui_gamewin.h"
#include <QDebug>
#include <QTimer>
#include <QBrush>
#include <QImage>

//extern QPointer<Gamewin> game;
//extern Gamewin *game;

Gamewin::Gamewin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gamewin)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/game_img/background.png")));
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
    //player->setRect(0,0,100,100); //Wymiary wstepne
    player->setPos(400,500);
    //player->setPos(scene->width()/2-player->rect().width()/2,scene->height()-player->rect().height());//center pos
    player->setFlag(QGraphicsItem::ItemIsFocusable); //Ustaw odpowiednia flage i focus, aby mozna bylo sterowac obiektem
    player->setFocus();
    scene->addItem(player); // dodaj gracza do sceny

    // Stworz obiekty typu "Score" i "Health" i dodaj do sceny
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+35);
    scene->addItem(health);

    //---------------Timer-------------//
    tim1 = new QTimer(this);
    QObject::connect(tim1,SIGNAL(timeout()),player,SLOT(makeSpawn()));
    tim1->start(3000);
}

Gamewin::~Gamewin()
{
    delete ui;
    delete player;
    //delete scene;
    delete score;
    delete health;
    //game.clear();
    //delete game;
    //delete this;
    //delete tim1;
}
//Slot odbier dane z akcelerometru od mainwindow, slot emituje sygnal dla gracza (player) ktory odbiera dane z akcelerometru
void Gamewin::getControlData(QList<float> acc_dat)
{
    emit passData(acc_dat);
}
