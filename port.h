#ifndef PORT_H
#define PORT_H

#include "QSerialPort"

class port : public QObject
{
    Q_OBJECT
public:
    port();
    ~port();
     void connect(QString portName); //Metoda umozliwiajaca nawiazanie polaczenia z mikrokontrolerem
     void closeConnection(); //Metoda zamykajaca polaczenie
private:
    QSerialPort *mcu; //Wskaznik na obiekt klasy QSerialPort
   // QString sBuff; // Bufor do ktorego beda zapisywane dane z mikrokontrolera
    //QByteArray sData;//
    QByteArray serialData;
    QString serialBuffer;

private slots:
    void readPortData(); //Slot czytajacy i wypisujacy dane przesylane z mikrokontrolera
};

#endif // PORT_H
