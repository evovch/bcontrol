#ifndef BCAMPARAMMODEL_H
#define BCAMPARAMMODEL_H

#include <QAbstractTableModel>

class bCamParamModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit bCamParamModel(QMap<int, QString> *bm = NULL, int defaultMap = 0, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int getKey(int index);
    int getIndex(int key);

    enum {foo, dMapId, sMapId, afMapId, modeMapId, isoMapId};

private:
    QMap<int, QString> *baseMap;

    QMap<int, QString> dMap;
    QMap<int, QString> sMap;
    QMap<int, QString> afMap;
    QMap<int, QString> isoMap;
    QMap<int, QString> modeMap;

    void initDefaultStructs();

signals:
    
public slots:
    
};

#endif // BCAMPARAMMODEL_H
