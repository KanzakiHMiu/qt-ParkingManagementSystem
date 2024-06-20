#include "pay.h"
#include "ui_pay.h"
#include<QtSql>
#include<QString>
#include<QMessageBox>
#include"walet.h"
extern QString p;
pay::pay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pay)
{
    ui->setupUi(this);
}

pay::~pay()
{
    delete ui;
}



void pay::on_backbtn_clicked()
{
    walet *w=new walet();
    this->close();
    w->show();
}


void pay::on_paybtn_clicked()
{
    //QString spotId = currentItem->data(Qt::UserRole).toString();

    // 获取当前时间作为预约时间
    //QString reservationTime = QDateTime::currentDateTime().toString(Qt::ISODate);
    QString m=ui->money->text();
    //QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    // 更新车位状态
    query.prepare("UPDATE wallets SET balance = ? + balance WHERE user_id =(select user_id from users where phone= ?)");
    query.addBindValue(m);
    query.addBindValue(p);
    if (query.exec()) {
        QMessageBox::information(this, "提示", "充值成功");
        walet *w=new walet();


        this->close();
        w->show();
        w->loadData();
    }
    else if (!query.exec()) {
        QMessageBox::critical(this, "充值失败", query.lastError().text());
        return;
    }


}

