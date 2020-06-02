#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setwindow.h"
#include <QSerialPort>//Do obslugi portow szeregowych
#include "port.h"
#include "gamewin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Klasa MainWindow
 *  Klasa odpowiada za główne menu aplikacji, dziedziczy po QMainWindow. \n
 * Posiada atrybuty odpowiedzialne za wykresy, okno ustawień połączenia oraz samo urządzenie.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor parametryczny głównego okna aplikacji.
     * \param[in] parent - wskażnik rodzica ustawiony na NULL pointer.
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
      * \brief Destruktor głównego okna aplikacji.
     */
    ~MainWindow();
    //Zmienne do rysowania wykresow
    float t = 0;
    float range = 20;
    int axis = 0;
    QString os;

private slots:
    /*!
     * \brief Slot otwierający okno ustawień połączenia z mikrokontrolerem.
     */
    void on_pushButtonConnect_clicked();
    /*!
     * \brief Slot aktualizujący pasek statusowy.
     * \param[in] message - string zawierający tekst wyświetlany w pasku statusowym.
     */
    void ifReport(const QString &message);
    //Funkcja odpowiada rysowanie wykresu
    /*!
     * \brief Slot rysujący wykres w zakładce "plots".
     * \param[in] acc_dat - dane z akcelerometru w postaci listy.
     */
    void makePlot(QList<float> acc_dat);
    /*!
     * \brief Przycisk przełączający wyświetlanie na wykresie danych z osi X.
     */
    void on_pushButtonX_clicked();
    /*!
     * \brief Przycisk przełączający wyświetlanie na wykresie danych z osi Y.
    */
    void on_pushButtonY_clicked();
    /*!
     * \brief Przycisk przełączający wyświetlanie na wykresie danych z osi Z.
    */
    void on_pushButton_3_clicked();
    /*!
     * \brief Przycisk uruchamiający nową grę.
     */
    void on_pushButtonPlay_clicked();

private:
    Ui::MainWindow *ui;
    SetWindow sw;
    //SetWindow *sw;
    port device;
    //port *device;
    //Gamewin *game;

};
#endif // MAINWINDOW_H
