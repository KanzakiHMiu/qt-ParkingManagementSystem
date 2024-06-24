#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "netmanager.h"

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
    void onLoginReply(QNetworkReply*);

    void on_btnreg_clicked();
    void onRegisterReply(QNetworkReply*);

    void onNetworkError(const QString&);

private:
    Ui::Widget *ui;
    netManager *NetManager;
};
#endif // WIDGET_H
