#include "pay.h"
#include "ui_pay.h"
#include "wallet.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
extern QString p;

pay::pay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pay)
    , NetManager(new netManager(this))
{
    ui->setupUi(this);

    connect(NetManager, &netManager::rechargeReply,
            this, &pay::onRechargeReply);
    connect(NetManager, &netManager::networkError,
            this, &pay::onNetworkError);
}

pay::~pay()
{
    delete ui;
}

void pay::onNetworkError(const QString &errorString)
{
    qDebug() << "Error:" << errorString;
    QMessageBox::warning(this, "网络错误", "无法连接到服务器，请稍后重试！");
}

void pay::on_backbtn_clicked()
{
    wallet *w = new wallet();
    this->close();
    w->show();
}

void pay::on_paybtn_clicked()
{
    QString m = ui->money->text();
    QUrl url("http://*:8689/user/recharge");

    QJsonObject json;
    json["phone"] = p;
    json["amount"] = m.toDouble();
    json["last_recharge_date"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    NetManager->putRequest(url, data);
}

void pay::onRechargeReply(QNetworkReply* reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "Recharge successful") {
        QMessageBox::information(this, "提示", "充值成功");
        wallet *w = new wallet();
        this->close();
        w->loadWalletData();
        w->show();
    } else {
        QMessageBox::critical(this, "充值失败", jsonObject["message"].toString());
    }
}
