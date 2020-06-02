#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

/*!
 * \brief Klasa modeluje wynik gry
 * Dziedziczy po QGraphicsTextItem i posiada niezbędne atrybuty oraz funkcję do śledzenia wyniku rozgrywki.
 */
class Score: public QGraphicsTextItem{
public:
    /*!
     * \brief Konstruktor parametryczny
     * \param[in] parent - wskaźnik na rodzica ustawiony na NULL pointer.
     */
    Score(QGraphicsItem * parent=0);
    /*!
     * \brief Funkcja zwiększająca wynik rozgrywki o 1.
     */
    void increase();
    /*!
     * \brief Funkcja umożliwiająca pozyskanie aktualnego wyniku gry.
     * \return Zwraca wynik gry w postaci liczby całkowitej.
     */
    int getScore();
private:
    int score;
};

#endif // SCORE_H
