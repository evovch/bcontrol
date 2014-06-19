#include "bcamparammodel.h"

bCamParamModel::bCamParamModel(QMap<int, QString> *bm, int defaultMap, QObject *parent) :
    QAbstractTableModel(parent)
{
    if(bm!=0)baseMap = bm;
    else {
        initDefaultStructs();
        switch(defaultMap){
            case bCamParamModel::dMapId:
                baseMap = &dMap;
            break;
            case bCamParamModel::sMapId:
                baseMap = &sMap;
            break;
            case bCamParamModel::afMapId:
                baseMap = &afMap;
            break;
            case bCamParamModel::modeMapId:
                baseMap = &modeMap;
            break;
            case bCamParamModel::isoMapId:
                baseMap = &isoMap;
            break;
        }
    }
}

int bCamParamModel::rowCount(const QModelIndex & /*parent*/) const
{
   int s = baseMap->size();

//   qDebug() << s;

   return s;
}

int bCamParamModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant bCamParamModel::data(const QModelIndex &index, int role) const
{
    QList<int> ks = baseMap->keys();
    if( ks.size() == 0)return QString("");

    int key = ks[index.row()];

    if (role == Qt::DisplayRole)
    {
       switch(index.column()) {
       case 0:
         return QString::number(key);
         break;
       case 1:
         return QString(baseMap->find(key).value());
         break;
       }
    }

    return QVariant();
}

int bCamParamModel::getKey(int index) {
    QList<int> ks = baseMap->keys();
    return ks[index];
}

int bCamParamModel::getIndex(int key) {
    QList<int> ks = baseMap->keys();
    return ks.indexOf(key);
}

void bCamParamModel::initDefaultStructs() {
    dMap.insert(1, "2.8");
    dMap.insert(2, "3.2");
    dMap.insert(5, "5.1");

    sMap.insert(1, "1/350");
    sMap.insert(2, "1/4000");

    modeMap.insert(1, "P");
    modeMap.insert(2, "M");
    modeMap.insert(3, "S");
    modeMap.insert(4, "A");

    afMap.insert(1, "on");
    afMap.insert(2, "off");

    isoMap.insert(1, "100");
    isoMap.insert(2, "3200");
}
