#ifndef CHANGEINFO_H
#define CHANGEINFO_H

#include <QWidget>
#include "netmanager.h"

namespace Ui {
class changeinfo;
}

class changeinfo : public QWidget
{
    Q_OBJECT

public:
    explicit changeinfo(QWidget *parent = nullptr);
    ~changeinfo();
    void loadUserData();

private slots:
    void on_btnback_clicked();

    void on_btnsave_clicked();

    void onNetworkError(const QString&);
    void onLoadUserDataReply(QNetworkReply*);
    void onUpdateUserInfoReply(QNetworkReply*);

    void on_image_clicked();

private:
    Ui::changeinfo *ui;
    netManager* NetManager;
    QByteArray avatarData;
};

#endif // CHANGEINFO_H
