#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>
//#include <QSerialPort>//Do obslugi portow szeregowych
//#include <QByteArray>
//#include "port.h"

namespace Ui {
class SetWindow;
}
/*!
 * \brief Klasa modeluje wygląd okna ustawień
 */
class SetWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetWindow(QWidget *parent = nullptr);
    ~SetWindow();
private slots:
    //---------Przyciski------------//
    /*!
     * \brief Przycisk umożliwiający przeszukanie urządzeń podłączonych do komputera przez port szeregowy COM.
     * Umieszcza nazwy znalezionych urządzeń w combobox'ie.
     */
    void on_pushButtonSearch_clicked();
    /*!
     * \brief Przycisk umożliwiający podłączenie mikrokontrolera do aplikacji.
     */
    void on_pushButtonConnect_clicked();
    /*!
     * \brief Przycisk umożliwiający odłączenie mikrokontrolera od aplikacji.
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
     * \brief Sygnal emitowany po wcisnieciu przycisku "Connect".
     */
    void setConnect(QString); //Sygnal emitowany po wcisnieciu przycisku "Connect"
    /*!
     * \brief Sygnal emitowany po wcisnieciu przycisku "Disconnect".
     */
    void closeConnect(); //Sygnal emitowany po wcisnieciu przycisku "Disconnect"
};

#endif // SETWINDOW_H
