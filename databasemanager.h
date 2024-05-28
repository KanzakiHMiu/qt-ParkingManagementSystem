#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql>
#include <QWidget>

class DatabaseManager : public QWidget
{
public:
    explicit DatabaseManager(QWidget *parent = nullptr);
    ~DatabaseManager();

    bool initializeDatabase();
    QSqlQuery loadUserData();

    bool addUser(const QString&, const QString&, const QString&);
    bool deleteUser(const QString&);
    bool modifyUser(const QString&, const QString&, const QString&);
    bool validateUserData(const QString&, const QString&);
    bool loginAdmin(const QString&, const QString&);

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
