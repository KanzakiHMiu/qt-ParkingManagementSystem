#include "wallet.h"
#include "ui_wallet.h"
#include "pay.h"
#include "firstpage.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUrlQuery>
extern QString p;

wallet::wallet(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::wallet)
    , NetManager(new netManager(this))
{
    ui->setupUi(this);

    connect(NetManager, &netManager::loadWalletReply,
            this, &wallet::onLoadWalletReply);
    connect(NetManager, &netManager::networkError,
            this, &wallet::onNetworkError);
}

wallet::~wallet()
{
    delete ui;
}

void wallet::onNetworkError(const QString &errorString)
{
    qDebug() << "Error:" << errorString;
    QMessageBox::warning(this, "网络错误", "无法连接到服务器，请稍后重试！");
}

void wallet::on_paybtn_clicked()
{
    pay *p=new pay();
    this->close();
    p->show();
}

void wallet::on_backbtn_clicked()
{
    firstpage *f=new firstpage();
    this->close();
    f->show();
}

void wallet::loadWalletData()
{
    QUrl url("http://43.136.79.145:8689/user/wallet");

    QUrlQuery query;
    query.addQueryItem("phone", p);
    url.setQuery(query);

    NetManager->getRequest(url);
}

void wallet::onLoadWalletReply(QNetworkReply* reply){
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "success") {
        QJsonObject data = jsonObject["data"].toObject();
        ui->balance->setText(QString::number(data["balance"].toDouble(), 'f', 2));
    } else {
        QMessageBox::warning(this, "加载失败", jsonObject["message"].toString());
    }
}
