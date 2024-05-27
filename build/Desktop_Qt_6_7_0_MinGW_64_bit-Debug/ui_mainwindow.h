/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLogout;
    QAction *actionAbout;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *UserInformation_tab;
    QTableWidget *userInfoTableWidget;
    QPushButton *addUserButton;
    QPushButton *deleteUserButton;
    QPushButton *modifyUserButton;
    QWidget *ParkingPosition_tab;
    QTableWidget *transactionTableWidget;
    QPushButton *modifyParkingPositionButton;
    QPushButton *deleteParkingPositionButton;
    QPushButton *addParkingPositionButton;
    QWidget *ParkingTransaction_tab;
    QTableWidget *transactionTableWidget_2;
    QPushButton *searchTransactionButton;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QLabel *label;
    QWidget *Monitor_tab;
    QLabel *cameraFeedLabel;
    QComboBox *cameraComboBox;
    QPushButton *switchCameraButton;
    QWidget *Announcement_tab;
    QTextEdit *announcementTextEdit;
    QPushButton *publishAnnouncementButton;
    QLabel *label_2;
    QWidget *MaintainSystem_tab;
    QLabel *systemStatusLabel;
    QPushButton *backupDatabaseButton;
    QPushButton *restoreDatabaseButton;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        actionLogout = new QAction(MainWindow);
        actionLogout->setObjectName("actionLogout");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1281, 701));
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        UserInformation_tab = new QWidget();
        UserInformation_tab->setObjectName("UserInformation_tab");
        userInfoTableWidget = new QTableWidget(UserInformation_tab);
        userInfoTableWidget->setObjectName("userInfoTableWidget");
        userInfoTableWidget->setGeometry(QRect(0, 50, 921, 601));
        userInfoTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        userInfoTableWidget->setTextElideMode(Qt::ElideMiddle);
        addUserButton = new QPushButton(UserInformation_tab);
        addUserButton->setObjectName("addUserButton");
        addUserButton->setGeometry(QRect(130, 10, 91, 31));
        deleteUserButton = new QPushButton(UserInformation_tab);
        deleteUserButton->setObjectName("deleteUserButton");
        deleteUserButton->setGeometry(QRect(250, 10, 91, 31));
        modifyUserButton = new QPushButton(UserInformation_tab);
        modifyUserButton->setObjectName("modifyUserButton");
        modifyUserButton->setGeometry(QRect(500, 10, 271, 31));
        tabWidget->addTab(UserInformation_tab, QString());
        ParkingPosition_tab = new QWidget();
        ParkingPosition_tab->setObjectName("ParkingPosition_tab");
        transactionTableWidget = new QTableWidget(ParkingPosition_tab);
        transactionTableWidget->setObjectName("transactionTableWidget");
        transactionTableWidget->setGeometry(QRect(0, 50, 921, 601));
        modifyParkingPositionButton = new QPushButton(ParkingPosition_tab);
        modifyParkingPositionButton->setObjectName("modifyParkingPositionButton");
        modifyParkingPositionButton->setGeometry(QRect(500, 10, 271, 31));
        deleteParkingPositionButton = new QPushButton(ParkingPosition_tab);
        deleteParkingPositionButton->setObjectName("deleteParkingPositionButton");
        deleteParkingPositionButton->setGeometry(QRect(250, 10, 91, 31));
        addParkingPositionButton = new QPushButton(ParkingPosition_tab);
        addParkingPositionButton->setObjectName("addParkingPositionButton");
        addParkingPositionButton->setGeometry(QRect(130, 10, 91, 31));
        tabWidget->addTab(ParkingPosition_tab, QString());
        ParkingTransaction_tab = new QWidget();
        ParkingTransaction_tab->setObjectName("ParkingTransaction_tab");
        transactionTableWidget_2 = new QTableWidget(ParkingTransaction_tab);
        transactionTableWidget_2->setObjectName("transactionTableWidget_2");
        transactionTableWidget_2->setGeometry(QRect(0, 50, 921, 601));
        searchTransactionButton = new QPushButton(ParkingTransaction_tab);
        searchTransactionButton->setObjectName("searchTransactionButton");
        searchTransactionButton->setGeometry(QRect(640, 10, 101, 31));
        startDateEdit = new QDateEdit(ParkingTransaction_tab);
        startDateEdit->setObjectName("startDateEdit");
        startDateEdit->setGeometry(QRect(199, 10, 151, 31));
        startDateEdit->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        startDateEdit->setCurrentSection(QDateTimeEdit::YearSection);
        endDateEdit = new QDateEdit(ParkingTransaction_tab);
        endDateEdit->setObjectName("endDateEdit");
        endDateEdit->setGeometry(QRect(410, 10, 151, 31));
        endDateEdit->setDateTime(QDateTime(QDate(2009, 12, 31), QTime(0, 0, 0)));
        endDateEdit->setCurrentSection(QDateTimeEdit::YearSection);
        label = new QLabel(ParkingTransaction_tab);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 20, 21, 16));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        tabWidget->addTab(ParkingTransaction_tab, QString());
        Monitor_tab = new QWidget();
        Monitor_tab->setObjectName("Monitor_tab");
        cameraFeedLabel = new QLabel(Monitor_tab);
        cameraFeedLabel->setObjectName("cameraFeedLabel");
        cameraFeedLabel->setGeometry(QRect(0, 0, 991, 641));
        cameraComboBox = new QComboBox(Monitor_tab);
        cameraComboBox->setObjectName("cameraComboBox");
        cameraComboBox->setGeometry(QRect(1040, 30, 191, 23));
        switchCameraButton = new QPushButton(Monitor_tab);
        switchCameraButton->setObjectName("switchCameraButton");
        switchCameraButton->setGeometry(QRect(1040, 580, 191, 41));
        QFont font1;
        font1.setPointSize(12);
        switchCameraButton->setFont(font1);
        tabWidget->addTab(Monitor_tab, QString());
        Announcement_tab = new QWidget();
        Announcement_tab->setObjectName("Announcement_tab");
        announcementTextEdit = new QTextEdit(Announcement_tab);
        announcementTextEdit->setObjectName("announcementTextEdit");
        announcementTextEdit->setGeometry(QRect(0, 40, 1071, 611));
        announcementTextEdit->setFont(font1);
        publishAnnouncementButton = new QPushButton(Announcement_tab);
        publishAnnouncementButton->setObjectName("publishAnnouncementButton");
        publishAnnouncementButton->setGeometry(QRect(1090, 570, 171, 71));
        QFont font2;
        font2.setPointSize(14);
        publishAnnouncementButton->setFont(font2);
        label_2 = new QLabel(Announcement_tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 10, 171, 21));
        QFont font3;
        font3.setPointSize(16);
        label_2->setFont(font3);
        tabWidget->addTab(Announcement_tab, QString());
        MaintainSystem_tab = new QWidget();
        MaintainSystem_tab->setObjectName("MaintainSystem_tab");
        systemStatusLabel = new QLabel(MaintainSystem_tab);
        systemStatusLabel->setObjectName("systemStatusLabel");
        systemStatusLabel->setGeometry(QRect(0, 0, 1271, 551));
        backupDatabaseButton = new QPushButton(MaintainSystem_tab);
        backupDatabaseButton->setObjectName("backupDatabaseButton");
        backupDatabaseButton->setGeometry(QRect(370, 580, 151, 51));
        restoreDatabaseButton = new QPushButton(MaintainSystem_tab);
        restoreDatabaseButton->setObjectName("restoreDatabaseButton");
        restoreDatabaseButton->setGeometry(QRect(740, 580, 151, 51));
        tabWidget->addTab(MaintainSystem_tab, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 20));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(actionLogout);
        menu_2->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLogout->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225/\345\210\207\346\215\242\347\224\250\346\210\267", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        addUserButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\347\224\250\346\210\267", nullptr));
        deleteUserButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\347\224\250\346\210\267", nullptr));
        modifyUserButton->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(UserInformation_tab), QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        modifyParkingPositionButton->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\350\275\246\344\275\215\344\277\241\346\201\257", nullptr));
        deleteParkingPositionButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\275\246\344\275\215", nullptr));
        addParkingPositionButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\275\246\344\275\215", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ParkingPosition_tab), QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\350\275\246\344\275\215\344\277\241\346\201\257", nullptr));
        searchTransactionButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        startDateEdit->setDisplayFormat(QCoreApplication::translate("MainWindow", "yyyy/MM/dd", nullptr));
        endDateEdit->setDisplayFormat(QCoreApplication::translate("MainWindow", "yyyy/MM/dd", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "~", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ParkingTransaction_tab), QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\345\201\234\350\275\246\345\234\272\346\265\201\346\260\264", nullptr));
        cameraFeedLabel->setText(QString());
        switchCameraButton->setText(QCoreApplication::translate("MainWindow", "\345\210\207\346\215\242\346\221\204\345\203\217\345\244\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Monitor_tab), QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\347\233\221\346\216\247", nullptr));
        publishAnnouncementButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\345\270\203\345\205\254\345\221\212", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\345\205\254\345\221\212\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Announcement_tab), QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\205\254\345\221\212", nullptr));
        systemStatusLabel->setText(QString());
        backupDatabaseButton->setText(QCoreApplication::translate("MainWindow", "\345\244\207\344\273\275\346\225\260\346\215\256\345\272\223", nullptr));
        restoreDatabaseButton->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215\346\225\260\346\215\256\345\272\223", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(MaintainSystem_tab), QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\347\273\264\346\212\244", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
