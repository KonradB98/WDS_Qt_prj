#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

/*!
 * \file
 * \brief Definicja klasy Score
 *
 * Plik zawiera definicję klasy Score, która jest klasą pochodną QGraphicsTextItem.
 */

/*!
 * \brief Klasa modeluje wynik gry
 * Dziedziczy po QGraphicsTextItem i posiada niezbędne atrybuty oraz funkcję do śledzenia wyniku rozgrywki.
 */
class Score: public QGraphicsTextItem{
public:
    /*!
     * \brief Konstruktor klasy Score
     * \param[in] parent - wskaźnik na rodzica ustawiony na 0.
     */
    Score(QGraphicsItem * parent=0);
    /*!
     * \brief Funkcja increase
     * Funkcja zwiększająca wynik rozgrywki o 1.
     */
    void increase();
    /*!
     * \brief Funkcja getScore
     * \return Zwraca wynik gry w postaci liczby całkowitej.
     * Funkcja umożliwiająca pozyskanie aktualnego wyniku gry.
     */
    int getScore();
private:
    /*!
     * \brief Atrybut score
     * Zmienna przechowująca aktualny wynik rozgrywki.
     */
    int score;
};

#endif // SCORE_H
