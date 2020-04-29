#include "gamewin.h"
#include "ui_gamewin.h"
#include <QDebug>

Gamewin::Gamewin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gamewin)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);

    ui->game->setScene(scene);
    ui->game->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->game->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->game->setFixedSize(800,600);

    // create the player
    player = new Player();
    connect(this,SIGNAL(passData(QList<float>)),player,SLOT(accMove(QList<float>)));
    player->setRect(0,0,100,100); // change the rect from 0x0 (default) to 100x100 pixels
    player->setPos(400,500); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the player to the scene
    scene->addItem(player);
}

Gamewin::~Gamewin()
{
    delete ui;
}

void Gamewin::getControlData(QList<float> acc_dat)
{
    emit passData(acc_dat);
}
