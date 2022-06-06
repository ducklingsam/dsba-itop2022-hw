#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "pokemon.h"

namespace Ui {
class addWindow;
}

class addWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWindow(QWidget *parent = nullptr);
    ~addWindow();
    void setModelPointer(Pokemon *poke, QStandardItemModel* model);

private slots:

    void on_addButton_clicked();

private:
    Ui::addWindow *ui;
    Pokemon *poke;
    QStandardItemModel *model;
};

#endif // ADDWINDOW_H
