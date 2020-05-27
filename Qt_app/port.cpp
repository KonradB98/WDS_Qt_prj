#include "port.h"
#include <QDebug>
#include <climits>

const float resolution = 2.0;//Rozdzielczosc akcelerometru

port::port()
{
    mcu = new QSerialPort;
    checkSync = 0x24;
}
port::~port()
{
    delete mcu;
}
/*
//Slot wyswietlajacy dane z mcu w konsoli
void port::readPortData()
{
    QList<float> acc_data;
    QStringList discoveryData = serialBuffer.split(" "); //Zmienna pomocnicza do weryfikacji poprawnosci danych
    qDebug()<<discoveryData;
    checkSUM = 0; //Zmienna pom do obliczenia sumy kontrolnej
    //ramka danych sklada sie z 6 czesci danych odzielonych spacja
    //[$][_][X][_][Y][_][Z][_][CRC][_][\n]
    if(discoveryData.length() < 6){
           serialData = mcu->readAll();//Czytaj dane z portu
           serialBuffer += QString::fromStdString(serialData.toStdString());//Dodaj dane do bufora i konwertuj do stringa
          // qDebug()<<"Mniejszy niz 6";
    }
    else{
        // przypisanie wartosci do zmiennej pomocniczej, na ktorej bedziemy dzilac
        //discoveryData = bufferSplit;
        //----------------SPRAWDZANIE POPRAWNOSCI DANYCH-------------------//
        //Sprawdz bit synchronizacji
        if(checkSync == QString(discoveryData[0]).toUInt(&correctConvert,16)){
            //Zlicz sume slowa bitowego
            for(int i = 1; i < 4; ++i){
                checkSUM += QString(discoveryData[i]).toInt();
                pom = discoveryData[i].toInt();
                pom_g = (pom*resolution)/((float)INT16_MAX);
                acc_data.append(pom_g);
            }
               // checkSUM += QString(discoveryData[i]).toInt();

               checkSUM = (checkSUM % 128); //Deszyfruj uzyskany wynik
               //Jesli wynik zgodny z rejsetrem CRC, wypisz dane do konsoli
                   if(checkSUM == QString(discoveryData[4]).toUInt()){
                       //---------Konwersja danych do jednostek Si(g) max=2.0g-------------//
                       emit plotData(acc_data);
                        //qDebug()<< discoveryData[1] << discoveryData[2] << discoveryData[3] << INT16_MAX;
                       //qDebug() << bufferSplit;
                   }
           }
        //Wyczysc bufor
        serialBuffer.clear();
        //bufferSplit.clear();
        //discoveryData.clear();
        serialData.clear();
    }

}
*/
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
          // QObject::connect(mcu,SIGNAL(readyRead()),this,SLOT(readPortData()));
           QObject::connect(mcu,SIGNAL(readyRead()),this,SLOT(readData()));
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

void port::readData()
{
    QList<float> acc_data;
    QByteArray recivedData;
    QString line;
    QStringList discoveryData;
    checkSUM = 0;
    recivedData.append(mcu->readAll());
    line = QString::fromStdString(recivedData.toStdString());
    discoveryData = line.split(" ");
    if(discoveryData.length()==6){
      if(checkSync == QString(discoveryData[0]).toUInt(&correctConvert,16)){
        //Zlicz sume slowa bitowego
        for(int i = 1; i < 4; ++i){
            checkSUM += QString(discoveryData[i]).toInt();
            pom = discoveryData[i].toInt();
            pom_g = (pom*resolution)/((float)INT16_MAX);
            acc_data.append(pom_g);
        }
           checkSUM = (checkSUM % 128); //Deszyfruj uzyskany wynik
           //Jesli wynik zgodny z rejsetrem CRC, wypisz dane do konsoli
               if(checkSUM == QString(discoveryData[4]).toUInt()){
                   //---------Konwersja danych do jednostek Si(g) max=2.0g-------------//
                   emit plotData(acc_data);
                   //qDebug()<<acc_data;
               }
               acc_data.clear();
       }
    }
    recivedData.clear();
    discoveryData.clear();
}

