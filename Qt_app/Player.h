#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

/*!
 * \file
 * \brief Definicja klasy Player
 *
 * Plik zawiera definicję klasy Player, która jest klasą pochodną QObject oraz QGraphicsPixmapItem.
 */

/*!
 * \brief Klasa Player
 * Klasa modeluje postać gracza. \n
 * Umożliwia sterowanie graczem przy pomocy danych z akcelerometru oraz tworzenie przeszkód.
 */
class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy Player
     * \param[in] parent - ustawienie rodzica na NULL.
     */
    Player(QGraphicsItem *parent = NULL);
public slots:
    /*!
     * \brief Slot accMove
     * Slot umożliwiający poruszanie postacią przy pomocy danych z akcelerometru.
     * \param[in] acc_dat - dane z akcelerometru w postaci listy
     */
    void accMove(QList<float> acc_dat); //Slot porusza postacia przy pomocy danych z akcelerometru

    /*!
     * \brief Slot makeSpawn
     * Slot cyklicznie tworzy przeszkody dla gracza (niebieskie bramki)
     */
    void makeSpawn(); //Slot spawnuje bramki (przeszkody)
};

#endif // PLAYER_H
