#include "login_admin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login_admin w;
    w.show();
    return a.exec();
}
