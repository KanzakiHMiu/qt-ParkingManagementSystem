#include "bill.h"
#include "ui_bill.h"
#include "firstpage.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QUrlQuery>
extern QString p;

bill::bill(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bill)
    , NetManager(new netManager(this))
{
    ui->setupUi(this);

    loadBillingHistory();
    connect(NetManager, &netManager::loadBillingHistoryReply,
            this, &bill::onLoadBillingHistoryReply);
    connect(NetManager, &netManager::networkError,
            this, &bill::onNetworkError);
}

bill::~bill()
{
    delete ui;
}

void bill::on_btnback_clicked()
{
    firstpage *f=new firstpage();
    this->close();
    f->show();
}

void bill::onNetworkError(const QString &errorString)
{
    qDebug() << "Error:" << errorString;
    QMessageBox::warning(this, "网络错误", "无法连接到服务器，请稍后重试！");
}

void bill::loadBillingHistory(){
    QUrl url("http://*:8689/user/billing_history");

    QUrlQuery query;
    query.addQueryItem("phone", p);
    url.setQuery(query);

    NetManager->getRequest(url);
}

void bill::onLoadBillingHistoryReply(QNetworkReply* reply){
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "success") {
        QJsonArray dataArray = jsonObject["data"].toArray();

        tabModel = new QStandardItemModel(dataArray.size(), 5, this);
        tabModel->setHeaderData(0, Qt::Horizontal, "账单ID");
        tabModel->setHeaderData(1, Qt::Horizontal, "用户ID");
        tabModel->setHeaderData(2, Qt::Horizontal, "订单ID");
        tabModel->setHeaderData(3, Qt::Horizontal,"时间");
        tabModel->setHeaderData(4, Qt::Horizontal,"金额");

        for (int i = 0; i < dataArray.size(); ++i) {
            QJsonObject item = dataArray[i].toObject();
            tabModel->setItem(i, 0, new QStandardItem(QString::number(item["bill_id"].toInt())));
            tabModel->setItem(i, 1, new QStandardItem(QString::number(item["order_id"].toInt())));
            tabModel->setItem(i, 2, new QStandardItem(QString::number(item["user_id"].toInt())));
            tabModel->setItem(i, 3, new QStandardItem(item["payment_date"].toString()));
            tabModel->setItem(i, 4, new QStandardItem(QString::number(item["amount"].toDouble(), 'f', 2)));
        }

        ui->billtab->setModel(tabModel);
        ui->billtab->setColumnHidden(0, 1);
        ui->billtab->setColumnHidden(1, 1);
        ui->billtab->setColumnHidden(2, 1);
        ui->billtab->setColumnWidth(3, 300);
        ui->billtab->setColumnWidth(4, 100);
        ui->billtab->update();
    } else {
        QMessageBox::warning(this, "加载失败", jsonObject["message"].toString());
    }
}
