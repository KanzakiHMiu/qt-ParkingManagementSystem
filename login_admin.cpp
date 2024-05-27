#include "login_admin.h"
#include "ui_login_admin.h"
#include "mainwindow.h"

login_admin::login_admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_admin)
{
    ui->setupUi(this);

}

login_admin::~login_admin()
{
    delete ui;
}

void login_admin::on_pushButton_login_clicked()
{
    if (ui->lineEdit_account->text() == "a" && ui->lineEdit_password->text() == "a") {
        MainWindow* w = new MainWindow;
        w->show();
        this->close();
    }
}

