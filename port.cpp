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
            this->mcu->setBaudRate(QSerialPort::Baud57600);
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
{
    QStringList buffsplit = sBuff.split(";");

    QByteArray _sData = mcu->readAll();
    QString _sBuff = QString::fromStdString(_sData.toStdString());
    qDebug() << _sBuff;
   // this->addLogs(_sBuff+"\t");
}

