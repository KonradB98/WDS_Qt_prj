#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setwindow.h"
#include <QSerialPort>//Do obslugi portow szeregowych
#include "port.h"
#include "gamewin.h"

/*!
 * \file
 * \brief Definicja klasy MainWindow
 *
 * Plik zawiera definicję klasy MainWindow, która jest klasą pochodną QMainWindow.
 */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Klasa MainWindow
 *  Klasa odpowiada za główne menu aplikacji oraz dziedziczy po QMainWindow. \n
 * Posiada atrybuty odpowiedzialne za wykresy, okno ustawień połączenia oraz samo urządzenie.
 * Umożliwa również dynamiczne stworzenie obiektu typu Gamewindow po wciśnięciu przycisku "Play".
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor głównego okna aplikacji.
     * \param[in] parent - wskaźnik rodzica ustawiony na nullptr.
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief Destruktor głównego okna aplikacji.
     */
    ~MainWindow();
    //Zmienne do rysowania wykresow
    /*!
     * \brief Atrybut t
     * Zmienna odpowiedzialna za czas (oś X) wykresu podawany w sekundach.
     */
    float t;
    /*!
     * \brief Atrybut range
     * Zmienna odpowiedzialna za zakres czasu symulacji na wykresie podawany w sekundach.
     */
    float range;
    /*!
     * \brief Atrybut axis
     * Zmienna pomocnicza odpowiedzialna za wybór osi, z której dane prezentowane są na wykresie. axis = 0 oznacza oś X,
     * axis = 1 oznacza oś Y, axis = 2 oznacza oś Z.
     */
    int axis;
    /*!
     * \brief Atrybut os
     * Zmienna typu QString używana do opisu osi Y wykresu. Jej wartość przypisywana jest w momencie wciśnięcia przycisku
     * zmieniającego dane prezentowane na wykresie. W konstruktorze przypisywana jest wartość os = "X"
     */
    QString os;

private slots:
    /*!
     * \brief Slot dla przycisku "Connect"
     * Slot otwiera okno ustawień połączenia aplikacji z mikrokontrolerem.
     */
    void on_pushButtonConnect_clicked();
    /*!
     * \brief Slot aktualizujący pasek statusowy.
     * \param[in] message - Qstring zawierający tekst wyświetlany w pasku statusowym.
     * Jego wartość jest zmieniana podczas połączenia lub rozłączenia aplikacji z mikrokontrolerem.
     */
    void ifReport(const QString &message);
    //Funkcja odpowiada rysowanie wykresu
    /*!
     * \brief Slot makePlot
     * Slot odpowiedzialny za rysowanie wykres w zakładce "plots".
     * \param[in] acc_dat - dane z akcelerometru w postaci listy floatów w jednostce g.
     */
    void makePlot(QList<float> acc_dat);
    /*!
     * \brief Slot on_pushButtonX_clicked
     * Przycisk przełączający wyświetlanie na wykresie danych z osi X.
     */
    void on_pushButtonX_clicked();
    /*!
     * \brief Slot on_pushButtonY_clicked
     * Przycisk przełączający wyświetlanie na wykresie danych z osi Y.
    */
    void on_pushButtonY_clicked();
    /*!
     * \brief Slot on_pushButton_3_clicked
     * Przycisk przełączający wyświetlanie na wykresie danych z osi Z.
    */
    void on_pushButton_3_clicked();
    /*!
     * \brief Slot on_pushButtonPlay_clicked
     * Przycisk inicjalizujący nową grę.
     */
    void on_pushButtonPlay_clicked();

private:
    Ui::MainWindow *ui;
    /*!
     * \brief Atrybut sw
     * Zmienna typu SetWindow odpowiedzialna za okno konfiguracji połączenia.
     */
    SetWindow sw;
    //SetWindow *sw;
    /*!
     * \brief Atrybut device
     * Zmienna typu port odpowiedzialna za przetwarzanie danych z mikrokontrolera.
     */
    port device;
    //port *device;
    //Gamewin *game;

};
#endif // MAINWINDOW_H
