#include "login_admin.h"
#include "ui_login_admin.h"
#include "mainwindow.h"
#include <QMessageBox>

login_admin::login_admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_admin)
    , nwManager(new NetworkManager(this))
{
    ui->setupUi(this);

    connect(nwManager, &NetworkManager::loginFinished,
            this, &login_admin::onLoginFinished);
    connect(nwManager, &NetworkManager::requestTimeout,
            this, &login_admin::onRequestTimeout);
}

login_admin::~login_admin()
{
    delete ui;
}

void login_admin::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();

    nwManager->loginAdmin(username, password);
}

void login_admin::onLoginFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << "Login successful:" << response;
        QMessageBox::information(this, "登录成功", "登录成功！");
        MainWindow* w = new MainWindow;
        w->show();
        this->close();
    } else {
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        int status = statusCode.toInt();
        if (status == 401) {
            qDebug() << "Unauthorized: " << reply->errorString();
            QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重试！");
        } else {
            qDebug() << "Error:" << reply->errorString();
            QMessageBox::warning(this, "登录失败", "登录时发生错误，请重试！");
        }
    }
    reply->deleteLater();
}

void login_admin::onRequestTimeout()
{
    QMessageBox::warning(this, "请求超时", "请求超时，请检查网络连接并重试！");
}
