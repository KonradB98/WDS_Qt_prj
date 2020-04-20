#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setwindow.h"//*sw
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStatusBar(new QStatusBar());//StatusBar
    statusBar()->showMessage("Status: Disconnected");
    device = new port;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Slot otwiera nowe okno do ustawien polaczenia z mikrokontreolerem
void MainWindow::on_pushButtonConnect_clicked()
{

    sw = new SetWindow(this);//Dynamiczna alokacja pamieci oraz ustawienie rodzica(MainWindow) do poprawnego zwolnienia pamieci
    sw->show();//Wyswietlenie nowego okna z ustawieniami
    connect(sw,SIGNAL(reportStatus(const QString &)),this,SLOT(ifReport(const QString &)));
    //connect(sw,SIGNAL(reportStatus));

}

void MainWindow::ifReport(const QString &message)
{
    statusBar()->showMessage(message);
}

