#ifndef BFIXEDPOINTMODEL_H
#define BFIXEDPOINTMODEL_H

#include <QAbstractTableModel>
#include "btypes.h"

class bFixedPointModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit bFixedPointModel(QObject *parent = 0, fixedPointHash *fp = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void selectFixedPoint(QString id);

private:
    fixedPointHash *fPs;
    QString currentFixedPointId;

signals:
    void removeFixedPointClicked(QString id);
    void selectFixedPointClicked(QString id);
    void toggleTimelapseFixedPointClicked(QString id);
    void selectRow(int row) const;
    
public slots:
    void _onFixedPointsUpdated(void);
    void _onCellClicked ( const QModelIndex index );
};

#endif // BFIXEDPOINTMODEL_H
