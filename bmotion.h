#ifndef BMOTION_H
#define BMOTION_H

#include <QWidget>

namespace Ui {
    class bmotion;
}

class bmotion : public QWidget
{
    Q_OBJECT
    
public:
    explicit bmotion(QWidget *parent = 0);
    ~bmotion();
    
    void mouseMoveEvent (QMouseEvent* event);
    void mousePressEvent (QMouseEvent* event);

signals:
    void virtualX(int);
    void virtualY(int);

private:
    Ui::bmotion *ui;
    bool trackingOn;

};

#endif // BMOTION_H
