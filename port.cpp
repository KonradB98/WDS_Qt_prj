#include "port.h"
#include <QDebug>
#include <QList>//Dynamiczna lista obiektow QList<QSerialPortInfo>
#include <QSerialPortInfo>//QSerialPortInfo
#include <QByteArray>


port::port()
{
    mcu = new QSerialPort;
}
port::~port()
{
    delete mcu;
}
//Funkcja otwierajaca port szeregowy
void port::connect(QString portName)
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
        //   QString stat = "Status: Connected";
         //  emit reportStatus(stat);

        }
        else
        {
              qDebug()<< "FAIL! Port couldn't be opened";

        }
   }
}
//Funkcja zamykajaca port szeregowy
void port::closeConnection()
{
    if(this->mcu->isOpen())
    {
        this->mcu->close();
        qDebug()<<"Connection closed.";
    }
    else {
        qDebug()<<"Port isn't opened!";
        return;
    }
}
//Slot wyswietlajacy dane z mcu w konsoli
void port::readPortData()
{/*
    QStringList buffsplit = serialBuffer.split(" ");
    QStringList discoveryData;
    serialData = mcu->readAll();
    serialBuffer = QString::fromStdString(serialData.toStdString());
    qDebug() << serialBuffer;*/

    QStringList bufferSplit = serialBuffer.split(" ");
    QStringList discoveryData;
    int checkSUM = 0;
    if(bufferSplit.length() < 4){
           serialData = mcu->readAll();
           serialBuffer += QString::fromStdString(serialData.toStdString());
    }
    else{
        // bufferSplit[0], bufferSplit[1] ...
        discoveryData = bufferSplit;

        // SPRAWDZANIE POPRAWNOSCI DANYCH
        for(int i = 0; i < 3; ++i)
            checkSUM += QString(discoveryData[i]).toInt();

           checkSUM = (checkSUM % 128);
               if(checkSUM == QString(discoveryData[3]).toInt()){
                   qDebug() << bufferSplit;
               }
        serialBuffer = "";
    }

}

