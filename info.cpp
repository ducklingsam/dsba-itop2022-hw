#include "info.h"
#include "ui_info.h"
#include <QMessageBox>
#include <QColor>

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
    QMessageBox msgBox(QMessageBox::Information, "About", "Created by\n©Student №178\n2022");
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    msgBox.setPalette(pal);
    msgBox.exec();
}

void info::on_pushButton_2_clicked()
{
    this->close();
}

