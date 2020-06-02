#include "mainwindow.h"
#include <QApplication>

/*!
 * \file
 * \brief Zawiera funkcję główną programu.
 */

/*!
 * \brief Tworzy główne okno aplikacji oraz inicjalizuje pętlę obsługi zdarzeń.
 *
 * Funkcja odpowiada za utworzenie obiektów klasy "QApplication" i "MainWindow".
 * Nstępnie uruchamia pętlę obsługi zdarzeń dla obiektu aplikacji.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
