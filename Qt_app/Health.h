#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

/*!
 * \file
 * \brief Definicja klasy Health
 *
 * Plik zawiera definicję klasy Health, która jest klasą pochodną QGraphicsTextItem.
 */

/*!
 * \brief Klasa Health
 * Klasa odpowiada za atrybut gry jakim jest zdrowie narciarza.
 */
class Health: public QGraphicsTextItem{
public:
    /*!
     * \brief Konstruktor klasy Health
     * \param[in] parent - rodzic obiektu ustawiony na NULL pointer.
     */
    Health(QGraphicsItem * parent=0);
    /*!
     * \brief Funkcja decrease
     * Funkcja odpowiada za pomniejszenie wyniku o 1. Wywoływana jest po uderzeniu gracza w bramkę.
     */
    void decrease();
    /*!
     * \brief Funkcja getHealth
     * Funkcja umożliwia pozyskanie atrybutu health.
     * \return Zwraca ilość zdrowia gracza w postaci liczby całkowitej.
     */
    int getHealth();
private:
    /*!
     * \brief Atrybut health
     * Atrybut odpowiadający za ilość zdrowia gracza.
     */
    int health;
};

#endif // HEALTH_H
