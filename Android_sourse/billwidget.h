#ifndef BILLWIDGET_H
#define BILLWIDGET_H

#include <QWidget>

namespace Ui {
class billwidget;
}

class billwidget : public QWidget
{
    Q_OBJECT

public:
    explicit billwidget(QWidget *parent = nullptr);
    ~billwidget();

private:
    Ui::billwidget *ui;
};

#endif // BILLWIDGET_H
