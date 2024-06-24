#include "databasemanager.h"
#include <QMessageBox>

DatabaseManager::DatabaseManager(QWidget *parent)
    : QWidget(parent)
{
    initializeDatabase();
}

DatabaseManager::~DatabaseManager()
{
    db.close();
}

bool DatabaseManager::initializeDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("parking_management_system");
    db.setUserName("root");
    db.setPassword("youmumoe.2");

    if (!db.open()) {
        QMessageBox::critical(this, "数据库连接失败", db.lastError().text());
        return false;
    }
    return true;
}

QSqlQuery DatabaseManager::loadUserData() {
    QSqlQuery query("SELECT username, registration_date, car_plate FROM users");
    return query;
}

bool DatabaseManager::addUser(const QString &username, const QString &registrationDate, const QString &carPlate) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, registration_date, car_plate) VALUES (:username, :registration_date, :car_plate)");
    query.bindValue(":username", username);
    query.bindValue(":registration_date", registrationDate);
    query.bindValue(":car_plate", carPlate);

    return query.exec();
}

bool DatabaseManager::deleteUser(const QString &username) {
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE username = :username");
    query.bindValue(":username", username);

    return query.exec();
}

bool DatabaseManager::modifyUser(const QString &oldUsername, const QString &newUsername, const QString &newCarPlate) {
    QSqlQuery query;
    query.prepare("UPDATE users SET username = :newUsername, car_plate = :newCarPlate WHERE username = :oldUsername");
    query.bindValue(":newUsername", newUsername);
    query.bindValue(":newCarPlate", newCarPlate);
    query.bindValue(":oldUsername", oldUsername);

    return query.exec();
}

bool DatabaseManager::validateUserData(const QString &username, const QString &carPlate) {
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

bool DatabaseManager::loginAdmin(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM admin WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::warning(this, "登录失败", "登录失败，请重试！");
        return false;
    } else {
        return query.next();
    }
}
