/*This program is Licensed under the GNU GPL V3. This program uses Qt opensource
 * which uses the GPL V3, except for the Qt Sql library. The Qt Sql library is
 *licensed under the GNU LGPL V3 https://www.gnu.org/licenses/lgpl-3.0.html
 * This program also uses SQlite which is in the public domain, see sqlite.org for more information.*/
#include "mainwindow.h"

#include <QApplication>
#include <QInputMethod>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
