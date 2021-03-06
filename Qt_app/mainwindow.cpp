#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPointer>

//Zmienna wskaznikowa globalna do utworzenia rozgrywki
Gamewin *game;

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
    connect(&device,SIGNAL(plotData(QList<float>)),this,SLOT(makePlot(QList<float>)));//Rysuj wykres

    t = 0;
    range = 20;
    axis = 0;
    os = "X";
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
//Przycisk uruchamia nowa gre
void MainWindow::on_pushButtonPlay_clicked()
{
    game = new Gamewin(this);
    connect(&device,SIGNAL(plotData(QList<float>)),game,SLOT(getControlData(QList<float>)));//Rysuj
    game->show();
}
//Slot odpowiedzialny za aktualizacje paska statusowego polaczenia
void MainWindow::ifReport(const QString &message)
{
    statusBar()->showMessage(message);
}
//Rysowanie wykresu
void MainWindow::makePlot(QList<float> acc_dat)
{
    //os = "X";
    ui->customPlot->addGraph();
    ui->customPlot->setBackground(QColor(102, 102, 102));
    if(axis == 0){
        ui->customPlot->graph(0)->addData(t,acc_dat.at(0));
        ui->customPlot->graph(0)->setPen(QPen(QColor(153, 187, 255),2));
    }
    else if(axis == 1){
       ui->customPlot->graph(0)->addData(t,acc_dat.at(1));
       ui->customPlot->graph(0)->setPen(QPen(QColor(255, 128, 128),2));
    }
    else{
        ui->customPlot->graph(0)->addData(t,acc_dat.at(2));
        ui->customPlot->graph(0)->setPen(QPen(QColor(77, 0, 77),2));
    }
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("t [s]");
    ui->customPlot->yAxis->setLabel("Przyspieszenie wzgledem osi " + os + " [g]");
    if(t < range){
        ui->customPlot->xAxis->setRange(0,t);
    }
    else{
        ui->customPlot->xAxis->setRange(t-range, t);
    }
    ui->customPlot->yAxis->setRange(-2,2);
    ui->customPlot->replot();
    //++t;
    t+=0.17;
}


//-----Przyciski zmieniajace osie--------//
void MainWindow::on_pushButtonX_clicked()
{
    axis = 0;
    ui->customPlot->clearGraphs();
    os = "X";
    t = 0;
}

void MainWindow::on_pushButtonY_clicked()
{
    axis = 1;
    ui->customPlot->clearGraphs();
    os = "Y";
    t = 0;
}

void MainWindow::on_pushButton_3_clicked()
{
    axis = 2;
    ui->customPlot->clearGraphs();
    os = "Z";
    t = 0;
}
