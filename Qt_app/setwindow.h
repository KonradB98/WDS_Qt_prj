#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>

/*!
 * \file
 * \brief Definicja klasy SetWindow
 *
 * Plik zawiera definicję klasy SetWindow, która jest klasą pochodną QMainWindow.
 */

namespace Ui {
class SetWindow;
}
/*!
 * \brief Klasa modeluje wygląd okna ustawień
 * Umożliwia za pomocą poszczególnych przycisków na wyszukanie urządzenia oraz nawiązanie lub zakończenie połączenia.
 */
class SetWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor klasy SetWindow
     * \param[in] parent - wskaźnik rodzica ustawiony na nullptr.
     */
    explicit SetWindow(QWidget *parent = nullptr);
    /*!
      * \brief Destruktor klasy SetWindow
     */
    ~SetWindow();
private slots:
    //---------Przyciski------------//
    /*!
     * \brief Slot on_pushButtonSearch_clicked
     * Przycisk "Search" umożliwiający przeszukanie urządzeń podłączonych do komputera przez port szeregowy COM.
     * Umieszcza nazwy znalezionych urządzeń w combobox'ie.
     */
    void on_pushButtonSearch_clicked();
    /*!
     * \brief Slot on_pushButtonConnect_clicked
     * Przycisk "Connect" umożliwiający podłączenie mikrokontrolera do aplikacji.
     */
    void on_pushButtonConnect_clicked();
    /*!
     * \brief Slot on_pushButtonDisconnect_clicked
     * Przycisk "Disconnect" umożliwiający odłączenie mikrokontrolera od aplikacji.
     */
    void on_pushButtonDisconnect_clicked();
private:
    Ui::SetWindow *ui;
    /*!
     * \brief Funkcja wpisujaca logi do pola tekstowego.
     * \param[in] message - treść komunikatu w postaci QString'a.
     */
    void addLogs(QString message);//Metoda wpisujaca logi do pola tekstowego
signals:
    /*!
     * \brief Sygnał setConnect
     * Sygnał emitowany po wcisnieciu przycisku "Connect".
     */
    void setConnect(QString); //Sygnal emitowany po wcisnieciu przycisku "Connect"
    /*!
     * \brief Sygnał setConnect
     * Sygnał emitowany po wcisnieciu przycisku "Disconnect".
     */
    void closeConnect(); //Sygnal emitowany po wcisnieciu przycisku "Disconnect"
};

#endif // SETWINDOW_H
