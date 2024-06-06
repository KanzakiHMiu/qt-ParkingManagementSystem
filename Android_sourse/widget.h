#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<first.h>


extern QString p;
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnlogin_clicked();

    void on_btnreg_clicked();

private:
    Ui::Widget *ui;
    first *f;
};
#endif // WIDGET_H
