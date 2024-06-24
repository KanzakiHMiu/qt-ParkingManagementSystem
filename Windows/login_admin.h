#ifndef LOGIN_ADMIN_H
#define LOGIN_ADMIN_H

#include <QWidget>
#include <QKeyEvent>
#include "netmanager.h"

namespace Ui {
class login_admin;
}

class login_admin : public QWidget
{
    Q_OBJECT

public:
    explicit login_admin(QWidget *parent = nullptr);
    ~login_admin();
    void handleSeccessfulLogin();

private slots:
    void on_pushButton_login_clicked();
    void onLoginReply(QNetworkReply*);

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        {
            on_pushButton_login_clicked();
        }
        QWidget::keyPressEvent(event);
    }

private:
    Ui::login_admin *ui;
    netManager *NetManager;
};

#endif // LOGIN_ADMIN_H
