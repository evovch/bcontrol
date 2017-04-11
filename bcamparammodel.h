#ifndef BCAMPARAMMODEL_H
#define BCAMPARAMMODEL_H

#include <QAbstractTableModel>

class bCamParamModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit bCamParamModel(QList<QString> *bm = NULL, int defaultMap = 0, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int getIndex(QString key);
    QString getValue(int index);

    enum {foo, dMapId, sMapId, afMapId, modeMapId, isoMapId, expMapId, focusmetermodeMapId}; //TODO no name enum - ?

private:
    QList<QString> *baseMap; //TODO pointer to the list of strings - wat?

    QList<QString> dMap;
    QList<QString> sMap;
    QList<QString> afMap;
    QList<QString> isoMap;
    QList<QString> modeMap;
    QList<QString> expMap;
    QList<QString> focusmetermodeMap;

    void initDefaultStructs();

signals:
    
public slots:
    
};

#endif // BCAMPARAMMODEL_H
