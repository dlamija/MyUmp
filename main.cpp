#include "myump.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    MyUmp *w;

    QCoreApplication::setOrganizationName("Pakciktua");
    QCoreApplication::setOrganizationDomain("pakciktua.org");
    QCoreApplication::setApplicationName("UMPApps");

    w = new MyUmp(&window);

    return a.exec();
}
