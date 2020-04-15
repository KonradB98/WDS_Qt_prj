#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setwindow.h"
#include <QSerialPort>//Do obslugi portow szeregowych


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButtonConnect_clicked();
    //---------------Proba--------------//
    void ifReport(const QString &message);
    void openPort();

private:
    Ui::MainWindow *ui;
    //SetWindow *sw;
    SetWindow *sw;//Wskaznik na obiekt SetWindow->okno ustawien polaczenia
    //QSerialPort *mcu;

};
#endif // MAINWINDOW_H
