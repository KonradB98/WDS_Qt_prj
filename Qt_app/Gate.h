#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QGraphicsPixmapItem> //Do graficznej reprezentacji obiektow

/*!
 * \brief Klasa Gate
 * Klasa modeluje przeszkody obecne w postaci niebieskich bramek w grze.
 */
class Gate:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor parametryczny
     * \param[in] parent - rodzic ustawiony na NULL pointer.
     */
    Gate(QGraphicsItem *parent=NULL);
public slots:
    /*!
     * \brief Slot odpowiadający za poruszanie się przeszkody (bramki) w dół sceny.
     */
    void moveDown(); //Slot porusza bramka w dol i sprawdza kolizje z graczem
};

#endif // GATE_H
