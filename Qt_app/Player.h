#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

/*!
 * \brief Klasa Player
 * Klasa zawiera konstruktor oraz sloty potrzebne do interakcji z postacią (poruszanie oraz tworzenie przeszkód)
 */
class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor parametryczny
     * \param [in] parent - ustawienie rodzica na NULL pointer
     */
    Player(QGraphicsItem *parent = NULL);
public slots:
    /*!
     * \brief Slot umożliwiający poruszanie postacią przy pomocy
     * \param [in] acc_dat - dane z akcelerometru w postaci listy
     */
    void accMove(QList<float> acc_dat); //Slot porusza postacia przy pomocy danych z akcelerometru

    /*!
     * \brief Slot tworzący cyklicznie przeszkody dla gracza (niebieskie bramki)
     */
    void makeSpawn(); //Slot spawnuje bramki (przeszkody)
};

#endif // PLAYER_H
