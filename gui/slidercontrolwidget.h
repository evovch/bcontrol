#ifndef SLIDERCONTROLWIDGET_H
#define SLIDERCONTROLWIDGET_H

#include "motorcontrolwidget.h"

namespace Ui {
    class sliderControlWidget;
}

class sliderControlWidget : public motorControlWidget
{
    Q_OBJECT
    
public:
    explicit sliderControlWidget(QWidget *parent = 0);
    ~sliderControlWidget();
    
private:
    Ui::sliderControlWidget *ui;

};

#endif // SLIDERCONTROLWIDGET_H
