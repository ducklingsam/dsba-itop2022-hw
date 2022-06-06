#include "pokeinfo.h"
#include "ui_pokeinfo.h"
#include "pokechar.h"
#include <vector>
#include <string>
#include "pokemon.h"
#include <iostream>

using std::to_string;

pokeInfo::pokeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pokeInfo)
{
    ui->setupUi(this);
}

pokeInfo::~pokeInfo()
{
    delete ui;
}


void pokeInfo::createLabel(){

    ui->taLabel->setText(QString::number(pokeAmount));
    ui->wLabel->setText(QString::number(pokeWater));
    ui->nLabel->setText(QString::number(pokeNorm));
    ui->pLabel->setText(QString::number(pokePoi));
    ui->gLabel->setText(QString::number(pokeGrass));
    ui->fiLabel->setText(QString::number(pokeFire));
    ui->flLabel->setText(QString::number(pokeFly));
    ui->psyLabel->setText(QString::number(pokePsy));
    ui->ttLabel->setText(QString::number(ttype));
}

void pokeInfo::setP(int pokeAmount, int pokeWater, int pokeNorm, int pokePoi, int pokeGrass, int pokeFire, int pokeFly, int pokePsy, int ttype){
    this->pokeAmount = pokeAmount;
    this->pokeWater = pokeWater;
    this->pokeNorm = pokeNorm;
    this->pokePoi = pokePoi;
    this->pokeGrass = pokeGrass;
    this->pokeFire = pokeFire;
    this->pokeFly = pokeFly;
    this->pokePsy = pokePsy;
    this->ttype = ttype;
    createLabel();
}
