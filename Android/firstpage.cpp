#include "firstpage.h"
#include "ui_firstpage.h"
#include "wallet.h"
#include "bill.h"
#include "widget.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QDebug>
#include <QDateTime>
extern QString p;

firstpage::firstpage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::firstpage)
    , NetManager(new netManager(this))
    , currentIndex(0)
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    timer->start(4000);

    initRoundImages();
    loadSpotsData();

    connect(timer, &QTimer::timeout,
            this, &firstpage::showNextImage);
    connect(NetManager, &netManager::loadUserDataReply,
            this, &firstpage::onLoadUserDataReply);
    connect(NetManager, &netManager::loadSpotsDataReply,
            this, &firstpage::onLoadSpotsDataReply);
    connect(NetManager, &netManager::bookSpotReply,
            this, &firstpage::onBookSpotReply);
    connect(NetManager, &netManager::networkError,
            this, &firstpage::onNetworkError);
}

firstpage::~firstpage()
{
    delete ui;
}

void firstpage::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    loadUserData();
}

void firstpage::on_btnchange_clicked()
{
    cginfo=new changeinfo();
    this->hide();
    cginfo->loadUserData();
    cginfo->show();
}

void firstpage::on_btnwallet_clicked()
{
    wallet *w=new wallet();
    this->hide();
    w->loadWalletData();
    w->show();
}

void firstpage::on_btnbill_clicked()
{
    bill *b=new bill();
    this->hide();
    b->show();
}

void firstpage::on_pushButton_clicked()
{
    Widget* wid = new Widget();
    this->close();
    wid->show();
}

void firstpage::showNextImage() {
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

void firstpage::showPreviousImage() {
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

void firstpage::animationFinished() {
    // 动画完成后，重置透明度效果
    currentEffect->setOpacity(1.0);
    nextEffect->setOpacity(0.0);
}

void firstpage::initRoundImages() {
    // 创建透明度效果
    currentEffect = new QGraphicsOpacityEffect(ui->changeimage->widget(currentIndex));
    ui->changeimage->widget(currentIndex)->setGraphicsEffect(currentEffect);
    currentEffect->setOpacity(1.0);

    nextEffect = new QGraphicsOpacityEffect();
    nextEffect->setOpacity(0.0);

    // 设置 QPropertyAnimation 动画
    currentAnimation = new QPropertyAnimation(currentEffect, "opacity");
    nextAnimation = new QPropertyAnimation(nextEffect, "opacity");

    connect(ui->previousButton, &QPushButton::clicked, this, &firstpage::showPreviousImage);
    connect(ui->nextButton, &QPushButton::clicked, this, &firstpage::showNextImage);
}

void firstpage::onNetworkError(const QString &errorString)
{
    qDebug() << "Error:" << errorString;
    QMessageBox::warning(this, "网络错误", "无法连接到服务器，请稍后重试！");
}

void firstpage::loadUserData()
{
    QUrl url("http://*:8689/user/info");

    QUrlQuery query;
    query.addQueryItem("phone", p);
    url.setQuery(query);

    NetManager->getRequest(url);
}

void firstpage::onLoadUserDataReply(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "success") {
        QJsonObject data = jsonObject["data"].toObject();

        ui->username->setText(data["username"].toString());
        ui->phone->setText(data["phone"].toString());
        ui->email->setText(data["email"].toString());
        ui->car_plate->setText(data["car_plate"].toString());
        if (!data["avatar"].toString().isEmpty()) {
            QByteArray avatarData = QByteArray::fromBase64(data["avatar"].toString().toUtf8());
            QPixmap pic;
            pic.loadFromData(avatarData);
            ui->labheadimage->setPixmap(pic.scaledToWidth(ui->labheadimage->width()));
        }
    } else {
        QMessageBox::warning(this, "加载失败", jsonObject["message"].toString());
    }
}

void firstpage::loadSpotsData()
{
    QUrl url("http://*:8689/parking/spots");

    NetManager->getRequest(url);
}

void firstpage::onLoadSpotsDataReply(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "success") {
        QJsonArray dataArray = jsonObject["data"].toArray();

        tabModel = new QStandardItemModel(dataArray.size(), 3, this);
        tabModel->setHeaderData(0, Qt::Horizontal, "spot_id");
        tabModel->setHeaderData(1, Qt::Horizontal, "车位号");
        tabModel->setHeaderData(2, Qt::Horizontal, "状态");

        for (int i = 0; i < dataArray.size(); ++i) {
            QJsonObject item = dataArray[i].toObject();
            tabModel->setItem(i, 0, new QStandardItem(QString::number(item["spot_id"].toInt())));
            tabModel->setItem(i, 1, new QStandardItem(item["spot_number"].toString()));
            tabModel->setItem(i, 2, new QStandardItem(QString::number(item["is_available"].toBool())));
        }

        ui->spottab->setModel(tabModel);
        ui->spottab->setColumnHidden(0, 1);
        ui->spottab->setColumnWidth(1, 200);
        ui->spottab->setColumnWidth(2, 100);
        ui->spottab->update();
    } else {
        QMessageBox::warning(this, "加载失败", jsonObject["message"].toString());
    }
}

void firstpage::on_bookbtn_clicked()
{
    int spotnum = ui->spotnum->value();
    if (!spotnum) {
        QMessageBox::warning(this, "错误", "请选择一个车位进行预约");
        return;
    }

    QUrl url("http://*:8689/user/bookspot");
    QJsonObject json;
    json["spot_number"] = spotnum;
    json["phone"] = p;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    NetManager->putRequest(url, data);
}

void firstpage::onBookSpotReply(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "Booking successful") {
        QMessageBox::information(this, "提示", "预约成功");
        loadSpotsData();
    } else if ((status == "User already booked a spot")){
        QMessageBox::warning(this, "预约失败", "用户已经预定了一个车位");
    } else if ((status == "Spot not found")){
        QMessageBox::warning(this, "预约失败", "未找到该车位");
    } else if ((status == "Spot is already booked")){
        QMessageBox::warning(this, "预约失败", "该车位已被预定");
    } else {
        QMessageBox::warning(this, "加载失败", jsonObject["message"].toString());
    }
}
