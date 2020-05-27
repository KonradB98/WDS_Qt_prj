#ifndef PORT_H
#define PORT_H

#include "QSerialPort"


class port : public QObject
{
    Q_OBJECT
public:
    port();
    ~port();
private:
    QSerialPort *mcu; //Wskaznik na obiekt klasy QSerialPort, do obsługi portow szeregowych
    QByteArray serialData; // Bufor do ktorego beda zapisywane dane z mikrokontrolera
    QString serialBuffer;
    uint checkSUM; //Zmienna pom do obliczenia sumy kontrolnej
    uint checkSync; //Znak '$' zapisany w Hex
    bool correctConvert;
    int16_t pom;
    float pom_g;

private slots:
    //void readPortData(); //Slot czytajacy i wypisujacy dane przesylane z mikrokontrolera
    void OpenPort(QString portName); //Slot konfiguruje i otwiera port szeregowy
    void ClosePort(); //Slot zamyka otwarty port szeregowy
    void readData(); //Slot czytajacy i wypisujacy dane przesylane z mikrokontrolera
signals:
    void reportStatus(const QString &);//Sygnal emitowany po poprawnym skonfigurowaniu i podlaczeniu urzadzenia
    void plotData(QList<float> ); // Sygnal emitowany po poprawnym odczytaniu danych w slocie readPortData()

};

#endif // PORT_H
