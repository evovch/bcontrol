#include "bfixedpointmodel.h"
#include <QDebug>
#include <QColor>

bFixedPointModel::bFixedPointModel(QObject *parent, fixedPointHash *fp) :
    QAbstractTableModel(parent)
{
    if (fp == 0)return;

    fPs = fp;
}

int bFixedPointModel::rowCount(const QModelIndex & /*parent*/) const
{
   int s = fPs->size();

//   qDebug() << s;

   return s;
}

int bFixedPointModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant bFixedPointModel::data(const QModelIndex &index, int role) const
{
    QList<QString> ids = fPs->keys();
    if( ids.size() == 0)return QString("");
    QString id = ids[index.row()];

    if (role == Qt::DisplayRole)
    {
       switch(index.column()) {
       case 0:
         return QString(fPs->find(id).value().name);
         break;
       case 1:
         return QString::number(fPs->find(id).value().panValue) + "x" + QString::number(fPs->find(id).value().tiltValue);
         break;
       }
    }

    if (role == Qt::BackgroundColorRole && (index.column() == 0 || index.column() == 1) && id == currentFixedPointId ) {
        return QColor("#a2c7fb");
    }

    if (role == Qt::DecorationRole && index.column() == 2 ) {
        if(fPs->find(id).value().timelapseMember == 1)return QColor("#19c6ee");
        return QColor("#d3f9fe");
    }


    if (role == Qt::DecorationRole && index.column() == 3 ) {
        return QColor("#fc757b");
    }


    if (role == Qt::ToolTipRole) {
        return id;
    }

    if (role == Qt::InitialSortOrderRole && index.column() == 4) {
        return fPs->find(id).value().panValue;
    }

    return QVariant();
}

void bFixedPointModel::_onFixedPointsUpdated(void) {
//    qDebug() << "fPs updated";

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

//    sort(4);
    reset();
}

void bFixedPointModel::_onCellClicked ( const QModelIndex index ) {
    QString id = index.data(Qt::ToolTipRole).toString();

    if(index.column() == 2) {
        emit toggleTimelapseFixedPointClicked(id);

        qDebug() << "add to TL" << id;
    }

    if(index.column() == 3) {
        emit removeFixedPointClicked(id);

        qDebug() << "remove FP clicked: " << id;
    }

    if(index.column() == 0 or index.column() == 1) {
        emit selectFixedPointClicked(id);

        qDebug() << "select FP clicked: " << id;
    }
}

void bFixedPointModel::selectFixedPoint(QString id) {
    currentFixedPointId = id;
}
