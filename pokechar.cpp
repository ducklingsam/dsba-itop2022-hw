#include "pokechar.h"
#include "ui_pokechar.h"
#include "addwindow.h"
#include "pokeinfo.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::getline;
using std::string;
using std::ifstream;
using std::string; using std::stoi;
using std::ostringstream; using std::istringstream;
using std::map; using std::vector;

pokeChar::pokeChar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pokeChar)
{
    ui->setupUi(this);
    createTable();
    proxyModel = new class proxyModel();
    proxyModel -> setSourceModel(model);
    ui->nameTable->setModel(proxyModel);
    ui->nameTable->setSortingEnabled(true);
    ui->nameTable->sortByColumn(1, Qt::SortOrder::AscendingOrder);
}

pokeChar::~pokeChar()
{
    delete ui;
}

bool fileExists(QString file) {
    QFileInfo check(file);
    return check.exists() && check.isFile();
}

void pokeChar::createTable() {
    bool flag = false;
    model = new QStandardItemModel(0, 0, this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    QString fileName = QString::fromStdString("/Users/obozhenov/Desktop/DSBA/1y/cpp/updData.csv");
    if (!fileExists(fileName)) {
        flag = true;
        fileName = QString::fromStdString("/Users/obozhenov/Desktop/DSBA/1y/cpp/pokemonGO.csv");
    }
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    if (flag) file.readLine();
    while(!file.atEnd()) {
        string token;
        string line = file.readLine().toStdString();
        istringstream ss(line);
        vector<string> lineAsVector;
        while(getline(ss, token, ',')) lineAsVector.push_back(token);
        Pokemon po;
        po.number = stoi(lineAsVector[0]);
        po.name = lineAsVector[1];
        po.ftype = lineAsVector[2];
        po.stype = lineAsVector[3];
        po.cp = stoi(lineAsVector[4]);
        po.hp = stoi(lineAsVector[5]);
        if (!lineAsVector[6].empty() && lineAsVector[6][lineAsVector[6].length()-1] == '\n') {
            lineAsVector[6].erase(lineAsVector[6].length()-1);
        }
        po.url = lineAsVector[6];
        p.push_back(po);
    }
    file.close();
    for (int i = 0; i < p.size(); i++) {
        model->insertRow(i);
        model->setData(model->index(i, 0), QString::fromStdString(p[i].name));
    }
    int water = 0, norm = 0, poi = 0, grass = 0, fire = 0, fly = 0, psy = 0, tt = 0;
    for (int i = 0; i < p.size(); i++) {
        if (p[i].ftype == "Water" or p[i].stype == "Water") water++;
        if (p[i].ftype == "Normal" or p[i].stype == "Normal") norm++;
        if (p[i].ftype == "Poison" or p[i].stype == "Poison") poi++;
        if (p[i].ftype == "Grass" or p[i].stype == "Grass") grass++;
        if (p[i].ftype == "Fire" or p[i].stype == "Fire") fire++;
        if (p[i].ftype == "Flying" or p[i].stype == "Flying") fly++;
        if (p[i].ftype == "Psychic" or p[i].stype == "Psychic") psy++;
        if (p[i].stype != "") tt++;
    }
    std::cout << p.size();
    ui->taLabel->setText(QString::number(p.size()));
    ui->wLabel->setText(QString::number(water));
    ui->nLabel->setText(QString::number(norm));
    ui->pLabel->setText(QString::number(poi));
    ui->gLabel->setText(QString::number(grass));
    ui->fiLabel->setText(QString::number(fire));
    ui->flLabel->setText(QString::number(fly));
    ui->psyLabel->setText(QString::number(psy));
    ui->ttLabel->setText(QString::number(tt));
}

void pokeChar::on_mainButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Are you sure you want to quit?");
    msgBox.setInformativeText("All unsaved data will be deleted!");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    msgBox.setPalette(pal);
    int ans = msgBox.exec();
    switch(ans) {
        case QMessageBox::Yes: {
            this->close();
            break;
        }
        case QMessageBox::No: {
            break;
        }
    }
}


