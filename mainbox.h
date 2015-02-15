#ifndef MAINBOX_H
#define MAINBOX_H

#include <QWidget>

namespace Ui {
class mainBox;
}

class mainBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit mainBox(QWidget *parent = 0);
    ~mainBox();
    
private:
    Ui::mainBox *ui;
};

#endif // MAINBOX_H
