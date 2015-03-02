#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    if(argc < 2) {
        qDebug() << "specify delay (sec)";
    }

    qDebug() << argv[2];

    return a.exec();
}
