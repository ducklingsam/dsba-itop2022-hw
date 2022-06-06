#include "proxymodel.h"

proxyModel::proxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    minCP = 0;
    maxCP = INT_MAX;
    minHP = 0;
    maxHP = INT_MAX;
}

void proxyModel::setMinCP(int minCP)
{
    this->minCP = minCP;
    invalidateFilter();
}

void proxyModel::setMaxCP(int maxCP)
{
    this->maxCP = maxCP;
    invalidateFilter();
}

void proxyModel::setMinHP(int minHP)
{
    this->minHP = minHP;
    invalidateFilter();
}

void proxyModel::setMaxHP(int maxHP)
{
    this->maxHP = maxHP;
    invalidateFilter();
}

bool proxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{

    QString lenA = sourceModel()->data(left).toString();
    QString lenB = sourceModel()->data(right).toString();

    return lenA < lenB;
}

bool proxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
    int CP = sourceModel()->data(index).toInt();
    return (minCP <= CP) && (CP <= maxCP);
}


