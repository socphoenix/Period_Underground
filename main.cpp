/*This program is Licensed under the GNU GPL V3 */
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QInputMethod>

static void extracted(QApplication &a) {
    a.setAutoSipEnabled(false);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    extracted(a);

    MainWindow w;
    w.show();
    return a.exec();
}
