
#include "qtmini.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    auto wid = new QtMini;
    wid->show();
    return a.exec();
}
