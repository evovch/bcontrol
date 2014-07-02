#ifndef FHEAD_H
#define FHEAD_H

#include <QWidget>

namespace Ui {
class fhead;
}

class fhead : public QWidget
{
    Q_OBJECT

public:
    explicit fhead(QWidget *parent = 0);
    ~fhead();

signals:
    void afChanged(bool);
    void srChanged(bool);
    void afAndCaptureKey(void);
    void fpPressed(void);

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:
    Ui::fhead *ui;
};

#endif // FHEAD_H
