#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "pokechar.h"
#include "infowindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

private slots:
    void on_startButton_clicked();

    void on_infoButton_clicked();

    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    pokeChar *poke;
    infoWindow *info;
};
#endif // MAINWINDOW_H
