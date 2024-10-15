#include "connectmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connectMainWindow w;
    w.show();

    return a.exec();
}
