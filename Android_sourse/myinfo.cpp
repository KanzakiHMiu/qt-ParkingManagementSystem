#include "myinfo.h"
#include "ui_myinfo.h"

myinfo::myinfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myinfo)
{
    ui->setupUi(this);
}

myinfo::~myinfo()
{
    delete ui;
}
