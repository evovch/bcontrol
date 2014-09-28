#ifndef LIMITSWINDOW_H
#define LIMITSWINDOW_H

#include <QWidget>

namespace Ui {
class limitsWindow;
}

class limitsWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit limitsWindow(QWidget *parent = 0);
    ~limitsWindow();
    
private:
    Ui::limitsWindow *ui;
};

#endif // LIMITSWINDOW_H
