#ifndef POKECHAR_H
#define POKECHAR_H

#include "includesAndStd.h"
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
    vector<Pokemon> p;
    void info(vector<Pokemon> p);
    QString updDir;

private slots:
    void on_mainButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_nameTable_clicked(const QModelIndex &index);

    void on_updateButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::pokeChar *ui;
    QStandardItemModel* model;
    proxyModel *proxyModel;
    QStandardItemModel* infomod;

};

#endif // POKECHAR_H
