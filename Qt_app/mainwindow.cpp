#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

//Zmienne do rysowania wykresow
int t = 0;
int range = 200;
int axis = 0;
//Zmienna wskaznikowa globalna do utworzenia rozgrywki
Gamewin *game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStatusBar(new QStatusBar());//StatusBar
    statusBar()->showMessage("Status: Disconnected");
    //device = new port();
    connect(&sw,SIGNAL(setConnect(QString)),&device,SLOT(OpenPort(QString)));//Otworz i skonfiguruj port
    connect(&sw,SIGNAL(closeConnect()),&device,SLOT(ClosePort()));//Zamknij port

    connect(&device,SIGNAL(reportStatus(const QString &)),this,SLOT(ifReport(const QString &)));//Aktualizuj StatusBar
    connect(&device,SIGNAL(plotData(QList<float>)),this,SLOT(makePlot(QList<float>)));//Rysuj wykres
    //connect(device,SIGNAL(reportStatus(const QString &)),this,SLOT(ifReport(const QString &)));//Aktualizuj StatusBar
    //connect(device,SIGNAL(plotData(QList<float>)),this,SLOT(makePlot(QList<float>)));//Rysuj wykres
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete device;
    //delete game;
}

//Slot otwiera nowe okno do ustawien polaczenia z mikrokontreolerem
void MainWindow::on_pushButtonConnect_clicked()
{
     //sw = new SetWindow(this);
     //connect(sw,SIGNAL(setConnect(QString)),device,SLOT(OpenPort(QString)));//Otworz i skonfiguruj port
     //connect(sw,SIGNAL(closeConnect()),device,SLOT(ClosePort()));//Zamknij port
     sw.show();//Wyswietlenie nowego okna z ustawieniami
}
//Slot odpowiedzialny za aktualizacje paska statusowego polaczenia
void MainWindow::ifReport(const QString &message)
{
    statusBar()->showMessage(message);
}
//Rysowanie wykresu
void MainWindow::makePlot(QList<float> acc_dat)
{
    ui->customPlot->addGraph();
    if(axis == 0){
        ui->customPlot->graph(0)->addData(t,acc_dat.at(0));
    }
    else if(axis == 1){
       ui->customPlot->graph(0)->addData(t,acc_dat.at(1));
    }
    else{
        ui->customPlot->graph(0)->addData(t,acc_dat.at(2));
    }
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("t [s]");
    ui->customPlot->yAxis->setLabel("y");
    if(t < range){
        ui->customPlot->xAxis->setRange(0,t);
    }
    else{
        ui->customPlot->xAxis->setRange(t-200, t);
    }
    ui->customPlot->yAxis->setRange(-2,2);
    ui->customPlot->replot();
    ++t;
}
//-----Przyciski zmieniajace osie--------//
void MainWindow::on_pushButtonX_clicked()
{
    axis = 0;
    ui->customPlot->clearGraphs();
    t = 0;
}

void MainWindow::on_pushButtonY_clicked()
{
    axis = 1;
    ui->customPlot->clearGraphs();
    t = 0;
}

void MainWindow::on_pushButton_3_clicked()
{
    axis = 2;
    ui->customPlot->clearGraphs();
    t = 0;
}

void MainWindow::on_pushButtonPlay_clicked()
{
    game = new Gamewin(this);
    connect(&device,SIGNAL(plotData(QList<float>)),game,SLOT(getControlData(QList<float>)));//Rysuj wykres
    game->show();
}
