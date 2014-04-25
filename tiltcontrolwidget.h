#ifndef TILTCONTROLWIDGET_H
#define TILTCONTROLWIDGET_H

#include <QWidget>
#include "motorcontrolwidget.h";

namespace Ui {
class tiltControlWidget;
}

class tiltControlWidget : public motorControlWidget
{
    Q_OBJECT
    
public:
    explicit tiltControlWidget(QWidget *parent = 0);
    ~tiltControlWidget();
    
private:
    Ui::tiltControlWidget *ui;
};

#endif // TILTCONTROLWIDGET_H
