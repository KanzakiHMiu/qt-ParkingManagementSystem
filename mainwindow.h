#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool validateUserData(const QString&, const QString&);

private slots:
    void on_actionLogout_triggered();

    void on_actionAbout_triggered();

    // 管理用户信息
    void on_addUserButton_clicked();
    void on_deleteUserButton_clicked();
    void on_modifyUserButton_clicked();

private:
    Ui::MainWindow *ui;

    // 数据库
    QSqlDatabase db;
    void initializeDatabase();
    void loadUserData();
};
#endif // MAINWINDOW_H
