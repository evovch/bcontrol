#include "bcamparammodel.h"
#include <QDebug>

bCamParamModel::bCamParamModel(QList<QString> *bm, int defaultMap, QObject *parent) :
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
    if( baseMap->size() == 0)return QString("");

    if (role == Qt::DisplayRole)
    {
       switch(index.column()) {
       case 0:
         return QString::number(index.row());
         break;
       case 1:
           return QString(baseMap->at(index.row()));
         break;
       }
    }

    return QVariant();
}

QString bCamParamModel::getValue(int index) {
    return baseMap->at(index);
}

int bCamParamModel::getIndex(QString key) {
    if(key=="")return(0);
    qDebug() << "searching index: " << key;
    return baseMap->indexOf(key);
}

void bCamParamModel::initDefaultStructs() {
    dMap.append("f/2.8");
    dMap.append("f/3.2");
    dMap.append("f/4");
    dMap.append("f/4.5");
    dMap.append("f/5");
    dMap.append("f/5.6");
    dMap.append("f/6.3");
    dMap.append("f/7.1");
    dMap.append("f/8");
    dMap.append("f/9");
    dMap.append("f/10");
    dMap.append("f/11");
    dMap.append("f/12");
    dMap.append("f/13");
    dMap.append("f/14");
    dMap.append("f/18");
    dMap.append("f/20");
    dMap.append("f/22");

    sMap.append("1/8000");
    sMap.append("1/6400");
    sMap.append("1/5000");
    sMap.append("1/4000");
    sMap.append("1/3200");
    sMap.append("1/2500");
    sMap.append("1/2000");
    sMap.append("1/1600");
    sMap.append("1/1250");
    sMap.append("1/1000");
    sMap.append("1/800");
    sMap.append("1/640");
    sMap.append("1/500");
    sMap.append("1/400");
    sMap.append("1/320");
    sMap.append("1/250");
    sMap.append("1/200");
    sMap.append("1/160");
    sMap.append("1/125");
    sMap.append("1/100");
    sMap.append("1/80");
    sMap.append("1/60");
    sMap.append("1/50");
    sMap.append("1/40");
    sMap.append("1/30");
    sMap.append("1/25");
    sMap.append("1/20");
    sMap.append("1/15");
    sMap.append("1/13");
    sMap.append("1/10");
    sMap.append("1/8");
    sMap.append("1/6");
    sMap.append("1/5");
    sMap.append("1/4");
    sMap.append("1/3");
    sMap.append("10/25");
    sMap.append("1/2");
    sMap.append("10/16");
    sMap.append("10/13");
    sMap.append("1");
    sMap.append("13/10");
    sMap.append("16/10");
    sMap.append("2");
    sMap.append("25/10");
    sMap.append("3");
    sMap.append("4");
    sMap.append("5");
    sMap.append("6");
    sMap.append("8");
    sMap.append("10");
    sMap.append("13");
    sMap.append("15");
    sMap.append("20");
    sMap.append("25");
    sMap.append("30");

    modeMap.append("M");
    modeMap.append("P");
    modeMap.append("A");
    modeMap.append("S");

    afMap.append("on");
    afMap.append("off");

    isoMap.append("50");
    isoMap.append("64");
    isoMap.append("80");
    isoMap.append("100");
    isoMap.append("125");
    isoMap.append("160");
    isoMap.append("200");
    isoMap.append("250");
    isoMap.append("320");
    isoMap.append("400");
    isoMap.append("500");
    isoMap.append("640");
    isoMap.append("800");
    isoMap.append("1000");
    isoMap.append("1250");
    isoMap.append("1600");
    isoMap.append("2000");
    isoMap.append("2500");
    isoMap.append("3200");
    isoMap.append("4000");
    isoMap.append("5000");
    isoMap.append("6400");
    isoMap.append("8000");
    isoMap.append("10000");
    isoMap.append("12800");
    isoMap.append("14400");
    isoMap.append("20000");
    isoMap.append("25600");
    isoMap.append("51200");
}
