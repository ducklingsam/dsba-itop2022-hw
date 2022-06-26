#include "addwindow.h"
#include "ui_addwindow.h"
#include "pokechar.h"
#include "includesAndStd.h"

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
    this->poke->number = model->rowCount() + 1;
    this->poke->name = ui->nameInput->text().toStdString();
    this->poke->ftype = ft;
    this->poke->stype = st;
    this->poke->cp = ui->cpInput->text().toInt();
    this->poke->hp = ui->hpInput->text().toInt();
    this->poke->url = "";
    int row = model->rowCount();
    model->insertRows(row, 1);
    QModelIndex index = model->index(row, 0, QModelIndex());
    model->setData(index, ui->nameInput->text());
    this->close();
}


void addWindow::on_ftypeInput_currentTextChanged(const QString &arg1)
{
    ft = arg1.toStdString();
}


void addWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    st = arg1.toStdString();
}

