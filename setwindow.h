#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>
#include <QSerialPort>//Do obslugi portow szeregowych
//#include "mainwindow.h"
#include <QByteArray>

namespace Ui {
class SetWindow;
}

class SetWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetWindow(QWidget *parent = nullptr);
    ~SetWindow();

private slots:
    void on_pushButtonSearch_clicked();
    //void onErrorOccurred(QSerialPort::SerialPortError error);//Metoda do wykrywania bledow polaczen portow szeregowych

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

    void readPortData();

private:
    Ui::SetWindow *ui;
    QSerialPort *microcontroller;//Wskaznik na obiekt klasy QSerialPort
    void addLogs(QString message);//Metoda wpisujaca logi do pola tekstowego
    QByteArray sData;
    QString sBuff;
    //-----------Proba--------------//
signals:
    void reportStatus(const QString &);
    void portConfig();
};

#endif // SETWINDOW_H
