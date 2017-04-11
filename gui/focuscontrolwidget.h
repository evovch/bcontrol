#ifndef FOCUSCONTROLWIDGET_H
#define FOCUSCONTROLWIDGET_H

#include "motorcontrolwidget.h"

namespace Ui {
    class focusControlWidget;
}

class focusControlWidget : public motorControlWidget
{
    Q_OBJECT

public:
    explicit focusControlWidget(QWidget *parent = 0);
    ~focusControlWidget();

private:
    Ui::focusControlWidget *ui;

};

#endif // FOCUSCONTROLWIDGET_H
