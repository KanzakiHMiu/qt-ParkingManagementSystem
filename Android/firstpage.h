#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include <QWidget>
#include "changeinfo.h"
#include "netmanager.h"
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QStandardItemModel>

namespace Ui {
class firstpage;
}

class firstpage : public QWidget
{
    Q_OBJECT

public:
    explicit firstpage(QWidget *parent = nullptr);
    ~firstpage();
    void initRoundImages();
    void loadUserData();
    void loadSpotsData();

private slots:
    void on_btnchange_clicked();
    void on_tabWidget_currentChanged(int index);

    void showNextImage();
    void showPreviousImage();
    void animationFinished();

    void on_btnwallet_clicked();
    void on_btnbill_clicked();
    void on_bookbtn_clicked();

    void onNetworkError(const QString&);
    void onLoadSpotsDataReply(QNetworkReply*);
    void onLoadUserDataReply(QNetworkReply*);
    void onBookSpotReply(QNetworkReply *);

    void on_pushButton_clicked();

private:
    Ui::firstpage *ui;
    changeinfo *cginfo;
    netManager* NetManager;

    int currentIndex;
    QTimer *timer;
    QPropertyAnimation *currentAnimation;
    QPropertyAnimation *nextAnimation;
    QGraphicsOpacityEffect *currentEffect;
    QGraphicsOpacityEffect *nextEffect;
    QStandardItemModel *tabModel;
};

#endif // FIRSTPAGE_H
