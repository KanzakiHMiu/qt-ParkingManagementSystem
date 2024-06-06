#include "first.h"
#include<changeinfo.h>
#include "ui_changeinfo.h"
#include"widget.h"
#include<QtSql>
#include<QMessageBox>
extern QString p;
changeinfo::changeinfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::changeinfo)
{
    ui->setupUi(this);
    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loginpage");
    db.setUserName("root");
    db.setPassword("123");
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        return;
    }
    qDebug() << "Connected to database!";
    loadData();
}

changeinfo::~changeinfo()
{
    delete ui;
}

void changeinfo::on_btnback_clicked()
{
    first *f=new first();
    this->close();
    f->show();
}

void changeinfo::loadData()
{

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE phone = "+p); // 修改为你的表名和条件

    if (query.exec() && query.next())
    {
        ui->linename->setText(query.value("username").toString());
        ui->linephone->setText(query.value("phone").toString());
        ui->lineemail->setText(query.value("email").toString());
        ui->linecar->setText(query.value("car_plate").toString());
    } else {
        qDebug() << "Load Data Error: " << query.lastError().text();
    }
}

void changeinfo::on_btnsave_clicked()
{
    QString username = ui->linename->text();
    QString phone = ui->linephone->text();
    QString email = ui->lineemail->text();
    QString car_plate = ui->linecar->text();

    QSqlQuery query;
    query.prepare("UPDATE users SET username = ?, phone = ?, email = ?, car_plate = ? WHERE phone = "+p); // 修改为你的表名和条件
    query.addBindValue(username);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(car_plate);

    if (!query.exec()) {
        qDebug() << "Save Data Error: " << query.lastError().text();
        QMessageBox::critical(this, "Save Error", query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Data saved successfully.");
    }
}

