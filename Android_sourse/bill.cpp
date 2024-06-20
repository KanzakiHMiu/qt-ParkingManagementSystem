#include "bill.h"
#include "ui_bill.h"
#include"first.h"
#include<QSqlTableModel>
#include<QMessageBox>
#include<QSqlError>
#include<QDataWidgetMapper>
bill::bill(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bill)
{
    ui->setupUi(this);
    openDB();
}

bill::~bill()
{
    delete ui;
}
bool bill::openDB()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loginpage");
    db.setUserName("root");
    db.setPassword("123");
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
    }
    else
    {
        QStringList name=db.tables();
        qDebug()<<name.at(0);
        openTable();

    }
    qDebug() << "Connected to database!";
}
bool bill::openTable()
{
    tabModel = new QSqlTableModel(this,db);
    tabModel->setTable("billing_history");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setSort(tabModel->fieldIndex("bill_id"),Qt::AscendingOrder);

    if(!(tabModel->select()))
    {QMessageBox::critical(this,"错误","打开数据表错误:\n"+tabModel->lastError().text());}
    qDebug()<<"aaaa";

    int rowCount = tabModel->rowCount();
    qDebug() << "Number of rows in the model:" << rowCount;
    QModelIndex index = tabModel->index(0, 2); // 获取第一行第一列的数据
    QVariant data = tabModel->data(index);
    qDebug() << "Data at index (0, 2):" << data.toString();


    tabModel->setHeaderData(tabModel->fieldIndex("payment_date"),Qt::Horizontal,"时间");
    tabModel->setHeaderData(tabModel->fieldIndex("amount"),Qt::Horizontal,"金额");
    ui->billtab->setModel(tabModel);

    ui->billtab->setColumnHidden(tabModel->fieldIndex("user_id"),true);
    ui->billtab->setColumnHidden(tabModel->fieldIndex("order_id"),true);
    ui->billtab->setColumnHidden(tabModel->fieldIndex("bill_id"),true);
    ui->billtab->setColumnWidth(3, 300);  // 设置第一列的宽度为 100 像素

    ui->billtab->update();
}

void bill::on_btnback_clicked()
{
    first *f=new first();
    this->close();

}

