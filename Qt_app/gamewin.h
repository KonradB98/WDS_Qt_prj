#ifndef GAMEWIN_H
#define GAMEWIN_H

#include <QDialog>
#include "Player.h"
#include <QGraphicsScene>
#include "Score.h"
#include "Health.h"
#include <QPointer>
#include <QTimer>

/*!
 * \file
 * \brief Definicja klasy Gamewin
 *
 * Plik zawiera definicję klasy Gamewin, która jest klasą pochodną QDialog.
 */

namespace Ui {
class Gamewin;
}

/*!
 * \brief Klasa Gamewindow
 * Klasa modeluje całą rozgrywkę. \n
 * Posiada wskaźniki na wszystkie obiekty występujące w grze. Konstruktor inicjalizuje obiekty i wstawia je na scenę.
 */
class Gamewin : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor obiektu klasy Gamewin
     * \param[in] parent - rodzic ustawiony na NULL.
     */
    explicit Gamewin(QWidget *parent = nullptr);
    /*!
     * \brief Destruktor obiektu klasy Gamewin
     */
    ~Gamewin();

private:
    Ui::Gamewin *ui;
public:
    /*!
      * \brief Wskaźnik na obiekt typu QGraphicsScene
      *  Jest tworzony w konstruktorze i zawiera elementy gry takie jak gracz, wynik oraz życie.
      */
     QGraphicsScene *scene;
     /*!
      * \brief Wskaźnik na obiekt typu Player
      * Obiekt jest tworzony dynamicznie w konstruktorze i odpowiada za postać gracza na scenie.
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
     * \brief Slot odbierający dane
     * Umożliwia on odbiór danych z akcelerometru orez przesłanie ich dalej do obiektu Player.
     * \param[in] acc_dat - dane z akcelerometru w postaci listy.
     */
    void getControlData(QList<float> acc_dat); //Odbiera dane z akcelerometru od okna "mainwindow"
signals:
    /*!
     * \brief Sygnał emitowany po odebraniu danych
     * \param [in] acc_dat - dane z akcelerometru w postaci listy.
     * Sygnał emitowany jest po odbiorze danych przez slot getControlData.
     * Sygnał odbierany jest przez obiekt klasy Player, aby umożliwić poruszanie graczem za pomocą danych z akcelerometru.
     */
    void passData(QList<float> acc_dat); // Emitwany po odebraniu danych z akcelerometru w slocie  getControlData()
};

#endif // GAMEWIN_H
