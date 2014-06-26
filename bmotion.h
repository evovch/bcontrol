#ifndef BMOTION_H
#define BMOTION_H

#include <QWidget>
#include <qDebug>

namespace Ui {
class bmotion;
}

class bmotion : public QWidget
{
    Q_OBJECT
    
public:
    explicit bmotion(QWidget *parent = 0);
    ~bmotion();
    
    void mouseMoveEvent( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event );

private:
    Ui::bmotion *ui;
    bool trackingOn;

signals:
    void virtualX(int);
    void virtualY(int);

};

#endif // BMOTION_H
