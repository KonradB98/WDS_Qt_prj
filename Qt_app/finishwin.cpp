#include "finishwin.h"
#include "ui_finishwin.h"
#include "gamewin.h"

extern Gamewin *game;

Finishwin::Finishwin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finishwin)
{
    ui->setupUi(this);
}

Finishwin::~Finishwin()
{
    delete ui;
    //delete game;
}


void Finishwin::on_pushButtonClose_clicked()
{
    this->close();
    delete game;
    delete this;
}

void Finishwin::gameOver_slt(int score)
{
    ui->mylcd->display(score);
}



