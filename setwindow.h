#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>
#include <QSerialPort>//Do obslugi portow szeregowych
//#include "mainwindow.h"
#include <QByteArray>
#include "port.h"

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

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

  //  void readPortData();

private:
    Ui::SetWindow *ui;
    port *prt;
   // QSerialPort *microcontroller;//Wskaznik na obiekt klasy QSerialPort
    void addLogs(QString message);//Metoda wpisujaca logi do pola tekstowego
    QByteArray sData;
    QString sBuff;
    //-----------Proba--------------//
signals:
    void reportStatus(const QString &);
    void portConfig();
};

#endif // SETWINDOW_H
