#ifndef EQEPINT_H
#define EQEPINT_H

#include <QObject>
#include <QThread>
#include <string>

class eqepInt : public QThread
{
    Q_OBJECT

private:
    void pollingLoop(unsigned int eqep);
    unsigned int eqepNum;
    int currentValue, oldValue;
    int topLimit;
    int bottomLimit;
    int offset;

protected:
    void run(void);

public:
    explicit eqepInt(unsigned int eqep, QObject *parent = 0);

    static int eqep_fd_close(int fd);
    static int eqep_get_value(std::string eqep_filename, int *value);
    static int eqep_fd_open(std::string eqep_filename);



signals:
//     void gpioEdge(unsigned int, bool);
    void newValue(int);
    
public slots:
    
};

#endif // EQEPINT_H
