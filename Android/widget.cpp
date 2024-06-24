#include "widget.h"
#include "ui_widget.h"
#include "firstpage.h"
#include <QMovie>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDateTime>
QString p;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , NetManager(new netManager(this))
{
    ui->setupUi(this);

    QMovie *movie =new QMovie(this);
    movie->setFileName(":/sourse_images/background.gif");
    movie->start();

    connect(NetManager, &netManager::loginReply,
            this, &Widget::onLoginReply);
    connect(NetManager, &netManager::registerReply,
            this, &Widget::onRegisterReply);
    connect(NetManager, &netManager::networkError,
            this, &Widget::onNetworkError);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onNetworkError(const QString &errorString)
{
    qDebug() << "Error:" << errorString;
    QMessageBox::warning(this, "网络错误", "无法连接到服务器，请稍后重试！");
}

void Widget::on_btnlogin_clicked()
{
    QString phone = ui->username_2->text();
    QString password = ui->password_2->text();

    QUrl url("http://*:8689/user/login");

    QJsonObject json;
    json["phone"] = phone;
    json["password"] = password;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    NetManager->postRequest(url, data);
}

void Widget::onLoginReply(QNetworkReply* reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "Login successful") {
        QMessageBox::information(this, "登录成功", "登录成功！");
        firstpage *f= new firstpage();
        this->close();
        f->show();
        p=ui->username_2->text();
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重试！");
    }
}

void Widget::on_btnreg_clicked()
{
    QString phone = ui->username_3->text();
    QString password = ui->password_3->text();
    QString registrationDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    QUrl url("http://*:8689/user/register");

    QJsonObject json;
    json["phone"] = phone;
    json["password"] = password;
    json["registration_date"] = registrationDate;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    NetManager->postRequest(url, data);
}

void Widget::onRegisterReply(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "Registration successful") {
        QMessageBox::information(this, "注册成功", "正在返回登录界面！");
        ui->username_3->clear();
        ui->password_3->clear();
        ui->tabWidget->setCurrentIndex(0);
        ui->tabWidget->update();
    } else {
        QMessageBox::warning(this, "注册失败", "用户名已存在，请重试！");
    }
}
