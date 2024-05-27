#ifndef SYSABOUT_H
#define SYSABOUT_H

#include <QWidget>

namespace Ui {
class sysAbout;
}

class sysAbout : public QWidget
{
    Q_OBJECT

public:
    explicit sysAbout(QWidget *parent = nullptr);
    ~sysAbout();

private:
    Ui::sysAbout *ui;
};

#endif // SYSABOUT_H
