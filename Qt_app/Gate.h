#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsPixmapItem> //Do graficznej reprezentacji obiektow

/*!
 * \file
 * \brief Definicja klasy Gate
 *
 * Plik zawiera definicję klasy Gate, która jest klasą pochodną QObject oraz QGraphicsPixmapItem.
 */

/*!
 * \brief Klasa Gate
 * Klasa modeluje przeszkody obecne w postaci niebieskich bramek w grze.
 */
class Gate:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy Gate
     * \param[in] parent - rodzic ustawiony na NULL pointer.
     */
    Gate(QGraphicsItem *parent=NULL);
public slots:
    /*!
     * \brief Slot moveDown
     * Slot odpowiadający za poruszanie się przeszkody (bramki) w dół sceny.
     */
    void moveDown(); //Slot porusza bramka w dol i sprawdza kolizje z
signals:
    void sigGameOver(int scr);
};

#endif // GATE_H
