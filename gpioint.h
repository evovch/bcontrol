#ifndef GPIOINT_H
#define GPIOINT_H

#include <QObject>

class gpioInt : public QObject
{
    Q_OBJECT

private:
    static int gpio_export(unsigned int gpio);
    static int gpio_unexport(unsigned int gpio);
    static int gpio_set_dir(unsigned int gpio, unsigned int out_flag);
    static int gpio_set_value(unsigned int gpio, unsigned int value);
    static int gpio_get_value(unsigned int gpio, unsigned int *value);
    static int gpio_set_edge(unsigned int gpio, char *edge);
    static int gpio_fd_open(unsigned int gpio);
    static int gpio_fd_close(int fd);

    void gpioInt::pollingLoop(int gpio);

public:
    explicit gpioInt(int gpio, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // GPIOINT_H
