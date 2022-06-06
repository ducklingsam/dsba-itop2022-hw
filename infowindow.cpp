#include "infowindow.h"
#include "ui_infowindow.h"
#include "mainwindow.h"
#include <QMessageBox>

infoWindow::infoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::infoWindow)
{
    ui->setupUi(this);
}

infoWindow::~infoWindow()
{
    delete ui;
}

void infoWindow::on_about_clicked()
{
    QMessageBox::information(this, "About", "Created by\n© Bozhenov Oleg\n2022");
}


void infoWindow::on_back_clicked()
{
    close();
}

