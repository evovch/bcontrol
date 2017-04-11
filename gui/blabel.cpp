#include "blabel.h"

bLabel::bLabel(QWidget *parent) : QLabel(parent)
{
}

void bLabel::_onDataReceived(QString key, QString value)
{
    if (key=="s_p") setText(value);
}
