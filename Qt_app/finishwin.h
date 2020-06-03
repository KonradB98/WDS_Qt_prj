#ifndef FINISHWIN_H
#define FINISHWIN_H

#include <QDialog>

/*!
 * \file
 * \brief Definicja klasy Finishwin
 *
 * Plik zawiera definicję klasy Finishwin, która jest klasą pochodną QDialog.
 */

namespace Ui {
class Finishwin;
}
/*!
 * \brief Klasa Finishwin
 * Klasa modeluje wygląd okna, które pokazywane jest po osiągnięciu przez gracza wartości życia równą 0.
 */
class Finishwin : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor klasy Finishwin
     * \param[in] parent - wskaźnik na rodzica ustawiony na NULL.
     */
    explicit Finishwin(QWidget *parent = nullptr);
    /*!
     * \brief Destruktor klasy Finishwin
     */
    ~Finishwin();

private slots:

    /*!
     * \brief Slot on_pushButtonClose_clicked
     * Po wciśnięciu przycisku "Close", okno zostaje zamknięte oraz zostaje usunięta rozgrywka.
     */
    void on_pushButtonClose_clicked();
    /*!
     * \brief Slot gameOver_slt
     * \param[in] score - wynik rozgrywki w postaci liczby całkowitej.
     */
    void gameOver_slt(int score);

private:
    Ui::Finishwin *ui;
};

#endif // FINISHWIN_H
