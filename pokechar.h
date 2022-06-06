#ifndef POKECHAR_H
#define POKECHAR_H

#include <QDialog>
#include <QStandardItemModel>
#include <vector>
#include "pokemon.h"
#include "pokeinfo.h"
#include "proxymodel.h"

using std::vector;

namespace Ui {
class pokeChar;
}

class pokeChar : public QDialog
{
    Q_OBJECT
    friend class pokeInfo;

public:
    explicit pokeChar(QWidget *parent = nullptr);
    ~pokeChar();
    void createTable();
    void cntPoke();
    vector<Pokemon> p;

private slots:
    void on_mainButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_nameTable_clicked(const QModelIndex &index);

    void on_minCpSpin_valueChanged(int arg1);


    void on_maxCpSpin_valueChanged(int arg1);

    void on_minHpSpin_valueChanged(int arg1);

    void on_maxHpSpin_valueChanged(int arg1);

    void on_updateButton_clicked();

private:
    Ui::pokeChar *ui;
    QStandardItemModel* model;
    proxyModel *proxyModel;

};

#endif // POKECHAR_H
