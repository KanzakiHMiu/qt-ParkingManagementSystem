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
}

login_admin::~login_admin()
{
    delete ui;
}

void handleLogin(const QString& username, const QString& password, netManager*& NetManager) {
    QUrl url("http://*:8689/admin/login");

    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    NetManager->postRequest(url, data);
}

QString handleLoginResponseStatus(const QByteArray& response) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    return jsonObject["status"].toString();
}

QString handleLoginResponseErrors(const QByteArray& response) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    return jsonObject["error"].toString();
}

void login_admin::handleSeccessfulLogin()
{
    MainWindow* w = new MainWindow;
    w->show();
    this->close();
}

void login_admin::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();

    handleLogin(username, password, NetManager);
}

void login_admin::onLoginReply(QNetworkReply* reply)
{
    QByteArray response = reply->readAll();
    if (handleLoginResponseErrors(response) == "Invalid request") {
        QMessageBox::warning(this, "登陆失败", "无效的请求，请联系软件维护人员！");
    } else if (handleLoginResponseStatus(response) == "Internal Server Error") {
        QMessageBox::warning(this, "登陆失败", "服务端错误，请联系服务器维护人员！");
    } else if (handleLoginResponseStatus(response) == "Unauthorized") {
        QMessageBox::warning(this, "登陆失败", "用户名或密码错误，请重试！");
    } else if (handleLoginResponseStatus(response) == "Login successful") {
        QMessageBox::information(this, "登录成功", "登录成功！");
        handleSeccessfulLogin();
    }
}


