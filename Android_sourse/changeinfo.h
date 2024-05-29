#ifndef CHANGEINFO_H
#define CHANGEINFO_H

#include <QWidget>

namespace Ui {
class changeinfo;
}

class changeinfo : public QWidget
{
    Q_OBJECT

public:
    explicit changeinfo(QWidget *parent = nullptr);
    ~changeinfo();

private:
    Ui::changeinfo *ui;
};

#endif // CHANGEINFO_H