void pokeChar::on_addButton_clicked()
{
    addWindow add;
    Pokemon newPoke;
    this->p.push_back(newPoke);
    add.setModelPointer(&p[p.size() - 1], model);
    add.setModal(true);
    add.exec();
}

void pokeChar::on_deleteButton_clicked()
{
    int selectedRow = ui->nameTable->currentIndex().row();
    this->model->removeRows(selectedRow, 1);
    vector<Pokemon>::iterator it = this->p.begin() + selectedRow;
    this->p.erase(it);
}


void pokeChar::on_nameTable_clicked(const QModelIndex &index)
{
    string pokemonName = (index.data().toString()).toStdString();
    string url = "No URL added";
    for (int i = 0; i < p.size(); i++) {
        if (p[i].name == pokemonName) {
            ui->num->setText(QString::number(p[i].number));
            ui->ftype->setText(QString::fromStdString(p[i].ftype));
            ui->stype->setText(QString::fromStdString(p[i].stype));
            ui->cp->setText(QString::number(p[i].cp));
            ui->hp->setText(QString::number(p[i].hp));
            if (p[i].url != "") {
                url = string("<a href=\"") + p[i].url + string("\">Click Here</a>");
                ui->url->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
                ui->url->setOpenExternalLinks(true);
                ui->url->setTextFormat(Qt::RichText);
            }
            ui->url->setText(QString::fromStdString(url));

        }
    }
}

void pokeChar::on_updateButton_clicked()
{
    int water = 0, norm = 0, poi = 0, grass = 0, fire = 0, fly = 0, psy = 0, tt = 0;
    for (int i = 0; i < p.size(); i++) {
        if (p[i].ftype == "Water" or p[i].stype == "Water") water++;
        if (p[i].ftype == "Normal" or p[i].stype == "Normal") norm++;
        if (p[i].ftype == "Poison" or p[i].stype == "Poison") poi++;
        if (p[i].ftype == "Grass" or p[i].stype == "Grass") grass++;
        if (p[i].ftype == "Fire" or p[i].stype == "Fire") fire++;
        if (p[i].ftype == "Flying" or p[i].stype == "Flying") fly++;
        if (p[i].ftype == "Psychic" or p[i].stype == "Psychic") psy++;
        if (p[i].stype != "") tt++;
    }
    ui->taLabel->setText(QString::number(p.size()));
    ui->wLabel->setText(QString::number(water));
    ui->nLabel->setText(QString::number(norm));
    ui->pLabel->setText(QString::number(poi));
    ui->gLabel->setText(QString::number(grass));
    ui->fiLabel->setText(QString::number(fire));
    ui->flLabel->setText(QString::number(fly));
    ui->psyLabel->setText(QString::number(psy));
    ui->ttLabel->setText(QString::number(tt));
    QFile file("/Users/obozhenov/Desktop/DSBA/1y/cpp/updData.csv");
    if (file.open(QFile::WriteOnly|QFile::Text)) {
        QTextStream stream(&file);
        for (int i = 0; i < p.size(); i++) {
            stream << p[i].number << ',' << QString::fromStdString(p[i].name) << ',' << QString::fromStdString(p[i].ftype) << ',' << QString::fromStdString(p[i].stype)
                   << ',' << p[i].cp << ',' << p[i].hp << ',' << QString::fromStdString(p[i].url) << '\n';
        }
    }
}


void pokeChar::on_resetButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("This dataset will be deleted");
    msgBox.setInformativeText("Are you sure you want to proceed?\nYou will be returned to the main window");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    msgBox.setPalette(pal);
    int ans = msgBox.exec();
    switch(ans) {
        case QMessageBox::Yes: {
            QFile file("/Users/obozhenov/Desktop/DSBA/1y/cpp/updData.csv");
            file.remove();
            this->close();
            break;
        }
        case QMessageBox::No: {
            break;
        }
    }
}

