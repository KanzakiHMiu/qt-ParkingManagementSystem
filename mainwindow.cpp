#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_admin.h"
#include "sysabout.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化用户信息表格
    ui->userInfoTableWidget->setColumnCount(3);
    ui->userInfoTableWidget->setHorizontalHeaderLabels(QStringList() << "用户名" << "注册日期" << "车牌号");

    // 初始化数据库
    initializeDatabase();
    // 加载用户数据
    loadUserData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("parking_management_system");
    db.setUserName("root");
    db.setPassword("youmumoe.2");

    if (!db.open()) {
        QMessageBox::critical(this, "数据库连接失败", db.lastError().text());
        return;
    }
}

void MainWindow::loadUserData()
{
    QSqlQuery query("SELECT username, registration_date, car_plate FROM users");
    while (query.next()) {
        int row = ui->userInfoTableWidget->rowCount();
        ui->userInfoTableWidget->insertRow(row);
        ui->userInfoTableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->userInfoTableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->userInfoTableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
    }
}

bool MainWindow::validateUserData(const QString &username, const QString &carPlate)
{
    if (username.isEmpty() || username.length() > 50) {
        QMessageBox::warning(this, "输入错误", "用户名不能为空且长度不能超过50个字符！");
        return false;
    }

    if (carPlate.isEmpty() || carPlate.length() > 20) {
        QMessageBox::warning(this, "输入错误", "车牌号不能为空且长度不能超过20个字符！");
        return false;
    }

    return true;
}

// 添加用户槽函数
void MainWindow::on_addUserButton_clicked()
{
    QString userName = QInputDialog::getText(this, "添加用户", "用户名：");
    QString carPlate = QInputDialog::getText(this, "添加用户", "车牌号：");

    if (validateUserData(userName, carPlate)) {
        QString registrationDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");

        QSqlQuery query;
        query.prepare("INSERT INTO users (username, registration_date, car_plate) VALUES (:username, :registration_date, :car_plate)");
        query.bindValue(":username", userName);
        query.bindValue(":registration_date", registrationDate);
        query.bindValue(":car_plate", carPlate);

        if (!query.exec()) {
            QMessageBox::critical(this, "添加用户失败", query.lastError().text());
            return;
        }

        int row = ui->userInfoTableWidget->rowCount();
        ui->userInfoTableWidget->insertRow(row);
        ui->userInfoTableWidget->setItem(row, 0, new QTableWidgetItem(userName));
        ui->userInfoTableWidget->setItem(row, 1, new QTableWidgetItem(registrationDate));
        ui->userInfoTableWidget->setItem(row, 2, new QTableWidgetItem(carPlate));
        QMessageBox::information(this, "添加用户", "用户添加成功！");
    } else {
        QMessageBox::warning(this, "添加用户", "所有字段都是必填的！");
    }
}

// 删除用户槽函数
void MainWindow::on_deleteUserButton_clicked()
{
    int currentRow = ui->userInfoTableWidget->currentRow();
    if (currentRow >= 0) {
        QString userName = ui->userInfoTableWidget->item(currentRow, 0)->text();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "您确定要删除用户 " + userName + " 吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QSqlQuery query;
            query.prepare("DELETE FROM users WHERE username = :username");
            query.bindValue(":username", userName);

            if (!query.exec()) {
                QMessageBox::critical(this, "删除用户失败", query.lastError().text());
                return;
            }

            ui->userInfoTableWidget->removeRow(currentRow);
            QMessageBox::information(this, "删除用户", "用户删除成功！");
        }
    } else {
        QMessageBox::warning(this, "删除用户", "请选择要删除的用户！");
    }
}

// 修改用户信息槽函数
void MainWindow::on_modifyUserButton_clicked()
{
    int currentRow = ui->userInfoTableWidget->currentRow();
    if (currentRow >= 0) {
        QString oldUserName = ui->userInfoTableWidget->item(currentRow, 0)->text();

        QString newUserName = QInputDialog::getText(this, "修改用户信息", "用户名：", QLineEdit::Normal, oldUserName);
        QString newCarPlate = QInputDialog::getText(this, "修改用户信息", "车牌号：", QLineEdit::Normal, ui->userInfoTableWidget->item(currentRow, 2)->text());

        if (validateUserData(newUserName, newCarPlate)) {
            QSqlQuery query;
            query.prepare("UPDATE users SET username = :newUsername, car_plate = :newCarPlate WHERE username = :oldUsername");
            query.bindValue(":newUsername", newUserName);
            query.bindValue(":newCarPlate", newCarPlate);
            query.bindValue(":oldUsername", oldUserName);

            if (!query.exec()) {
                QMessageBox::critical(this, "修改用户信息失败", query.lastError().text());
                return;
            }

            ui->userInfoTableWidget->setItem(currentRow, 0, new QTableWidgetItem(newUserName));
            ui->userInfoTableWidget->setItem(currentRow, 2, new QTableWidgetItem(newCarPlate));
            QMessageBox::information(this, "修改用户信息", "用户信息修改成功！");
        }
    } else {
        QMessageBox::warning(this, "修改用户信息", "请选择要修改的用户！");
    }
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
