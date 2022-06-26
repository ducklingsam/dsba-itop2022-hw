#ifndef INFO_H
#define INFO_H

#include "includesAndStd.h"

namespace Ui {
class info;
}

class info : public QDialog
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = nullptr);
    ~info();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::info *ui;
};

#endif // INFO_H
