#ifndef PAY_H
#define PAY_H

#include <QWidget>
#include <netmanager.h>

namespace Ui {
class pay;
}

class pay : public QWidget
{
    Q_OBJECT

public:
    explicit pay(QWidget *parent = nullptr);
    ~pay();

private slots:
    void on_backbtn_clicked();

    void on_paybtn_clicked();

    void onNetworkError(const QString&);
    void onRechargeReply(QNetworkReply*);

private:
    Ui::pay *ui;
    netManager* NetManager;
};

#endif // PAY_H
