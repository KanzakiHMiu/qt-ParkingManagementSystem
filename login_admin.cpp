#include "login_admin.h"
#include "ui_login_admin.h"
#include "mainwindow.h"
#include <QMessageBox>

login_admin::login_admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_admin)
    , dbManager()
{
    ui->setupUi(this);

    // 初始化数据库
    dbManager.initializeDatabase();
}

login_admin::~login_admin()
{
    delete ui;
}

void login_admin::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();

    if (!dbManager.loginAdmin(username, password)) {
        // 查询结果为空，用户名和密码不匹配，登录失败
        qDebug() << "Login failed!";
        QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重试！");
    } else {
        // 查询结果非空，用户名和密码匹配，登录成功
        qDebug() << "Login successful!";
        QMessageBox::information(this, "登录成功", "登录成功！");
        MainWindow* w = new MainWindow;
        w->show();
        this->close();
    }
}
