#include "eqepint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#include <QDebug>

#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

eqepInt::eqepInt(unsigned int eqep, QObject *parent) :
    QThread(parent)
{
    eqepNum = eqep;
}

void eqepInt::run(void) {
    pollingLoop(eqepNum);
}

void eqepInt::pollingLoop(unsigned int eqep)
{
    std::string eqep_filename;
    switch(eqep){
        case 0:
            eqep_filename = "/sys/devices/ocp.3/48300000.epwmss/48300180.eqep/position";
            break;
        case 1:
            eqep_filename = "/sys/devices/ocp.3/48302000.epwmss/48302180.eqep/position";
            break;
        case 2:
            eqep_filename = "/sys/devices/ocp.3/48304000.epwmss/48304180.eqep/position";
            break;
    }

    struct pollfd fdset[2];
    int nfds = 2;
    int eqep_fd, timeout, rc;

    timeout = POLL_TIMEOUT;

    while (1) {
        eqep_fd = open(eqep_filename.c_str(), O_RDWR);

        char buf[MAX_BUF];
        memset((void*)fdset, 0, sizeof(fdset));

        fdset[0].fd = eqep_fd;
        fdset[0].events = POLLPRI;

        char          dummy;
        read(fdset[0].fd, &dummy, 1);

        rc = poll(fdset, 1, -1);

        if (rc < 0) {
            printf("\npoll() failed!\n");
            return;
        }

        if (rc == 0) {
            printf(".");
        }

        if (fdset[0].revents & POLLPRI) {
            int len;

            int v;
            eqep_get_value(eqep_filename, &v);

            qDebug() << "eqep value: " << v;

//            printf("\npoll() GPIO %d interrupt occurred\n", gpio);

//            if(v == 1)emit gpioEdge(gpio, true);
//            else emit gpioEdge(gpio, false);

//            Sleeper::msleep(500);
        }
        close(eqep_fd);
    }



}

int eqepInt::eqep_get_value(std::string eqep_filename, int *value)
{
    int fd;
    char ch[10];

    fd = open(eqep_filename.c_str(), O_RDONLY);
    if (fd < 0) {
        perror("eqep/get-value");
        return fd;
    }

    read(fd, &ch, 10);

    *value = atoi(ch);

    close(fd);
    return 0;
}


int eqepInt::eqep_fd_open(std::string eqep_filename)
{
    int fd;

    fd = open(eqep_filename.c_str(), O_RDONLY | O_NONBLOCK );
    if (fd < 0) {
        perror("gpio/fd_open");
    }
    return fd;
}

int eqepInt::eqep_fd_close(int fd)
{
    return close(fd);
}
