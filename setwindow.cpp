#include "setwindow.h"
#include "ui_setwindow.h"
#include <QDebug>//Debugowanie w konsoli
#include <QList>//Dynamiczna lista obiektow QList<QSerialPortInfo>
#include <QSerialPortInfo>//QSerialPortInfo
#include <QSerialPort>//obsluga portu szeregowego
#include <QDateTime>//currentDateTime()
#include "mainwindow.h"



SetWindow::SetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetWindow)
{
    ui->setupUi(this);
    prt = new port;
    //Stworzenie nowego obiektu klasy QSerial port oraz ustawienie jego rodzica(SetWindow) do poprawnego zwolnienia pamieci
   // microcontroller = new QSerialPort(this);
    sBuff = " ";
}

SetWindow::~SetWindow()
{
    delete ui;
}

void SetWindow::on_pushButtonSearch_clicked()
{
   // Dodanie komunikatu do Logow aplikacji
    this->addLogs("Device search...");
    QList<QSerialPortInfo> devices;//Lista obiektow typu QSerialPortInfo
    devices = QSerialPortInfo::availablePorts();//Wpisanie do listy info o portach metoda statyczna availablePorts()
    for(int i = 0; i < devices.count(); i++) {//Petla wypisujaca info o portach w Logs
        // Dodanie do Comboboxa:portName-Nazwa portu,description-Opis portu
        //at-indeks elementu listy
      ui->comboBoxDevices->addItem(devices.at(i).portName() + " " + devices.at(i).description());
      //Dodanie do logow info o znalezionym urzadzeniu
      this->addLogs("Device found:"+ devices.at(i).portName() + " " + devices.at(i).description());
    }
}

void SetWindow::addLogs(QString message)
{   //Aktualna data w formacie podanym w metodzie toString()
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEdit->append(currentDateTime + "\t" + message);
}
//Slot definiujacy nawiazanie polaczenia z mikrokontrolerem
void SetWindow::on_pushButtonConnect_clicked()
{
    //Sprawdzenie czy jakiekolwiek urzadzenia sa dostepne do podlaczenia
    //Jesli nie -> wyswietl komunikat i wroc ze slotu
    if(ui->comboBoxDevices->count() == 0)
    {
        this->addLogs("No connected devices!");
        return;
    }
    //Ustawienie nazwy portu
    QString comboBoxstr = ui->comboBoxDevices->currentText();
    QStringList portList = comboBoxstr.split(" ");
    QString portName = portList.first();

    prt->connect(portName);

    //QString portName = "COM3";
    //Ustaw nazwe portu
   // this->microcontroller->setPortName(portName);
    //Jesli port jest otworzony
    /*
    if(microcontroller->isOpen())
    {
        //Wyswietl komunikat i wroc ze slotu
        this->addLogs("Port is already opened!");
        return;
    }
    else
    {
        //Jesli udalo sie otworzyc port
        if(microcontroller->open(QSerialPort::ReadOnly))
        {
            this->microcontroller->setBaudRate(QSerialPort::Baud57600);
            this->microcontroller->setDataBits(QSerialPort::Data8);
            this->microcontroller->setParity(QSerialPort::NoParity);
            this->microcontroller->setStopBits(QSerialPort::OneStop);
            this->microcontroller->setFlowControl(QSerialPort::NoFlowControl);
            this->addLogs("Port is opened");

            //Polacz ze slotem
            connect(this->microcontroller,SIGNAL(readyRead()),this,SLOT(readPortData()));
            //Aktualizuj statusBar
           QString stat = "Status: Connected";
           emit reportStatus(stat);

        }
        else
        {
            this->addLogs("FAIL! Port couldn't be opened");
        }

    }
*/
}
//Slot odpowiadajacy zamknieciu portu
void SetWindow::on_pushButtonDisconnect_clicked()
{
    prt->closeConnection();
    /*
    //Jesli port jest otwarty
    if(microcontroller->isOpen())
    { //Zamknij port, wypisz komunikat
      microcontroller->close();
      this->addLogs("Connection closed.");
      //Aktualizuj statusBar
      QString stat = "Status: Disconnected";
      emit reportStatus(stat);
    }
    else
    {
      //Wypisz komunikat i wyjdz ze slotu
      this->addLogs("Port isn't opened!");
      return;
    }
    */
}

