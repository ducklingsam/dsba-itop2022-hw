#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>

namespace Ui {
class infoWindow;
}

class infoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit infoWindow(QWidget *parent = nullptr);
    ~infoWindow();

private slots:
    void on_about_clicked();

    void on_back_clicked();

private:
    Ui::infoWindow *ui;
};

#endif // INFOWINDOW_H
