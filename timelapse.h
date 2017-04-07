#ifndef TIMELAPSE_H
#define TIMELAPSE_H

#include <QWidget>

namespace Ui {
    class timelapse;
}

class timelapse : public QWidget
{
    Q_OBJECT
    
public:
    explicit timelapse(QWidget *parent = 0);
    ~timelapse();
    
private:
    Ui::timelapse *ui;
};

#endif // TIMELAPSE_H
