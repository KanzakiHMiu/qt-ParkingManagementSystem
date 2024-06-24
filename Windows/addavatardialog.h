#ifndef ADDAVATARDIALOG_H
#define ADDAVATARDIALOG_H

#include <QDialog>

namespace Ui {
class AddAvatarDialog;
}

class AddAvatarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAvatarDialog(QWidget *parent = nullptr);
    ~AddAvatarDialog();

    void getAvatarData(const QByteArray&);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddAvatarDialog *ui;
};

#endif // ADDAVATARDIALOG_H
