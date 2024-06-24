#ifndef BILL_H
#define BILL_H
#include "netmanager.h"
#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class bill;
}

class bill : public QWidget
{
    Q_OBJECT

public:
    explicit bill(QWidget *parent = nullptr);
    ~bill();
    void loadBillingHistory();

private slots:
    void on_btnback_clicked();

    void onNetworkError(const QString&);
    void onLoadBillingHistoryReply(QNetworkReply*);
private:
    Ui::bill *ui;
    netManager* NetManager;
    QStandardItemModel *tabModel;
};

#endif // BILL_H
