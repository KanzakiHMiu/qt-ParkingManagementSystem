/********************************************************************************
** Form generated from reading UI file 'sysabout.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSABOUT_H
#define UI_SYSABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sysAbout
{
public:
    QTextEdit *textEdit;

    void setupUi(QWidget *sysAbout)
    {
        if (sysAbout->objectName().isEmpty())
            sysAbout->setObjectName("sysAbout");
        sysAbout->resize(400, 300);
        textEdit = new QTextEdit(sysAbout);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 0, 401, 291));
        textEdit->setReadOnly(true);

        retranslateUi(sysAbout);

        QMetaObject::connectSlotsByName(sysAbout);
    } // setupUi

    void retranslateUi(QWidget *sysAbout)
    {
        sysAbout->setWindowTitle(QCoreApplication::translate("sysAbout", "Form", nullptr));
        textEdit->setHtml(QCoreApplication::translate("sysAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\207\252\345\212\250\345\214\226\345\201\234\350\275\246\345\234\272\347\256\241\347\220\206\347\263\273\347\273\237\342\200\224\342\200\224\347\256\241\347\220\206\345\221\230\357\274\210\347\224\265\350\204\221\357\274\211\347\253\257</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">qt-ParkingManagementSyst"
                        "em-AdminClient</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\234\254\347\256\241\347\220\206\345\221\230\347\253\257\347\263\273\347\273\237\346\227\250\345\234\250\346\217\220\344\276\233\344\270\200\344\270\252\351\253\230\346\225\210\343\200\201\344\276\277\346\215\267\347\232\204\350\247\243\345\206\263\346\226\271\346\241\210\346\235\245\347\256\241\347\220\206\345\201\234\350\275\246\345\234\272\347\232\204\346\227\245\345\270\270\350\277\220\350\220\245\345\222\214\347\224\250\346\210\267\344\275\223\351\252\214\343\200\202\350\257\245\347\263\273\347\273\237\346\266\265\347\233\226\344\272\206\347\224\250\346\210\267\347\256\241\347\220\206\343\200\201\350\275\246\344\275\215\347\256\241\347\220\206\345\222\214\345\216\206\345\217\262\346\225\260\346\215\256"
                        "\345\210\206\346\236\220\347\255\211\345\244\232\346\226\271\351\235\242\347\232\204\345\212\237\350\203\275\343\200\202\347\263\273\347\273\237\351\207\207\347\224\250C++\350\257\255\350\250\200\350\277\233\350\241\214\345\274\200\345\217\221\357\274\214\347\273\223\345\220\210Qt\346\241\206\346\236\266\350\277\233\350\241\214GUI\345\274\200\345\217\221\357\274\214\345\271\266\344\275\277\347\224\250MySql\346\225\260\346\215\256\345\272\223\350\277\233\350\241\214\346\225\260\346\215\256\345\255\230\345\202\250\345\222\214\347\256\241\347\220\206\343\200\202</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Copyright 2024, \350\264\272\345\234\243, \351\231\210\345\205\264\346\255\246, \345\210\230\345\256\207\346\235\255</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0p"
                        "x; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">(C++3\347\217\255\347\254\25412\347\273\204)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">GPL-3.0 licence</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\234\254\347\250\213\345\272\217\346\230\257\350\207\252\347\224\261\350\275\257\344\273\266\357\274\232\344\275\240\345\217\257\344\273\245\345\206\215\345\210\206\345\217\221\344\271\213\345\222\214/\346\210\226\344\276\235\347\205\247\347\224\261\350\207\252\347\224\261\350\275\257\344\273\266\345\237\272\351\207\221\344\274\232\345\217\221\345\270\203\347\232\204 GNU \351\200\232\347\224\250\345\205\254\345\205\261\350\256\270\345\217\257\350\257\201\344\277\256\346\224\271\344\271\213\357\274\214\346\227\240\350\256\272\346\230\257\347\211\210\346\234\254 3 \350\256\270\345\217\257\350\257\201\357\274\214\350\277"
                        "\230\346\230\257\357\274\210\346\214\211\344\275\240\347\232\204\345\206\263\345\256\232\357\274\211\344\273\273\344\275\225\344\273\245\345\220\216\347\211\210\351\203\275\345\217\257\344\273\245\343\200\202</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sysAbout: public Ui_sysAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSABOUT_H
