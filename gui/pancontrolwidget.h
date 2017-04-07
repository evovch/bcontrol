#ifndef PANCONTROLWIDGET_H
#define PANCONTROLWIDGET_H

#include <QWidget>

#include "motorcontrolwidget.h"

namespace Ui {
    class panControlWidget;
}

class panControlWidget : public motorControlWidget
{
    Q_OBJECT

public:
    explicit panControlWidget(QWidget *parent = 0);

    ~panControlWidget();

private:
    Ui::panControlWidget *ui;
};

#endif // PANCONTROLWIDGET_H
