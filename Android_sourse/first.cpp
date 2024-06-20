#include "first.h"
#include "ui_first.h"
#include<QtSql>
#include"walet.h"
#include"bill.h"
#include<QMessageBox>
#include<QDataWidgetMapper>
extern QString p;
first::first(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::first)
    , currentIndex(0)
{
    ui->setupUi(this);

    openDB();
    // 设置 QTimer 定时切换图像
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &first::showNextImage);
    timer->start(4000);

    // 创建透明度效果
    currentEffect = new QGraphicsOpacityEffect(ui->changeimage->widget(currentIndex));
    ui->changeimage->widget(currentIndex)->setGraphicsEffect(currentEffect);
    currentEffect->setOpacity(1.0);

    nextEffect = new QGraphicsOpacityEffect();
    nextEffect->setOpacity(0.0);

    // 设置 QPropertyAnimation 动画
    currentAnimation = new QPropertyAnimation(currentEffect, "opacity");
    nextAnimation = new QPropertyAnimation(nextEffect, "opacity");

    // 连接按钮信号到槽函数
    connect(ui->previousButton, &QPushButton::clicked, this, &first::showPreviousImage);
    connect(ui->nextButton, &QPushButton::clicked, this, &first::showNextImage);
}

void first::setHeadimage(QString imgpath)
{
    ui->labheadimage->setStyleSheet(imgpath);
}

void first::loadData()
{

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE phone = "+p);// 修改为你的表名和条件

    if (query.exec() && query.next())
    {
        ui->username->setText(query.value("username").toString());
        ui->phone->setText(query.value("phone").toString());
        ui->email->setText(query.value("email").toString());
        ui->car_plate->setText(query.value("car_plate").toString());
    } else {
        qDebug() << "Load Data Error: " << query.lastError().text();
    }
}
first::~first()
{
    delete ui;
}

void first::on_btnchange_clicked()
{
    cginfo=new changeinfo();
    this->hide();
    cginfo->show();
}


void first::on_tabWidget_currentChanged(int index)
{
    if (index == 2) {
        loadData();
    }
}

void first::showNextImage() {
    int nextIndex = (currentIndex + 1) % ui->changeimage->count();

    // 设置动画的开始和结束值
    currentAnimation->setDuration(1500);
    currentAnimation->setStartValue(1.0);
    currentAnimation->setEndValue(0.0);

    nextAnimation->setDuration(1500);
    nextAnimation->setStartValue(0.0);
    nextAnimation->setEndValue(1.0);

    // 应用透明度效果
    ui->changeimage->widget(nextIndex)->setGraphicsEffect(nextEffect);

    // 切换到下一个图像
    ui->changeimage->setCurrentIndex(nextIndex);

    // 启动动画
    currentAnimation->start();
    nextAnimation->start();

    currentIndex = nextIndex;
}

void first::showPreviousImage() {
    int nextIndex = (currentIndex - 1 + ui->changeimage->count()) % ui->changeimage->count();

    // 设置动画的开始和结束值
    currentAnimation->setDuration(1500);
    currentAnimation->setStartValue(1.0);
    currentAnimation->setEndValue(0.0);

    nextAnimation->setDuration(1500);
    nextAnimation->setStartValue(0.0);
    nextAnimation->setEndValue(1.0);

    // 应用透明度效果
    ui->changeimage->widget(nextIndex)->setGraphicsEffect(nextEffect);

    // 切换到上一个图像
    ui->changeimage->setCurrentIndex(nextIndex);

    // 启动动画
    currentAnimation->start();
    nextAnimation->start();

    currentIndex = nextIndex;
}

void first::animationFinished() {
    // 动画完成后，重置透明度效果
    currentEffect->setOpacity(1.0);
    nextEffect->setOpacity(0.0);
}


void first::on_btnwallet_clicked()
{
    walet *w=new walet();
    this->hide();
    w->show();
}


void first::on_btnbill_clicked()
{
    bill *b=new bill();
    b->show();
}

bool first::openDB()
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

bool first::openTable()
{
    tabModel = new QSqlTableModel(this,db);
    tabModel->setTable("parking_spots");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setSort(tabModel->fieldIndex("spot_id"),Qt::AscendingOrder);

    if(!(tabModel->select()))
    {QMessageBox::critical(this,"错误","打开数据表错误:\n"+tabModel->lastError().text());}
    qDebug()<<"aaaa";

    int rowCount = tabModel->rowCount();
    qDebug() << "Number of rows in the model:" << rowCount;
    QModelIndex index = tabModel->index(0, 2); // 获取第一行第一列的数据
    QVariant data = tabModel->data(index);
    qDebug() << "Data at index (0, 2):" << data.toString();


    tabModel->setHeaderData(tabModel->fieldIndex("spot_id"),Qt::Horizontal,"spot_id");
    tabModel->setHeaderData(tabModel->fieldIndex("spot_number"),Qt::Horizontal,"车位号");
    tabModel->setHeaderData(tabModel->fieldIndex("is_available"),Qt::Horizontal,"状态");
    ui->spottab->setModel(tabModel);

    ui->spottab->setColumnWidth(0, 100);  // 设置第一列的宽度为 100 像素
    ui->spottab->setColumnWidth(1, 200);
    ui->spottab->setColumnWidth(2, 100);

    ui->spottab->update();


    dataMapper=new QDataWidgetMapper(this);
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    dataMapper->addMapping(ui->spotnum,tabModel->fieldIndex("spot_id"));

    dataMapper->toFirst();

    selModel = new  QItemSelectionModel(tabModel,this);
    connect(selModel,&QItemSelectionModel::currentRowChanged,this,&first::do_currentRowChange);

    ui->spottab->setSelectionModel(selModel);

}

void first::do_currentRowChange(const QModelIndex &current,const QModelIndex &previous)

{
    dataMapper->setCurrentIndex(current.row());
    int curRecNo=current.row();
    QSqlRecord curRec=tabModel->record(curRecNo);

}

void first::on_bookbtn_clicked()
{
    int spotnum=ui->spotnum->value();
    if (!spotnum) {
        QMessageBox::warning(this, "错误", "请选择一个车位进行预约");
        return;
    }

    //QString spotId = currentItem->data(Qt::UserRole).toString();

    // 获取当前时间作为预约时间
    //QString reservationTime = QDateTime::currentDateTime().toString(Qt::ISODate);

    //QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    // 更新车位状态
    query.prepare("UPDATE parking_spots SET is_available = 0 WHERE spot_id = ?");
    query.addBindValue(spotnum);
    if (query.exec()) {
        QMessageBox::information(this, "提示", "预约成功");
        openTable();
        return;
    }
    else if (!query.exec()) {
        QMessageBox::critical(this, "数据库错误", query.lastError().text());
        return;
    }


}

