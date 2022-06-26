#ifndef POKEINFO_H
#define POKEINFO_H

#include "includesAndStd.h"
#include "pokemon.h"

namespace Ui {
class pokeInfo;
}

class pokeInfo : public QDialog
{
    Q_OBJECT

public:
    explicit pokeInfo(QWidget *parent = nullptr);
    ~pokeInfo();
    void createLabel();
    void setP(int pokeAmount, int pokeWater, int pokeNorm, int pokePoi, int pokeGrass, int pokeFire, int pokeFly, int pokePsy, int ttype);

private:
    Ui::pokeInfo *ui;
    int pokeAmount;
    int pokeWater;
    int pokeNorm;
    int pokePoi;
    int pokeGrass;
    int pokeFire;
    int pokeFly;
    int pokePsy;
    int ttype;
};

#endif // POKEINFO_H
