#include "addavatardialog.h"
#include "ui_addavatardialog.h"

AddAvatarDialog::AddAvatarDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddAvatarDialog)
{
    ui->setupUi(this);
}

AddAvatarDialog::~AddAvatarDialog()
{
    delete ui;
}

void AddAvatarDialog::getAvatarData(const QByteArray& avatarData)
{
    if (!avatarData.isEmpty()) {
        QPixmap pic;
        pic.loadFromData(avatarData);
        ui->avatarLabel->setPixmap(pic.scaled(ui->avatarLabel->size()));
    }
}

void AddAvatarDialog::on_buttonBox_accepted()
{

}


void AddAvatarDialog::on_buttonBox_rejected()
{
    this->close();
}
