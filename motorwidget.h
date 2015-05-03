#ifndef MOTORWIDGET_H
#define MOTORWIDGET_H

#include <QWidget>

namespace Ui {
class motorWidget;
}

class motorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit motorWidget(QWidget *parent = 0);
    ~motorWidget();

    void init(QString ms);
    void setPosition(int pos);
    void setPowerControl(bool state);

private:
    Ui::motorWidget *ui;
    QString motorSuffix;

signals:
    void doSeek(QString, int);
    void doSetNull(QString);
    void doSetCenter(QString);
    void doSetLimit(QString);
    void doResetLimit(QString);
    void doPower(QString);

public slots:
    void _onSeekPressed(void);
    void _onNullPressed(void);
    void _onCenterPressed(void);
    void _onLimitPressed(void);
    void _onResetPressed(void);
    void _onPowerPressed(void);
};



#endif // MOTORWIDGET_H
