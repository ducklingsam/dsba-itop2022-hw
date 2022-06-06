#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "info.h"
#include "pokechar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    class pokeChar poke;
    poke.setModal(true);
    poke.exec();
}


void MainWindow::on_infoButton_clicked()
{
    class info inf;
    inf.setModal(true);
    inf.exec();
}

