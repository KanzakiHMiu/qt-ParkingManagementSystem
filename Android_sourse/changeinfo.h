#ifndef CHANGEINFO_H
#define CHANGEINFO_H

#include <QWidget>
namespace Ui {
class changeinfo;
}

class changeinfo : public QWidget
{
    Q_OBJECT

public:
    explicit changeinfo(QWidget *parent = nullptr);
    void loadData();
    ~changeinfo();

private slots:
    void on_btnback_clicked();

    void on_btnsave_clicked();

private:
    Ui::changeinfo *ui;
};

#endif // CHANGEINFO_H
