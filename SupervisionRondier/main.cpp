#include "supervisionrondier.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SupervisionRondier w;
    w.show();

    return a.exec();
}
