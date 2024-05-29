#ifndef MYINFO_H
#define MYINFO_H

#include <QWidget>

namespace Ui {
class myinfo;
}

class myinfo : public QWidget
{
    Q_OBJECT

public:
    explicit myinfo(QWidget *parent = nullptr);
    ~myinfo();

private:
    Ui::myinfo *ui;
};

#endif // MYINFO_H
