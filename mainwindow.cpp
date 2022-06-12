#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "info.h"
#include "pokechar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(700, 600));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    QRectF rCircle(275, 100, 150, 150);
    QRectF wCircle(325, 150, 50, 50);

    rCircle.setSize(2*rCircle.size());
    wCircle.setSize(2*wCircle.size());

    rCircle.moveCenter(rect().center());
    wCircle.moveCenter(rect().center());
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawEllipse(rCircle);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawEllipse(wCircle);
}

void MainWindow::on_startButton_clicked()
{
    class pokeChar poke;
    poke.setModal(true);
    poke.exec();
}


void MainWindow::on_infoButton_clicked()
{
    class info inf;
    inf.setModal(true);
    inf.exec();
}

