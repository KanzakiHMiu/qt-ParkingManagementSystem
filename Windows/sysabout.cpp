#include "sysabout.h"
#include "ui_sysabout.h"

sysAbout::sysAbout(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sysAbout)
{
    ui->setupUi(this);
}

sysAbout::~sysAbout()
{
    delete ui;
}
