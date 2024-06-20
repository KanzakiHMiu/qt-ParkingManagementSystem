#ifndef WALET_H
#define WALET_H

#include <QWidget>

namespace Ui {
class walet;
}

class walet : public QWidget
{
    Q_OBJECT

public:
    explicit walet(QWidget *parent = nullptr);
    void loadData();
    ~walet();

private slots:


    void on_paybtn_clicked();

    void on_backbtn_clicked();



private:
    Ui::walet *ui;

};

#endif // WALET_H
