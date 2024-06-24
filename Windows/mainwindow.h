#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTimer>
#include "netmanager.h"

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

    void onLoadUserDataReply(QNetworkReply*);

    void onAvatarButtonClicked(const QString&);

    void updateProgressBar();

private:
    Ui::MainWindow *ui;
    netManager* NetManager;

    QTimer *timer;
    int progressValue;
    QStandardItemModel* userTabModel;

    void loadUserData();
};
#endif // MAINWINDOW_H
