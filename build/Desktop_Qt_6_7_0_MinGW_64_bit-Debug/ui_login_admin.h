/********************************************************************************
** Form generated from reading UI file 'login_admin.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_ADMIN_H
#define UI_LOGIN_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login_admin
{
public:
    QPushButton *pushButton_login;
    QPushButton *pushButton_resetPasword;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_account;
    QLabel *label_password;
    QLabel *label_account;
    QLineEdit *lineEdit_password;

    void setupUi(QWidget *login_admin)
    {
        if (login_admin->objectName().isEmpty())
            login_admin->setObjectName("login_admin");
        login_admin->resize(600, 300);
        pushButton_login = new QPushButton(login_admin);
        pushButton_login->setObjectName("pushButton_login");
        pushButton_login->setGeometry(QRect(230, 230, 151, 31));
        pushButton_resetPasword = new QPushButton(login_admin);
        pushButton_resetPasword->setObjectName("pushButton_resetPasword");
        pushButton_resetPasword->setGeometry(QRect(480, 161, 71, 20));
        layoutWidget = new QWidget(login_admin);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(110, 80, 361, 131));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_account = new QLineEdit(layoutWidget);
        lineEdit_account->setObjectName("lineEdit_account");

        gridLayout->addWidget(lineEdit_account, 0, 1, 1, 1);

        label_password = new QLabel(layoutWidget);
        label_password->setObjectName("label_password");
        QFont font;
        font.setPointSize(14);
        label_password->setFont(font);

        gridLayout->addWidget(label_password, 1, 0, 1, 1);

        label_account = new QLabel(layoutWidget);
        label_account->setObjectName("label_account");
        label_account->setFont(font);

        gridLayout->addWidget(label_account, 0, 0, 1, 1);

        lineEdit_password = new QLineEdit(layoutWidget);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_password, 1, 1, 1, 1);


        retranslateUi(login_admin);

        QMetaObject::connectSlotsByName(login_admin);
    } // setupUi

    void retranslateUi(QWidget *login_admin)
    {
        login_admin->setWindowTitle(QCoreApplication::translate("login_admin", "Login", nullptr));
        pushButton_login->setText(QCoreApplication::translate("login_admin", "\347\231\273\345\275\225", nullptr));
        pushButton_resetPasword->setText(QCoreApplication::translate("login_admin", "\345\277\230\350\256\260\345\257\206\347\240\201\357\274\237", nullptr));
        label_password->setText(QCoreApplication::translate("login_admin", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_account->setText(QCoreApplication::translate("login_admin", "\350\264\246\345\217\267\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login_admin: public Ui_login_admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_ADMIN_H
