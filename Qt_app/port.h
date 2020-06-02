#ifndef PORT_H
#define PORT_H

#include "QSerialPort"

/*!
 * \brief Klasa modeluje obiekt typu port.
 * Posiada niezbęde atrybuty, sloty oraz sygnały umożliwiające nawiązanie połączenia z zewnątrznym urządzeniem.
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
     * \brief Wskaźnik na obiekt klasy QSerialPort.
     * Definuje obiekt, umożliwiający połączenie oraz interakcję aplikacji z urządzeniem zewnętrznym.
     */
    QSerialPort *mcu; //Wskaznik na obiekt klasy QSerialPort, do obsługi portow szeregowych
    QByteArray serialData; // Bufor do ktorego beda zapisywane dane z mikrokontrolera
    QString serialBuffer;
    /*!
     * \brief Zmienna potrzebna do obliczenia sumy kontrolnej.
     */
    uint checkSUM; //Zmienna pom do obliczenia sumy kontrolnej
    /*!
     * \brief Zmienna przechowująca znak synchronizacji zapisany w systemie szestnastkowym.
     */
    uint checkSync; //Znak '$' zapisany w Hex
    bool correctConvert;
    int16_t pom;
    float pom_g;

private slots:
    //void readPortData(); //Slot czytajacy i wypisujacy dane przesylane z mikrokontrolera
    /*!
     * \brief Slot konfiguruje i otwiera port szeregowy.
     * \param[in] portName - nazwa portu typu QString, sczytana z combobox'a.
     */
    void OpenPort(QString portName); //Slot konfiguruje i otwiera port szeregowy
    /*!
     * \brief Slot zamyka otwarty port szeregowy.
     */
    void ClosePort(); //Slot zamyka otwarty port szeregowy
    /*!
     * \brief Slot czytajacy i wypisujacy dane przesylane z mikrokontrolera.
     */
    void readData(); //Slot czytajacy i wypisujacy dane przesylane z mikrokontrolera
signals:
    /*!
     * \brief Sygnal emitowany po poprawnym skonfigurowaniu i podlaczeniu urzadzenia.
     */
    void reportStatus(const QString &);//Sygnal emitowany po poprawnym skonfigurowaniu i podlaczeniu urzadzenia
    /*!
     * \brief Sygnal emitowany po poprawnym odczytaniu danych w slocie readData().
     */
    void plotData(QList<float> ); // Sygnal emitowany po poprawnym odczytaniu danych w slocie readData()

};

#endif // PORT_H
