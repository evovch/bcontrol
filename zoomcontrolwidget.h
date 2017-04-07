#ifndef ZOOMCONTROLWIDGET_H
#define ZOOMCONTROLWIDGET_H

#include <QWidget>

#include "motorcontrolwidget.h"

namespace Ui {
    class zoomControlWidget;
}

class zoomControlWidget : public motorControlWidget
{
    Q_OBJECT

public:
    explicit zoomControlWidget(QWidget *parent = 0);

    ~zoomControlWidget();

private:
    Ui::zoomControlWidget *ui;
};

#endif // ZOOMCONTROLWIDGET_H
