#include "QtEmu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEmu w;
    w.show();

    return a.exec();
}
