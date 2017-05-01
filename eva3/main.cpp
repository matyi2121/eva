#include "awari.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    awari w;
    w.show();

    return a.exec();
}
