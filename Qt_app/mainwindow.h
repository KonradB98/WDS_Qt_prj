#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setwindow.h"
#include <QSerialPort>//Do obslugi portow szeregowych
#include "port.h"
#include "gamewin.h"

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
    //Funkcja odpowiada rysowanie wykresu
    void makePlot(QList<float> acc_dat);
    void on_pushButtonX_clicked();

    void on_pushButtonY_clicked();

    void on_pushButton_3_clicked();

    void on_pushButtonPlay_clicked();

private:
    Ui::MainWindow *ui;
    //SetWindow sw;
    SetWindow *sw;
    port device;
    //port *device;
    //Gamewin *game;

};
#endif // MAINWINDOW_H
