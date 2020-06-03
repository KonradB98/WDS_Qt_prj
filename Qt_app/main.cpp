#include "mainwindow.h"
#include <QApplication>

/*!
 * \mainpage Gra interaktywna -- Narciarz
 *
 * \section etykieta-opis Opis ogólny
 * Gra polega na takim sterowaniu tytułowym narciarzem, aby omijał on przeszkody (bramki) spadające w dół ekranu. \n
 * Za każdym razem kiedy postać uderzy w przeszkodę, wartość życia narciarza ulega pomniejszeniu o jeden. Punktacja
 * liczona jest wprost proporcjonalnie do ominiętych bramek tj. ilość bramek, które nie dotknięte przez narciarza znikną
 * z ekranu gry. Gra kończy się w momencie kiedy główna postać trzykrotnie uderzy w bramki. Po tym zdarzeniu wyświetlane
 * jest nowe okno informujące o wyniku zakończonej rozgrywki. \n
 * Sterowanie narciarzem odbywa się za pomocą danych z akcelerometru umieszczonego na płytce rozwojowej.
 *
 * \section etykieta-main Menu
 * Okno główne aplikacji składa się z dwóch przycisków odpowiadających za konfigurację połączenia z mikrokontrolerem (przycisk "Connection") oraz
 * za rozpoczęcie nowej gry (przycisk "Play"). \n
 * W zakładce "Plots" znajduje się pole, na którym wyświetlany jest wykres przyspieszenia względem konkretnej osi od czasu.
 * Oś wybierana jest przy pomocy przycisków znajdujących się w górnej części zakładki.
 *
 * \section etykieta-game Okno gry
 * Okno gry otwierane jest po wciśnięciu przycisku "Play" znajdującym się w głównym menu aplikacji. \n
 * Otwarcie tego okna powoduje inicjalizację gry oraz wszystkich jej elementów takich jak scena, gracz, życie, punkty i timer.
 * Okno oraz jego zawartość kasowana jest w momencie osiągnięcia przez gracza wartości życia równej 0 lub zamknięciu okna
 * przez wciśnięcie czerwonego krzyżyka w górnej części okna.
 *
 * \section etykieta-setings Okno ustawień
 * Okno ustawień otwierane jest po wciśnięciu przycisku "Connection" znajdującego się w menu aplikacji.\n
 * Umożliwia ono wyszukanie oraz wybór urządzenia podłączonego poprzez port szeregowy do komputera. Jeśli mikrokontroler
 * podłączony do komputera, możliwe jest nawiązanie połączenia poprzez wciśnięcie przycisku "Connect". Aby odłączyć
 * urządzenie od aplikacji należy wcisnąć czerwony przycisk "Disconnect".
 *
 * \section etykieta-fin Okno końca rozgrywki
 * Okno końca rozgrywki wyświetlane jest w momencie osiągnięcia przez gracza wartości zdrowia równej 0.\n
 * W górnej części pojawia się komunikat o końcu rozgrywki, a na wirtualnym wyświetlaczu LCD pokazany jest osiągnięty
 * wynik.
 *
 */

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
