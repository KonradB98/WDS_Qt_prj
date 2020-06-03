#include "setwindow.h"
#include "ui_setwindow.h"
#include <QList>//Dynamiczna lista obiektow QList<QSerialPortInfo>
#include <QSerialPortInfo>//QSerialPortInfo
#include <QDateTime>//currentDateTime()


SetWindow::SetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetWindow)
{
    ui->setupUi(this);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonDisconnect->setStyleSheet("background-color: #b30000;");
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
    //emituj sygnal, ktory aktywuje SLOT w port.cpp odpowiadajacy za otworzenie i konfiguracje polaczenia
    emit setConnect(portName);
    //Sprzezenie dwóch przycisku connect z disconnect
    ui->pushButtonDisconnect->setEnabled(true);
    ui->pushButtonDisconnect->setStyleSheet("background-color: rgb(255, 26, 26);");
    ui->pushButtonConnect->setEnabled(false);
    ui->pushButtonConnect->setStyleSheet("background-color: #00b300;");
}
//Slot odpowiadajacy zamknieciu portu
void SetWindow::on_pushButtonDisconnect_clicked()
{
    //emituje sygnal, ktory aktywuje SLOT w port.cpp odpowiadajacy za zamkniecie polaczenia
    emit closeConnect();
    //Sprzezenie dwóch przycisku connect z disconnect
    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonDisconnect->setStyleSheet("background-color: #b30000;");
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonConnect->setStyleSheet("background-color: #00ff00;");
}
