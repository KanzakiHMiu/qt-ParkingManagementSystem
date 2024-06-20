#include "walet.h"
#include "ui_walet.h"
#include"pay.h"
#include"first.h"
extern QString p;
walet::walet(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::walet)
{
    ui->setupUi(this);
    loadData();

}

walet::~walet()
{
    delete ui;
}

void walet::on_paybtn_clicked()
{
    pay *p=new pay();
    this->close();
    p->show();
}


void walet::on_backbtn_clicked()
{
    first *f=new first();
    this->close();
    f->loadData();
    f->show();
}

void walet::loadData()
{

    QSqlQuery query;
    query.prepare("SELECT * FROM wallets WHERE user_id =(select user_id from users where phone= ?)");// 修改为你的表名和条件
    query.addBindValue(p);
    qDebug()<<query.value("balance").toString();
    if (query.exec() && query.next())
    {
        ui->balance->setText(query.value("balance").toString());
    } else {
        qDebug() << "Load Data Error: " << query.lastError().text();
    }
}


