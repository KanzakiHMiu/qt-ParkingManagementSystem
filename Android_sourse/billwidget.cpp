#include "billwidget.h"
#include "ui_billwidget.h"

billwidget::billwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::billwidget)
{
    ui->setupUi(this);
}

billwidget::~billwidget()
{
    delete ui;
}
