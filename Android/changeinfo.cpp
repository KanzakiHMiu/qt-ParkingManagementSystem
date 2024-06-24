#include <changeinfo.h>
#include "ui_changeinfo.h"
#include "widget.h"
#include "firstpage.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QDebug>
#include <QFileDialog>
extern QString p;

changeinfo::changeinfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::changeinfo)
    , NetManager(new netManager(this))
{
    ui->setupUi(this);

    connect(NetManager, &netManager::loadUserDataReply,
            this, &changeinfo::onLoadUserDataReply);
    connect(NetManager, &netManager::updateUserInfoReply,
            this, &changeinfo::onUpdateUserInfoReply);
    connect(NetManager, &netManager::networkError,
            this, &changeinfo::onNetworkError);
}

changeinfo::~changeinfo()
{
    delete ui;
}

void changeinfo::on_btnback_clicked()
{
    firstpage *f=new firstpage();
    this->close();
    f->show();
}

void changeinfo::onNetworkError(const QString &errorString)
{
    qDebug() << "Error:" << errorString;
    QMessageBox::warning(this, "网络错误", "无法连接到服务器，请稍后重试！");
}

void changeinfo::loadUserData()
{
    QUrl url("http://*:8689/user/info");

    QUrlQuery query;
    query.addQueryItem("phone", p);
    url.setQuery(query);

    NetManager->getRequest(url);
}

void changeinfo::onLoadUserDataReply(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "success") {
        QJsonObject data = jsonObject["data"].toObject();

        ui->linename->setText(data["username"].toString());
        ui->linephone->setText(data["phone"].toString());
        ui->lineemail->setText(data["email"].toString());
        ui->linecar->setText(data["car_plate"].toString());
        if (!data["avatar"].toString().isEmpty()) {
            QByteArray avatarData = QByteArray::fromBase64(data["avatar"].toString().toUtf8());
            QPixmap pic;
            pic.loadFromData(avatarData);
            ui->labelimage->setPixmap(pic.scaledToWidth(ui->labelimage->width()));
        }
    } else {
        QMessageBox::warning(this, "加载失败", jsonObject["message"].toString());
    }
}

void changeinfo::on_btnsave_clicked()
{
    QUrl url("http://*:8689/user/update");

    QJsonObject json;
    json["phone"] = ui->linephone->text();
    json["username"] = ui->linename->text();
    json["email"] = ui->lineemail->text();
    json["car_plate"] = ui->linecar->text();
    if (avatarData.isEmpty()) {
        json["avatar"] = "";
    }
    json["avatar"] = QString::fromUtf8(avatarData.toBase64());

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    NetManager->putRequest(url, data);
}

void changeinfo::onUpdateUserInfoReply(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    QString status = jsonObject["status"].toString();

    if (status == "Update successful") {
        QMessageBox::information(this, "提示", "用户信息更新成功");
    } else {
        QMessageBox::warning(this, "更新失败", jsonObject["message"].toString());
    }
}

void changeinfo::on_image_clicked()
{
    QString aFile = QFileDialog::getOpenFileName(this, "选择图片文件", "", "照片(*.jpg)");
    if (aFile.isEmpty()) {
        return;
    }

    QFile* file = new QFile(aFile);
    file->open(QIODevice::ReadOnly);
    avatarData = file->readAll();
    file->close();
    delete file;

    QPixmap pic;
    pic.load(aFile);
    ui->labelimage->setPixmap(pic.scaledToWidth(ui->labelimage->width()));
}

