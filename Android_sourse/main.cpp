#include "widget.h"

#include <QApplication>
#include<QTableWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
