#include "changeinfo.h"
#include "ui_changeinfo.h"

changeinfo::changeinfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::changeinfo)
{
    ui->setupUi(this);
}

changeinfo::~changeinfo()
{
    delete ui;
}
