#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStatusBar(new QStatusBar());//StatusBar
    statusBar()->showMessage("Status: Disconnected");
    connect(&sw,SIGNAL(setConnect(QString)),&device,SLOT(OpenPort(QString)));//Otworz i skonfiguruj port
    connect(&sw,SIGNAL(closeConnect()),&device,SLOT(ClosePort()));//Zamknij port
    connect(&device,SIGNAL(reportStatus(const QString &)),this,SLOT(ifReport(const QString &)));//Aktualizuj StatusBar
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Slot otwiera nowe okno do ustawien polaczenia z mikrokontreolerem
void MainWindow::on_pushButtonConnect_clicked()
{
     sw.show();//Wyswietlenie nowego okna z ustawieniami
}
//Slot odpowiedzialny za aktualizacje paska statusowego polaczenia
void MainWindow::ifReport(const QString &message)
{
    statusBar()->showMessage(message);
}

