#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sysabout.h"
#include "login_admin.h"
#include "AddAvatarDialog.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , NetManager(new netManager(this))
    , timer(new QTimer(this))
    , progressValue(0)
{
    ui->setupUi(this);

    loadUserData();

    connect(timer, &QTimer::timeout, this, &MainWindow::updateProgressBar);
    timer->start(40);

    connect(NetManager, &netManager::loadUserDataReply,
            this, &MainWindow::onLoadUserDataReply);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateProgressBar() {
    if (progressValue != 90) {
        progressValue += 1;
        ui->loadingUserProgressBar->setValue(progressValue);
    } else {
        timer->stop();
    }
}

QString handleLoadUserDataResponseStatus(const QByteArray& response){
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    return jsonObject["status"].toString();
}

QJsonArray handleLoadUserDataResponseData(const QByteArray& response){
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();
    return jsonObject["data"].toArray();
}

void MainWindow::loadUserData()
{
    QUrl url("http://*:8689/admin/loadusers");
    NetManager->getRequest(url);
}

void MainWindow::onLoadUserDataReply(QNetworkReply* reply)
{
    QByteArray response = reply->readAll();
    if (handleLoadUserDataResponseStatus(response) == "Internal Server Error") {
        QMessageBox::warning(this, "登陆失败", "服务端错误，请联系服务器维护人员！");
    }else if (handleLoadUserDataResponseStatus(response) == "success") {
        QJsonArray dataArray = handleLoadUserDataResponseData(response);

        userTabModel = new QStandardItemModel(dataArray.size(), 7, this);
        userTabModel->setHeaderData(0, Qt::Horizontal, "username");
        userTabModel->setHeaderData(1, Qt::Horizontal, "phone");
        userTabModel->setHeaderData(2, Qt::Horizontal, "car_plate");
        userTabModel->setHeaderData(3, Qt::Horizontal, "password");
        userTabModel->setHeaderData(4, Qt::Horizontal, "email");
        userTabModel->setHeaderData(5, Qt::Horizontal, "registration_date");
        userTabModel->setHeaderData(6, Qt::Horizontal, "avatar");
        ui->userInfoTableWidget->setModel(userTabModel);

        for (int i = 0; i < dataArray.size(); ++i) {
            QJsonObject item = dataArray[i].toObject();
            userTabModel->setItem(i, 0, new QStandardItem(item["username"].toString()));
            userTabModel->setItem(i, 1, new QStandardItem(item["phone"].toString()));
            userTabModel->setItem(i, 2, new QStandardItem(item["car_plate"].toString()));
            userTabModel->setItem(i, 3, new QStandardItem(item["password"].toString()));
            userTabModel->setItem(i, 4, new QStandardItem(item["email"].toString()));
            userTabModel->setItem(i, 5, new QStandardItem(item["registration_date"].toString()));

            QPushButton *avatarButton = new QPushButton;
            if (item["avatar"].toString().isEmpty()) {
                avatarButton->setText("添加头像");
            } else {
                avatarButton->setText("查看头像");
            }
            QModelIndex index = userTabModel->index(i, 6);
            ui->userInfoTableWidget->setIndexWidget(index, avatarButton);

            connect(avatarButton, &QPushButton::clicked,
                    this, [=](){
                onAvatarButtonClicked(item["avatar"].toString());
            });
            int progress = 95;
            ui->loadingUserProgressBar->setValue(progress);
        }

        ui->userInfoTableWidget->setColumnWidth(3, 550);
        ui->userInfoTableWidget->setColumnWidth(4, 150);
        ui->userInfoTableWidget->setColumnWidth(5, 150);
        ui->userInfoTableWidget->update();

        ui->loadingUserProgressBar->hide();
    }
}

void MainWindow::onAvatarButtonClicked(const QString &avatarBase64)
{
    AddAvatarDialog* addAvtDlog = new AddAvatarDialog(this);
    if (!avatarBase64.isEmpty()) {
        QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toUtf8());
        addAvtDlog->setWindowTitle("查看头像");
        addAvtDlog->getAvatarData(avatarData);
    } else {
        addAvtDlog->setWindowTitle("添加头像");
    }

    addAvtDlog->exec();
}

void MainWindow::on_actionLogout_triggered()
{
    login_admin* l = new login_admin;
    l->show();
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    sysAbout* a = new sysAbout;
    a->show();
}
