#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

/*!
 * \brief Klasa Health
 * Klasa odpowiada za atrybut gracza jakim jest zdrowie.
 */
class Health: public QGraphicsTextItem{
public:
    /*!
     * \brief Konstruktor parametryczny
     * \param[in] parent - rodzic obiektu ustawiony na NULL pointer.
     */
    Health(QGraphicsItem * parent=0);
    /*!
     * \brief Funkcja odpowiada za pomniejszenie wyniku o 1.
     */
    void decrease();
    /*!
     * \brief Funkcja umożliwia pozyskanie atrybutu health.
     * \return zwraca ilość zdrowia gracza w postaci liczby całkowitej.
     */
    int getHealth();
private:
    /*!
     * \brief Atrybut odpowiadający za ilość zdrowia gracza.
     */
    int health;
};

#endif // HEALTH_H
