#ifndef BLABEL_H
#define BLABEL_H

#include <QLabel>

class bLabel : public QLabel
{
    Q_OBJECT

public:
    bLabel(QWidget *parent = 0);

public slots:
    void _onDataReceived(QString key, QString value);

};

#endif // BLABEL_H
