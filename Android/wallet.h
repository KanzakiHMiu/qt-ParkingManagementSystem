#ifndef WALLET_H
#define WALLET_H

#include <QWidget>
#include "netmanager.h"

namespace Ui {
class wallet;
}

class wallet : public QWidget
{
    Q_OBJECT

public:
    explicit wallet(QWidget *parent = nullptr);
    ~wallet();
    void loadWalletData();

private slots:
    void on_paybtn_clicked();

    void on_backbtn_clicked();

    void onNetworkError(const QString&);
    void onLoadWalletReply(QNetworkReply*);

private:
    Ui::wallet *ui;
    netManager* NetManager;
};

#endif // WALLET_H
