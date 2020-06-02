#ifndef GAMEWIN_H
#define GAMEWIN_H

#include <QDialog>
#include "Player.h"
#include <QGraphicsScene>
#include "Score.h"
#include "Health.h"
#include <QPointer>
#include <QTimer>


namespace Ui {
class Gamewin;
}

/*!
 * \brief Klasa Gamewindow
 * Klasa modeluje całą rozgrywkę. \n
 * Posiada wszystkie obiekty występujące w grze.
 */
class Gamewin : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor parametryczny
     * \param [in] parent - rodzic ustawiony na NULL pointer.
     */
    explicit Gamewin(QWidget *parent = nullptr);
    ~Gamewin();

private:
    Ui::Gamewin *ui;
public:
    /*!
      * \brief Wskaźnik na obiekt typu QGraphicsScene do stworzenia sceny rozgrywki.
      */
     QGraphicsScene *scene;
     /*!
      * \brief Wskaźnik na obiekt typu Player
      * Obiekt jest tworzony dynamicznie i odpowiada za postać gracza na scenie.
      */
     Player *player;
     //QPointer<Player> player;
     /*!
      * \brief Wskaźnik na obiekt typu Score
      * Obiekt tworzony dynamicznie odpowiadający za aktualny wynik gry.
      */
     Score *score;
     /*!
      * \brief Wskaźnik na obiekt typu Health
      * Obiekt przechowuje informacje na temat zdrowia gracza.
      */
     Health *health;
     /*!
      * \brief Wskaźnik na obiekt typu QTimer
      * Obiekt odpowiedzialny za timer cyklicznie tworzący przeszkody w grze.
      */
     QTimer *tim1;
public slots:
     /*!
     * \brief Slot umożliwiający odbiór danych z akcelerometru.
     * \param [in] acc_dat - dane z akcelerometru w postaci listy.
     */
    void getControlData(QList<float> acc_dat); //Odbiera dane z akcelerometru od okna "mainwindow"
signals:
    /*!
     * \brief Sygnał emitowany po odebraniu danych przez obiekt klasy gamewindow.
     * \param [in] acc_dat - dane z akcelerometru w postaci listy.
     * Sygnał odbierany jest przez obiekt klasy Player, aby umożliwić poruszanie graczem za pomocą danych z akcelerometru.
     */
    void passData(QList<float> acc_dat); // Emitwany po odebraniu danych z akcelerometru w slocie  getControlData()

};

#endif // GAMEWIN_H
