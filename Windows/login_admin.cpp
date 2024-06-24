#include "login_admin.h"
#include "ui_login_admin.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

login_admin::login_admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_admin)
    , NetManager(new netManager(this))
{
    ui->setupUi(this);

    connect(NetManager, &netManager::loginReply,
            this, &login_admin::onLoginReply);
    connect(NetManager, &netManager::networkError,
            this, &login_admin::onNetworkError);
}

login_admin::~login_admin()
{
    delete ui;
}

void login_admin::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();

    QUrl url("http://*:8689/admin/login");

    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    NetManager->postRequest(url, data);
}

void login_admin::onLoginReply(QNetworkReply* reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "Login successful") {
        QMessageBox::information(this, "登录成功", "登录成功！");
        MainWindow* w = new MainWindow;
        w->show();
        this->close();
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重试！");
    }
}

void login_admin::onNetworkError(const QString &errorString)
{
    qDebug() << "Error:" << errorString;
    QMessageBox::warning(this, "网络错误", "无法连接到服务器，请稍后重试！");
}
