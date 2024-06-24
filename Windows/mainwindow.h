#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"

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

private slots:
    void on_actionLogout_triggered();

    void on_actionAbout_triggered();

    // 管理用户信息
    void on_addUserButton_clicked();
    void on_deleteUserButton_clicked();
    void on_modifyUserButton_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseManager dbManager;
    void loadUserData();
};
#endif // MAINWINDOW_H
