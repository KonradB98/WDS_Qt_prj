#include "port.h"
#include <QDebug>


port::port()
{
    mcu = new QSerialPort;
}
port::~port()
{
    delete mcu;
}

//Slot wyswietlajacy dane z mcu w konsoli
void port::readPortData()
{   /*
    QStringList buffsplit = serialBuffer.split(" ");
    QStringList discoveryData;
    serialData = mcu->readAll();
    serialBuffer = QString::fromStdString(serialData.toStdString());
    qDebug() << serialBuffer;
    */
    //wpisz do zmiennej pomocniczej dane z bufora
    QStringList bufferSplit = serialBuffer.split(" ");
    QStringList discoveryData; //Zmienna pomocnicza do weryfikacji poprawnosci danych
    int checkSUM = 0; //Zmienna pom do obliczenia sumy kontrolnej
    uint checkSync = 0x24; //Znak '$' zapisany w Hex
    bool correctConvert;
    //ramka danych sklada sie z 6 czesci danych odzielonych spacja
    //[$][_][X][_][Y][_][Z][_][CRC][_][\n]
    if(bufferSplit.length() < 6){
           serialData = mcu->readAll();//Czytaj dane z portu
           serialBuffer += QString::fromStdString(serialData.toStdString());//Dodaj dane do bufora i konwertuj do stringa
    }
    else{
        // przypisanie wartosci do zmiennej pomocniczej, na ktorej bedziemy dzilac
        discoveryData = bufferSplit;
        //----------------SPRAWDZANIE POPRAWNOSCI DANYCH-------------------//
        //Sprawdz bit synchronizacji
        //if(checkSync == QString(discoveryData[0].toInt())){
        if(checkSync == QString(discoveryData[0]).toUInt(&correctConvert,16)){
            //Zlicz sume slowa bitowego
            for(int i = 1; i < 4; ++i)
                checkSUM += QString(discoveryData[i]).toInt();

               checkSUM = (checkSUM % 128); //Deszyfruj uzyskany wynik
               //Jesli wynik zgodny z rejsetrem CRC, wypisz dane do konsoli
                   if(checkSUM == QString(discoveryData[4]).toInt()){
                       qDebug() << bufferSplit;
                   }
           }
        //Wyczysc bufor
        serialBuffer = "";
    }

}
//Slot otwierajacy i konfigurujacy port. port jest otwierany poprzez wcisniecie przycisku connect w setwindow.
void port::OpenPort(QString portName)
{
    if(mcu->isOpen())
    {
        //Wyswietl komunikat i wroc ze slotu
        qDebug()<<"Port is already opened!";
        return;
    }
    else
    {
        this->mcu->setPortName(portName);
        //Jesli udalo sie otworzyc port
        if(mcu->open(QSerialPort::ReadOnly))
        {
            this->mcu->setBaudRate(QSerialPort::Baud115200);
            this->mcu->setDataBits(QSerialPort::Data8);
            this->mcu->setParity(QSerialPort::NoParity);
            this->mcu->setStopBits(QSerialPort::OneStop);
            this->mcu->setFlowControl(QSerialPort::NoFlowControl);
            qDebug()<<"Port is opened";

            //Polacz ze slotem
           QObject::connect(mcu,SIGNAL(readyRead()),this,SLOT(readPortData()));
            //Aktualizuj statusBar
            QString stat = "Status: Connected";
            emit reportStatus(stat);

        }
        else
        {
              qDebug()<< "FAIL! Port couldn't be opened";

        }
    }
}
//Slot odpowiadajacy za zamkniecie portu szeregowego. Slot jest wywolywany poprzez nacisniecie przycisku disconnect w setwindow
void port::ClosePort()
{
    if(this->mcu->isOpen())
    {
        this->mcu->close();
        qDebug()<<"Connection closed.";
        QString stat = "Status: Disconnected";
        emit reportStatus(stat);
    }
    else {
        qDebug()<<"Port isn't opened!";
        return;
    }
}

