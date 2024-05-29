#include "first.h"
#include "ui_first.h"

first::first(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::first)
{
    ui->setupUi(this);
}

void first::setHeadimage(QString imgpath)
{
    ui->labheadimage->setStyleSheet(imgpath);
}
first::~first()
{
    delete ui;
}

void first::on_btnchange_clicked()
{

}

