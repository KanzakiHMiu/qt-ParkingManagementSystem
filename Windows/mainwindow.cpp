#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sysabout.h"
#include "login_admin.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbManager()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadUserData()
{

}

void MainWindow::on_addUserButton_clicked()
{
    QString phone = QInputDialog::getText(this, "添加用户", "手机号：");
    QString carPlate = QInputDialog::getText(this, "添加用户", "车牌号：");
    QString password = "123";

    if (dbManager.validateUserData(phone, carPlate)) {
        QString registrationDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");

        if (!dbManager.addUser(phone, registrationDate, carPlate)) {
            QMessageBox::critical(this, "添加用户失败", "添加用户失败");
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

void MainWindow::on_deleteUserButton_clicked()
{
    int currentRow = ui->userInfoTableWidget->currentRow();
    if (currentRow >= 0) {
        QString userName = ui->userInfoTableWidget->item(currentRow, 0)->text();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "您确定要删除用户 " + userName + " 吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (!dbManager.deleteUser(userName)) {
                QMessageBox::critical(this, "删除用户失败", "删除用户失败");
                return;
            }

            ui->userInfoTableWidget->removeRow(currentRow);
            QMessageBox::information(this, "删除用户", "用户删除成功！");
        }
    } else {
        QMessageBox::warning(this, "删除用户", "请选择要删除的用户！");
    }
}

void MainWindow::on_modifyUserButton_clicked()
{
    int currentRow = ui->userInfoTableWidget->currentRow();
    if (currentRow >= 0) {
        QString oldUserName = ui->userInfoTableWidget->item(currentRow, 0)->text();

        QString newUserName = QInputDialog::getText(this, "修改用户信息", "用户名：", QLineEdit::Normal, oldUserName);
        QString newCarPlate = QInputDialog::getText(this, "修改用户信息", "车牌号：", QLineEdit::Normal, ui->userInfoTableWidget->item(currentRow, 2)->text());

        if (dbManager.validateUserData(newUserName, newCarPlate)) {
            if (!dbManager.modifyUser(oldUserName, newUserName, newCarPlate)) {
                QMessageBox::critical(this, "修改用户信息失败", "修改用户信息失败");
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
