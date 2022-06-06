#include "addwindow.h"
#include "ui_addwindow.h"
#include "pokechar.h"

addWindow::addWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindow)
{
    ui->setupUi(this);
}

addWindow::~addWindow()
{
    delete ui;
}

void addWindow::setModelPointer(Pokemon *poke, QStandardItemModel* model) {
    this->poke = poke;
    this->model = model;
}

void addWindow::on_addButton_clicked()
{
    this->poke->number = model->rowCount();
    this->poke->name = ui->nameInput->text().toStdString();
    this->poke->ftype = ui->ftypeInput->text().toStdString();
    this->poke->stype = ui->stypeInput->text().toStdString();
    this->poke->cp = ui->cpInput->text().toInt();
    this->poke->hp = ui->hpInput->text().toInt();
    this->poke->url = "No URL added";

    int row = model->rowCount();
    model->insertRows(row, 1);
    QModelIndex index = model->index(row, 0, QModelIndex());
    model->setData(index, ui->nameInput->text());
    this->close();
}

