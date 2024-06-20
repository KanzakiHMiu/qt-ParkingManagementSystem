#ifndef BILL_H
#define BILL_H
#include<QSqlTableModel>
#include<QDataWidgetMapper>
#include <QWidget>

namespace Ui {
class bill;
}

class bill : public QWidget
{
    Q_OBJECT

public:
    explicit bill(QWidget *parent = nullptr);
    bool openTable();
    bool openDB();
    ~bill();

private slots:
    void on_btnback_clicked();

private:
    Ui::bill *ui;
    QSqlTableModel *tabModel;
    QDataWidgetMapper *dataMapper;
    QSqlDatabase db;
};

#endif // BILL_H
