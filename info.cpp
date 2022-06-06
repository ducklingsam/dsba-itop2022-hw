#include "info.h"
#include "ui_info.h"
#include <QMessageBox>

info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
}

info::~info()
{
    delete ui;
}

void info::on_pushButton_clicked()
{
    QMessageBox::information(this, "About", "Created by\n© Bozhenov Oleg\n2022");
}

void info::on_pushButton_2_clicked()
{
    this->close();
}

