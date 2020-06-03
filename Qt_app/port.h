#ifndef PORT_H
#define PORT_H


#include "QSerialPort"

/*!
 * \file
 * \brief Definicja klasy port
 *
 * Plik zawiera definicję klasy port, która jest klasą pochodną QObject.
 */

/*!
 * \brief Klasa port.
 * Klasa modeluje obiekt typu port. \n
 * Dostarcza interfejs umożliwiający nawiązanie połączenia oraz odbieranie danych przez aplikację.
 */
class port : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor
     */
    port();
    /*!
     * \brief Destruktor
     */
    ~port();
private:
    /*!
     * \brief Wskaźnik na obiekt klasy QSerialPort
     * Definuje obiekt, umożliwiający połączenie oraz interakcję aplikacji z urządzeniem zewnętrznym.
     */
    QSerialPort *mcu; //Wskaznik na obiekt klasy QSerialPort, do obsługi portow szeregowych
    QByteArray serialData; // Bufor do ktorego beda zapisywane dane z mikrokontrolera
    QString serialBuffer;
    /*!
     * \brief Atrybut checkSUM
     * Zmienna używana podczas obliczenia sumy kontrolnej.
     */
    uint checkSUM; //Zmienna pom do obliczenia sumy kontrolnej
    /*!
     * \brief Atrybut checkSync
     * Zmienna przechowująca znak synchronizacji '$' zapisany w systemie szesnastkowym.
     */
    uint checkSync; //Znak '$' zapisany w Hex
    bool correctConvert;
    int16_t pom;
    float pom_g;

private slots:
    //void readPortData(); //Slot czytajacy i wypisujacy dane przesylane z mikrokontrolera
    /*!
     * \brief Slot OpenPort
     * \param[in] portName - nazwa portu typu QString, wybrana przez użytkownika z combobox'a.
     * Slot konfiguruje i otwiera port szeregowy.
     */
    void OpenPort(QString portName); //Slot konfiguruje i otwiera port szeregowy
    /*!
     * \brief Slot ClosePort
     * Slot zamyka otwarty port szeregowy.
     */
    void ClosePort(); //Slot zamyka otwarty port szeregowy
    /*!
     * \brief Slot readData
     * Slot czytajacy dane przesylane z mikrokontrolera.
     */
    void readData(); //Slot czytajacy dane przesylane z mikrokontrolera
signals:
    /*!
     * \brief Sygnal readData
     *  Sygnał emitowany po poprawnym skonfigurowaniu i podlaczeniu urzadzenia.
     */
    void reportStatus(const QString &);//Sygnal emitowany po poprawnym skonfigurowaniu i podlaczeniu urzadzenia
    /*!
     * \brief Sygnal plotData
     * Sygnał emitowany po poprawnym odczytaniu danych w slocie readData().
     */
    void plotData(QList<float> ); // Sygnal emitowany po poprawnym odczytaniu danych w slocie readData()

};

#endif // PORT_H
