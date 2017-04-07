#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QWidget>

namespace Ui {
    class network;
}

class network : public QWidget
{
    Q_OBJECT
    
public:
    explicit network(QWidget *parent = 0);
    ~network();
    
private:
    Ui::network *ui;
};

#endif // NETWORKWIDGET_H
