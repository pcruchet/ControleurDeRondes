#include <QApplication>
#include "mainwindowconfigurationrondier.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowConfigurationRondier w;

    w.show();

    return a.exec();
}
