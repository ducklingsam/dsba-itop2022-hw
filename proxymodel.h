#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include "includesAndStd.h"

class proxyModel: public QSortFilterProxyModel
{
    public:
        proxyModel(QObject* parent = 0);

        void setMinCP(int minCP);
        void setMaxCP(int maxCP);
        void setMinHP(int minHP);
        void setMaxHP(int maxHP);

        int get_minCP() const
        {
            return minCP;
        }
        int get_maxCP() const
        {
            return maxCP;
        }
        int get_minHP() const
        {
            return minHP;
        }
        int get_maxHP() const
        {
            return maxHP;
        }

    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;


    private:
        int minCP;
        int maxCP;
        int minHP;
        int maxHP;
};

#endif // PROXYMODEL_H
