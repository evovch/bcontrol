#ifndef GPIOINT_H
#define GPIOINT_H

//#include <QObject>
#include <QThread>
#include <string>

class gpioInt : public QThread
{
    Q_OBJECT

public:
    explicit gpioInt(unsigned int gpio, QObject *parent = 0);
    void setOutput(void);
    void setValue(unsigned int value);

    static int gpio_export(unsigned int gpio);
    static int gpio_unexport(unsigned int gpio);
    static int gpio_set_dir(unsigned int gpio, unsigned int out_flag);
    static int gpio_set_value(unsigned int gpio, unsigned int value);
    static int gpio_get_value(unsigned int gpio, unsigned int *value);
    static int gpio_set_edge(unsigned int gpio, char *edge);
    static int gpio_fd_open(unsigned int gpio);
    static int gpio_fd_close(int fd);

    static int eqep_get_value(std::string eqep_filename, unsigned int *value);
    static int eqep_fd_open(std::string eqep_filename);

protected:
    void run(void);

signals:
     void gpioEdge(unsigned int, bool);
    
public slots:
    
private:
    void pollingLoop(unsigned int gpio);
    void pollingLoopEqep(unsigned int eqep);
    unsigned int gpioNum;

};


class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs) {QThread::usleep(usecs);}
    static void msleep(unsigned long msecs) {QThread::msleep(msecs);}
    static void sleep(unsigned long secs) {QThread::sleep(secs);}
};

#endif // GPIOINT_H
