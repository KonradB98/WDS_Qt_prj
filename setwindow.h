#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>
//#include <QSerialPort>//Do obslugi portow szeregowych
//#include <QByteArray>
//#include "port.h"

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
    //---------Przyciski------------//
    void on_pushButtonSearch_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();
private:
    Ui::SetWindow *ui;
    void addLogs(QString message);//Metoda wpisujaca logi do pola tekstowego
signals:
    void setConnect(QString); //Sygnal emitowany po wcisnieciu przycisku "Connect"
    void closeConnect(); //Sygnal emitowany po wcisnieciu przycisku "Disconnect"
};

#endif // SETWINDOW_H
