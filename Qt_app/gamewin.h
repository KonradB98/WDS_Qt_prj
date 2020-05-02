#ifndef GAMEWIN_H
#define GAMEWIN_H

#include <QDialog>
#include "Player.h"
#include <QGraphicsScene>

namespace Ui {
class Gamewin;
}

class Gamewin : public QDialog
{
    Q_OBJECT

public:
    explicit Gamewin(QWidget *parent = nullptr);
    ~Gamewin();

private:
    Ui::Gamewin *ui;
public:
     QGraphicsScene * scene;
     Player * player;
public slots:
    void getControlData(QList<float> acc_dat); //Odbiera dane z akcelerometru od okna "mainwindow"
signals:
    void passData(QList<float> acc_dat); // Emitwany po odebraniu danych z akcelerometru w slocie  getControlData()
};

#endif // GAMEWIN_H
